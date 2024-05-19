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

import os
from gettext import gettext as _

from softwareproperties.gtk.utils import (
    setup_ui,
)

class DialogUaAttach:
  def __init__(self, parent, datadir, ua_object):
    """setup up the gtk dialog"""
    setup_ui(self, os.path.join(datadir, "gtkbuilder", "dialog-ua-attach.ui"), domain="software-properties")

    self.ua_object = ua_object
    self.dialog = self.dialog_ua_attach
    self.dialog.set_transient_for(parent)

    self.attaching = False

  def run(self):
    self.dialog.run()
    self.dialog.hide()

  def update_state(self):
    have_token = self.entry_token.get_text() != ''
    self.button_attach.set_sensitive(have_token and not self.attaching)
    self.entry_token.set_sensitive(not self.attaching)
    if self.attaching:
        self.spinner.start()
    else:
        self.spinner.stop()

  def attach(self):
    if self.attaching:
        return

    token = self.entry_token.get_text()
    if token == '':
        return

    self.attaching = True
    self.label_attach_error.set_text('')
    def on_reply():
        self.dialog.response(0)
    def on_error(error):
        # FIXME
        print(error)
        self.label_attach_error.set_text(_('Failed to attach. Please try again'))
        self.attaching = False
        self.update_state()
    self.ua_object.Attach(token, reply_handler=on_reply, error_handler=on_error, dbus_interface='com.canonical.UbuntuAdvantage.Manager')
    self.update_state()

  def on_token_entry_changed(self, entry):
    self.update_state()

  def on_token_entry_activate(self, entry):
    self.attach()

  def on_attach_clicked(self, button):
    self.attach()

  def on_cancel_clicked(self, button):
    self.dialog.response(0)
