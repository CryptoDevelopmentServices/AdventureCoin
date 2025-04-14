
Debian
====================
This directory contains files used to package advcd/advc-qt
for Debian-based Linux systems. If you compile advcd/advc-qt yourself, there are some useful files here.

## advc: URI support ##


advc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install advc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your advc-qt binary to `/usr/bin`
and the `../../share/pixmaps/advc128.png` to `/usr/share/pixmaps`

advc-qt.protocol (KDE)

