__all__ = ["VERSION", "PACKAGE", "WEBSITE", "ICON_PATH", "PIXMAP_PATH", "UI_PATH", "PKGDATA_DIR", "BIN_DIR"]

VERSION = "2.2.4"
PACKAGE = "blueman"
WEBSITE = "https://github.com/blueman-project/blueman"
PREFIX = "/usr"
BIN_DIR = "/usr/bin"
LOCALEDIR = "/usr/share/locale"
ICON_PATH = "/usr/share/icons"
PIXMAP_PATH = "/usr/share/blueman/pixmaps"
UI_PATH = "/usr/share/blueman/ui"
DHCP_CONFIG_FILE = "/etc/dhcp/dhcpd.conf"
POLKIT = True
GETTEXT_PACKAGE = "blueman"
RFCOMM_WATCHER_PATH = "/usr/libexec/blueman-rfcomm-watcher"

import os

if 'BLUEMAN_SOURCE' in os.environ:
    _dirname = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
    BIN_DIR = os.path.join(_dirname, 'apps')
    ICON_PATH = os.path.join(_dirname, 'data', 'icons')
    PIXMAP_PATH = os.path.join(_dirname, 'data', 'icons', 'pixmaps')
    UI_PATH = os.path.join(_dirname, 'data', 'ui')