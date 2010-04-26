Upgrade Auf eine neue U-Boot Version
====================================

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

Wichtige Umgebungsvariablen
============================
bootargs:
  Der Inhalt dieser Veriable wird dem Linux Kernel als Bootargumente übergeben
  
bootcmd:
  Beinhaltet einen Commandstring, der automatisch von U-Boot beim starten
  ausgeführt wird.

ipaddr:
  IP von NGW100 wird für tftp gebraucht

serverip:
  Adresse des tftp servers

Wichtige Kommandos
==================
bootm <Addr>:
  Booten von der angegebenen Speicheradresse

setenv <Variable> <String>:
  Setzt Umgebungsvariablen

saveenv:
  Sichert die Umgebungsvariablen in den Flash Speicher, so dass sie den Neustart überleben

Booten per NFS
==============
Wir gehen davon aus, dass NFS auf dem Host korrekt eingerichtet ist. Unter
/srv/ngw100 liegt das Root-Dateisystem und unter /srv/ng100/uImage das
KernelImage. IP Des Hosts: 192.168.1.8, IP des Targets: 192.168.1.4

U-Boot> nfs 11000000 192.168.1.8:/srv/ngw100/boot/uImage
U-Boot> setenv bootargs 'root=nfs nfsroot=192.168.1.8:/srv/ngw100 ip=192.168.1.4:192.168.1.8::255.255.255.0::eth0:none'
U-Boot> bootm

Beim Laden des Kernels kommt es zu folgender Fehlermeldung: ERROR: Cannot umount
Der Kernel wurde aber trozdem geladen - die Meldung kann ignoriert werden.

Kommt es während des Bootvorgangs zu folgendem Fehler:
Warning: unable to open an initial console.

Schafft folgendes Workaround abhilfe:
Aufdem Host: sudo cp -a /dev/{console,null} /srv/ngw100/dev

Hintergrund ist, dass versucht wird auf dem Host mit 'mknod' die beiden Devices anzulen, dies aber fehlschlägt, weil dieser Befehl nur mit Rootrechten ausgeführt werden kann.
