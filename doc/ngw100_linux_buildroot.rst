====================
Linux auf dem NGW100
====================

Software
========

SSH Client Dropbear
-------------------

Dropbear lässt sich nicht starten / komische Logmeldungen
`````````````````````````````````````````````````````````

Problem
~~~~~~~
* Dropbear bleibt beim generieren der Keys hängen.
* Dropbear scheint korrekt zu starten, man kann sich ber SSH einloggen
* In /var/log/messages tauchen folgende Meldungen auf:
  "Warning: Reading the random source seems to have blocked.
  If you experience problems, you probably need to find a better entropy
  source."

Lösung
~~~~~~
In */etc/init.d/S50dropbear* Code am Anfang der *start()* Funktion einfügen::
  
  #workaround for /dev/randomproblem
  mv /dev/random /dev/random-blocks
  ln -s /dev/urandom /dev/random

Hintergrund
~~~~~~~~~~~
* Quelle: http://www.nslu2-linux.org/wiki/Unslung/KnownProblems
* Hintergrundinfos: http://people.freebsd.org/~dougb/randomness.html

Linux Probleme
==============
/usr/ wird nicht über nfs geladen
---------------------------------
Problem
~~~~~~~
* Wird ein Programm auf dem Host z. B. nach /usr/bin kopiert, ist es nicht auf
  dem Target auffindbar

Lösung
~~~~~~
Sieht man sich /etc/fstab an, sieht man darin folgenden Eintrag::
  /dev/mtdblock3  /usr            jffs2           defaults        0       0

Scheinbar wird also /usr vom Flashspeicher eingebunden. Kommentiert man diese
Zeile aus (# davor), wird /usr nach einem Neustart über nfs geladen.


Hardware
========

GPIO
----

LEDs über sysfs ansteuern
`````````````````````````

Im Verzeichnis /sys/class/leds gibt es für jede LED ein Verzeichnis.

* LED einschalten: echo 255 > brightness
* LED ausschalten: echo 0 > brightness
* Blinken: echo heartbeat > trigger
* Blinken aus: echo none > trigger
