=========
Buildroot
=========

Ein neues Paket hinzufügen
--------------------------

Die Dokumentation von Atmel scheint schon ziemlich veraltet zu sein, besser ist
diese Anleitung:
http://buildroot.uclibc.org/downloads/buildroot.html#add_packages

Um ein neues Paket einzufügen, sind folgende Schritte notwendig:

 #. Neues Verzeichnis unter packages erstellen.
 #. Config.in Datei erstellen.
 #. Paket in packages/Config.in eintragen.
 #. .mk Datei erstellen.
     * 3 Typen werden unterschieden:
        * Generische Makefiles
        * Makefiles für autotools
        * Manuelle Makefiles (veraltet, wird bei neuen Paketen nicht empfohlen)
 #. Tarball nach $BUILDROOT/dl kopieren um dessen download zu verhindern.

Ein vorhandenes Paket neu bauen
-------------------------------
 * Einfachste Möglichkeit: output/build/packagename-version löschen. Dadurch
   wird das Paket erneut entpackt, konfiguriert, kompiliert und installiert
 * Bei Buildrootpaketen können Stampfiles
   (ouput/build/packagename-version/.stamp_*) gelöscht werden um einzelne
   Ereignisse zu triggern. Bei anderen Paketen muss der package.mk file
   untersucht werden.
