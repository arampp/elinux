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

