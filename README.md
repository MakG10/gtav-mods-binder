# Mods Binder for GTA V
ASI plugin for Script Hook V to access all configured mods with one single in-game menu.

![Mods Binder Menu screenshot](http://i.imgur.com/hoCfFqX.png)

Installation
--------------
1. Install [Script Hook V by Alexander Blade](http://www.dev-c.com/gtav/scripthookv/) and ASI loader that comes with it.
2. Paste ModsBinder.asi and ModsBinder.ini from "bin" directory into GTA V folder.

Usage
--------------
Defaults:
F5 - Open Menu
CTRL+BACKSPACE - Repeat the last action performed in Mods Binder menu (useful in case if a binded mod doesn't support BACKSPACE to exit its menu and you don't remember the shortcut for open/close action).

The menu is consisted of entries from "Mods" section in ModsBinder.ini file. You can easily add mods providing a display name and human-readable key combination. The display name can contain spaces. Example:

```
[Mods]
Bodyguard Menu = F8
Native Trainer = F4
Custom Mod     = CTRL+L
Custom Mod #2  = SHIFT+SPACE+9
```

If __autoscan__ option is enabled, Mods Binder checks if any of a few popular, pre-defined mods is installed. In order for autoscanner to work, the mods must be inside GTA V folder and must have original filenames.

Options
--------------
* **shortcut** - Shortcut for the Mods Binder menu, it may be a combination of several keys, i.e. SHIFT+V (default: F5)
* **closeCurrentShortcut** - Shortcut for refiring the last selected item (default: CTRL+BACKSPACE)
* **autoscan** - Autoscan feature automatically checks if any of pre-defined mods is installed and adds it to the menu. Possible values: true, false (default: true)

Video
--------------
Watch it on [YouTube](https://www.youtube.com/watch?v=_ZuaDE9sFRw).
