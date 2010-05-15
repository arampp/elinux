==============
Schnittstellen
==============

Dieses Dokument beschreibt diverse Schnittstellen, über die der AP7000 verfügt.

GPIO
====
Mit dem GPIO Interface können Pins einzeln angesprochen werden. Dazu muss GPIO
zuerst im Kernel aktiviert werden:

* in Buildroot: make linux26-menuconfig
* Haken setzen unter Device Drivers --> GPIO Support -->
  /sys/class/gpio/.. (sysfs interface)
* in Buildroot: make

Anschließend ist das GPIO Sysfs Interface unter /sys/class/gpio verfügbar.

LED über GPIO ansteuern:
------------------------
LED wird an PA04 (das ist Pin 7 auf J5) gegen GND angeschlossen (WICHTIG: LED
NIEMALS OHNE VORWIDERSTAND ANSCHLIESSEN!!!). Um zugriff auf den Pin zu bekommen,
muss er erstmal konfiguriert werden:

* echo 4 > /sys/class/gpio/export # erstellt unter /sys/class/gpio/gpio4 das
  API für den PIN
* echo "out" > /sys/class/gpio/gpio4/direction # Pin als Ausgang konfigurieren
* echo 1 > /sys/class/gpio/gpio4/value # Ausgang auf "High" setzen
* echo 0 > /sys/class/gpio/gpio4/value # Ausgang auf "Low" setzen
* echo 4 > /sys/class/gpio/unexport # Pin freigeben
