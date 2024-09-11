#
#  Copyright (c) 2021 Canonical Ltd.
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of the
#  License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
#  USA

import dbus
from gi.repository import Gio

from .DialogUaAttach import DialogUaAttach

class UaService:
    def __init__(self, bus_object, name, entitled, status):
        self.bus_object = bus_object
        self.name = name
        self.entitled = entitled
        self.status = status
        self.request_in_progress = False

class UbuntuProPage(object):

    def __init__(self, parent):
        self._parent = parent

        self.detaching = False

        self.stack_ua_attach = parent.stack_ua_attach
        self.box_ua_attached = parent.box_ua_attached
        self.box_ua_unattached = parent.box_ua_unattached
        self.box_ua_esm = parent.box_ua_esm
        self.switch_ua_esm = parent.switch_ua_esm
        self.label_ua_esm_error = parent.label_ua_esm_error
        self.box_ua_livepatch = parent.box_ua_livepatch
        self.switch_ua_livepatch = parent.switch_ua_livepatch
        self.checkbutton_livepatch_topbar = parent.checkbutton_livepatch_topbar
        self.label_ua_livepatch_error = parent.label_ua_livepatch_error
        self.box_ua_fips = parent.box_ua_fips
        self.switch_ua_fips = parent.switch_ua_fips
        self.label_ua_fips_error = parent.label_ua_fips_error
        self.box_ua_fips_updates = parent.box_ua_fips_updates
        self.switch_ua_fips_updates = parent.switch_ua_fips_updates
        self.label_ua_fips_updates_error = parent.label_ua_fips_updates_error
        self.box_ua_cc_eal = parent.box_ua_cc_eal
        self.switch_ua_cc_eal = parent.switch_ua_cc_eal
        self.label_ua_cc_eal_error = parent.label_ua_cc_eal_error
        self.box_ua_cis_tools = parent.box_ua_cis_tools
        self.switch_ua_cis_tools = parent.switch_ua_cis_tools
        self.label_ua_cis_tools_error = parent.label_ua_cis_tools_error

        parent.button_ua_attach.connect('clicked', self.on_button_ua_attach_clicked)
        parent.button_ua_detach.connect('clicked', self.on_button_ua_detach_clicked)
        self.on_ua_esm_changed_handler = self.switch_ua_esm.connect('notify::active', self.on_ua_esm_changed)
        self.on_ua_livepatch_changed_handler = self.switch_ua_livepatch.connect('notify::active', self.on_ua_livepatch_changed)
        self.on_ua_fips_changed_handler = self.switch_ua_fips.connect('notify::active', self.on_ua_fips_changed)
        self.on_ua_fips_updates_changed_handler = self.switch_ua_fips_updates.connect('notify::active', self.on_ua_fips_updates_changed)
        self.on_ua_cc_eal_changed_handler = self.switch_ua_cc_eal.connect('notify::active', self.on_ua_cc_eal_changed)
        self.on_ua_cis_tools_changed_handler = self.switch_ua_cis_tools.connect('notify::active', self.on_ua_cis_tools_changed)

        self.update_notifier_settings = None
        source = Gio.SettingsSchemaSource.get_default()
        if source is not None:
            schema = source.lookup('com.ubuntu.update-notifier', True)
            if schema is not None:
                settings = Gio.Settings.new('com.ubuntu.update-notifier')
                if schema.has_key('show-livepatch-status-icon'):
                    self.update_notifier_settings = settings

        if self.update_notifier_settings is not None:
            self.on_checkbutton_livepatch_topbar_toggled_handler = self.checkbutton_livepatch_topbar.connect('toggled', self.on_checkbutton_livepatch_topbar_toggled)
            self.on_update_notifier_settings_changed_handler = self.update_notifier_settings.connect('changed::show-livepatch-status-icon', self.on_update_notifier_settings_changed)
            self.on_update_notifier_settings_changed(self.update_notifier_settings, 'show-livepatch-status-icon')

        bus = dbus.SystemBus()
        self.ua_object = bus.get_object('com.canonical.UbuntuAdvantage', '/com/canonical/UbuntuAdvantage/Manager')

        # Monitor services
        self.attached = False
        self.services = {}
        def on_interfaces_added(path, interfaces_and_properties):
            if path == '/com/canonical/UbuntuAdvantage/Manager':
                self.attached = interfaces_and_properties['com.canonical.UbuntuAdvantage.Manager']['Attached']
            elif path.startswith('/com/canonical/UbuntuAdvantage/Services/'):
                properties = interfaces_and_properties.get('com.canonical.UbuntuAdvantage.Service')
                bus_object = bus.get_object('com.canonical.UbuntuAdvantage', path)
                self.services[path] = UaService(bus_object, properties['Name'], properties['Entitled'], properties['Status'])
            self.update_status()
        def on_interfaces_removed(path, interfaces):
            if 'com.canonical.UbuntuAdvantage.Service' in interfaces:
                self.services.pop(path)
            self.update_status()
        def on_properties_changed(interface, changed_properties, invalidated_properties, path):
            def get_property(properties, name, default):
                value = properties.get(name)
                if value is None:
                    value = default
                return value
            if path == '/com/canonical/UbuntuAdvantage/Manager' and interface == 'com.canonical.UbuntuAdvantage.Manager':
                self.attached = get_property(changed_properties, 'Attached', self.attached)
            elif path.startswith('/com/canonical/UbuntuAdvantage/Services/') and interface == 'com.canonical.UbuntuAdvantage.Service':
                service = self.services[path]
                service.entitled = get_property(changed_properties, 'Entitled', service.entitled)
                service.status = get_property(changed_properties, 'Status', service.status)
            self.update_status()
        object_manager_object = bus.get_object('com.canonical.UbuntuAdvantage', '/')
        object_manager_object.connect_to_signal('InterfacesAdded', on_interfaces_added, dbus_interface='org.freedesktop.DBus.ObjectManager')
        object_manager_object.connect_to_signal('InterfacesRemoved', on_interfaces_removed, dbus_interface='org.freedesktop.DBus.ObjectManager')
        bus.add_signal_receiver(on_properties_changed, bus_name='com.canonical.UbuntuAdvantage', signal_name='PropertiesChanged', dbus_interface='org.freedesktop.DBus.Properties', path_keyword='path')
        objects = object_manager_object.GetManagedObjects(dbus_interface='org.freedesktop.DBus.ObjectManager')
        for path in objects:
            on_interfaces_added(path, objects[path])

    def get_service(self, name):
        for service in self.services.values():
            if service.name == name:
                return service
        return None

    def update_status(self):
        self.stack_ua_attach.set_sensitive(not self.detaching)
        if self.attached:
            self.stack_ua_attach.set_visible_child(self.box_ua_attached)
        else:
            self.stack_ua_attach.set_visible_child(self.box_ua_unattached)

        def update_sensitive(box, service):
            box.set_sensitive(service is not None and service.entitled == 'yes' and not service.request_in_progress)

        def update_switch(switch, service, handler):
            if service is not None and service.request_in_progress:
                return
            switch.handler_block(handler)
            switch.set_active(service is not None and service.status == 'enabled')
            switch.handler_unblock(handler)

        esm_infra_service = self.get_service('esm-infra')
        update_sensitive(self.box_ua_esm, esm_infra_service);
        update_switch(self.switch_ua_esm, esm_infra_service, self.on_ua_esm_changed_handler)

        livepatch_service = self.get_service('livepatch')
        update_sensitive(self.box_ua_livepatch, livepatch_service);
        update_switch(self.switch_ua_livepatch, livepatch_service, self.on_ua_livepatch_changed_handler)
        self.checkbutton_livepatch_topbar.set_sensitive(self.update_notifier_settings is not None and self.switch_ua_livepatch.get_active())

        fips_service = self.get_service('fips')
        update_sensitive(self.box_ua_fips, fips_service)
        update_switch(self.switch_ua_fips, fips_service, self.on_ua_fips_changed_handler)

        fips_updates_service = self.get_service('fips-updates')
        update_sensitive(self.box_ua_fips_updates, fips_updates_service)
        update_switch(self.switch_ua_fips_updates, fips_updates_service, self.on_ua_fips_updates_changed_handler)

        cc_eal_service = self.get_service('cc-eal')
        update_sensitive(self.box_ua_cc_eal, cc_eal_service)
        update_switch(self.switch_ua_cc_eal, cc_eal_service, self.on_ua_cc_eal_changed_handler)

        cis_service = self.get_service('cis')
        update_sensitive(self.box_ua_cis_tools, cis_service)
        update_switch(self.switch_ua_cis_tools, cis_service, self.on_ua_cis_tools_changed_handler)

    def on_button_ua_attach_clicked(self, button):
        dialog = DialogUaAttach(self._parent.window_main, self._parent.datadir, self.ua_object)
        dialog.run()

    def on_button_ua_detach_clicked(self, button):
        def on_reply():
            self.detaching = False
            self.update_status()
        def on_error(error):
            # FIXME
            print(error)
            self.detaching = False
            self.update_status()
        self.ua_object.Detach(reply_handler=on_reply, error_handler=on_error, dbus_interface='com.canonical.UbuntuAdvantage.Manager')
        self.detaching = True
        self.update_status()

    def set_service_enabled(self, service_name, switch, error_label):
        error_label.set_visible(False)
        service = self.get_service(service_name)
        if service is None:
            return
        def on_reply():
            service.request_in_progress = False
            self.update_status()
        def on_error(error):
            # FIXME
            print(error)
            error_label.set_visible(True)
            service.request_in_progress = False
            self.update_status()
        if switch.get_active():
            service.bus_object.Enable(reply_handler=on_reply, error_handler=on_error, dbus_interface='com.canonical.UbuntuAdvantage.Service')
        else:
            service.bus_object.Disable(reply_handler=on_reply, error_handler=on_error, dbus_interface='com.canonical.UbuntuAdvantage.Service')
        service.request_in_progress = True
        self.update_status()

    def on_ua_esm_changed(self, switch, param):
        self.set_service_enabled('esm-infra', self.switch_ua_esm, self.label_ua_esm_error)

    def on_ua_livepatch_changed(self, switch, param):
        self.set_service_enabled('livepatch', self.switch_ua_livepatch, self.label_ua_livepatch_error)

    def on_checkbutton_livepatch_topbar_toggled(self, button):
        self.update_notifier_settings.handler_block(self.on_update_notifier_settings_changed_handler)
        self.update_notifier_settings.set_boolean('show-livepatch-status-icon', self.checkbutton_livepatch_topbar.get_active())
        self.update_notifier_settings.handler_unblock(self.on_update_notifier_settings_changed_handler)

    def on_update_notifier_settings_changed(self, settings, key):
        self.checkbutton_livepatch_topbar.handler_block(self.on_checkbutton_livepatch_topbar_toggled_handler)
        self.checkbutton_livepatch_topbar.set_active(self.update_notifier_settings.get_boolean('show-livepatch-status-icon'))
        self.checkbutton_livepatch_topbar.handler_unblock(self.on_checkbutton_livepatch_topbar_toggled_handler)

    def on_ua_fips_changed(self, switch, param):
        self.set_service_enabled('fips', self.switch_ua_fips, self.label_ua_fips_error)

    def on_ua_fips_updates_changed(self, switch, param):
        self.set_service_enabled('fips-updates', self.switch_ua_fips_updates, self.label_ua_fips_updates_error)

    def on_ua_cc_eal_changed(self, switch, param):
        self.set_service_enabled('cc-eal', self.switch_ua_cc_eal, self.label_ua_cc_eal_error)

    def on_ua_cis_tools_changed(self, switch, param):
        self.set_service_enabled('cis', self.switch_ua_cis_tools, self.label_ua_cis_tools_error)
