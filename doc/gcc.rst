Unterschied zwischen avr32-gcc und avr32-linux-gcc?
===================================================

* avr32-gcc erzeugt nativen Code, der direkt auf dem AVR32 läuft, unter Linux
  gibt es i. d. R. einen Seg Fault. Er linkt gegen die sog. newlib.

* avr32-linux-gcc erzeugt den Code, der auf dem Linux Kernel läuft. So wie es
  aussieht, ist dieser Compiler nicht im NGW100 BSP enthalten. Er linkt gegen uClib.

* Die Linux-Toolchain befindet sich in *$BUILDROOT/output/staging/usr/bin
  nachdem Buildroot erfolgreich durchgelaufen ist. Sobald man dieses Verzeichnis
  in $PATH aufnimmt, steht das Kommando avr32-linux-gcc zur Verfügung.
