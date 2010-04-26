Upgrade von U-Boot
==================

1. SD-Karte vorbereiten
-----------------------
1. Flash-Upgrade Image runterladen:  wget
http://www.atmel.no/buildroot/binaries/u-boot/atngw100/u-boot-atngw100-v2008.10.bin

2. SD-Karte formatieren: mk2fs.ext2 /dev/sdxx
3. Image auf Flashkarte als flash-upgrade.uimg kopieren
4. Flashkarte unmounten

2. Flash-Upgrade starten
------------------------
1. Flashkarte in NGW100 stecken und reset Knopf drücken
2. Uboot> mmcinit
3. Uboot> ext2load mmc 0:1 0x10400000 /flash-upgrade.uimg
4. Uboot> bootm 0x10400000
5. Den Anweisungen folgen

Hinweis:
Große SD-Karten werden von U-Boot manchmal nicht erkannt, es kommt dan zu
folgender Fehlermeldung:

.bad MBR sector signature 0x0000
** Bad partition 1 **

Abhilfe schafft eine andere, kleinere SD-Karte.
