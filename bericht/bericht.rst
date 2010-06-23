UART
----
Der "Universal Asynchronous Receiver Transmitter" (UART) ist ein Bauelement, das
die serielle Datenübertragung zwischen zwei Geräten realisiert. Physisch besteht
das ganze aus 3 Adern:

Rx
  "Receive" - Daten werden empfangen
Tx
  "Transmit"  - Daten werden gesendet
GND
  "Ground" - gegenüber dieser Leitung wird die Spannung von Rx und Tx
  gemessen

.. image:: images/uart.png
   :alt: Adern der UART Schnittstelle


UART arbeitet in einem Spannungsbereich von ca. 0 - 3,3 Volt. Die RS232
Schnittstelle (serielle Schnittstelle am PC) arbeitet in einem Spannungsbereich
von ca. -15 - +15 Volt. D. h. möchte man RS232 mit UART verbinden, ist ein
Pegelwandler nötig.


Das NGW 100 bietet 4 UART Schnittstellen. UART1 ist dabei an die Serielle
Konsole gebunden, die anderen Schnittstellen stehen zur freien Verfügung.  Die
Schnittstellen sind über folgende Pins auf dem Board erreichbar:

- USART 0: Port PA06 - Port09
- USART 1: Port PA20 bzw. Serielle Konsole
- USART 2: Port PB26 - PB27
- USART 3: Port PB15 - PB19



Einbinden in Linux
~~~~~~~~~~~~~~~~~~
Die UART Schnittstelle muss im Linuxkernel aktiviert werden. Dazu wird 
die Datei ``arch/avr32/boards/atngw100/setup.c`` im Kernelverzeichnis
bearbeitet.  In der Funktion ``setup_board(void)`` wird unter folgender Code
eingefügt um UART 2 und 3 zu aktivieren::

  at32_map_usart(2, 1); /* USART 2: /dev/ttyS1 */
  at32_map_usart(3, 2); /* USART 3: /dev/ttyS2 */

Damit die Schnittstelle auch unter ``/dev`` verfügbar ist, fügt man in der
Funktion ``atngw100_init(void)`` folgenden Code ein::

 at32_add_device_usart(1);
 at32_add_device_usart(2);

Anschließend wird der Kernel neu kompiliert, die Schnittstellen stehen nun
unter ``/dev/{ttyS1,ttyS2}`` zur Verfügung.

Ansteuerung mit C
~~~~~~~~~~~~~~~~~

Überblick
``````````````````

Da es sich bei den Schnittstellen ``/dev/ttyS*`` um Characterdevices handelt,
können diese einfach wie eine Datei angesteuert werden. Beispiel::

 char[] text = "Hallo Welt";
 int fd = open( "/dev/ttyS1", O_RDWR );
 write( fd, text, strlen( text );
 close(fd);

In der Standardkonfiguration geben die Schnittstellen gesendete Bytes wieder
zurück, wie es im Terminalbetrieb üblich ist.  Dies möchte man bei einer
normalen Datenübertragung natürlich nicht haben.  Mit dem Struct ``termios``,
definiert in ``asm/termios.h`` kann man die Schnittstelle entsprechend
konfigurieren::

 #define NCCS 19
 struct termios {
   tcflag_t c_iflag;		/* input mode flags */
   tcflag_t c_oflag;		/* output mode flags */
   tcflag_t c_cflag;		/* control mode flags */
   tcflag_t c_lflag;		/* local mode flags */
   cc_t c_line;			/* line discipline */
   cc_t c_cc[NCCS];		/* control characters */
 };

``c_iflag``
  Flags die bestimmen, wie eingehende Zeichen vorverarbeitet werden.

``c_oflag``
  Flags, die bestimmen wie ausgehende Zeichen nachbearbeitet werden.

``c_cflag``
  Kontrolliert Einstellungen für den Port, z. B. Baudrate, Bits per Zeichen,
  Stop Bits, etc.

``c_lflag``
  Konfiguriert ob Zeichen zurrückgesendet werden, wie das eigene Programm
  signalisiert wird, etc.

``c_line``
  In POSIX konformen Systemen unbenutzt.

``c_cc``
  Definiert Steuerzeichen wie z. B. EOF (End of File), Stop Characters, etc.

Eingabekonzepte
```````````````
Es gibt verschiedene Konzepte, eingehende Bytes zu behandeln.  Um die
Konformität zu Manpages und anderen HOWTOs zu wahren, verwende ich die
englischen Bezeichnungen.

Canonical Input Processing
  Dieser Eingebaemodus arbeitet zeilenorientiert. D. h. jeder ``read``
  Aufruf gibt eine komplette Zeile zurrück.  Als Zeilenende wird dabei der Unix
  Line-Feed (ASCII ``LF``) interpretiert.

Non-Canonial Input Processing
  Hierbei wird eine fixe Anzahl von Zeichen bei jedem ``read``
  gelesen.

Asynchroner Input
  Sowohl Canonical, als auch Non-Canonical kann synchron (standard) oder
  asynchron gelesen werden.  Beim synchronen Lesen blockt ``read`` so lange,
  bis etwas gelesen wurde.  Beim asynchronen Lesen kehrt ``read`` hingegen
  sofort zurück und schickt ein Signal, sobald etwas gelesen wurde.

In diesem HOWTO beschränke ich mich auf synchronen Canonical Input, für die
anderen Modi,
siehe `Serial Programming HOWTO`__.


Konfiguration der Schnittstelle
```````````````````````````````
Zur Konfiguration der Schnittstelle stellt ``termios.h`` folgende Funktionen
zur Verfügung:

``int tcgetattr (int __fd, struct termios *__termios_p)``
  Schreibt die aktuelle Konfiguration in das übergebene termios Struct

``extern int tcsetattr (int __fd, int __optional_actions, __const struct termios *__termios_p)``
  Schreibt eine neue Konfiguration in die Schnittstelle

Um nun Canonical Input Processing zu konfigurieren müssen folgende Flags gesetzt werden
(Codebeispiel
von `Serial Programming HOWTO`__)::

 #define BAUDRATE B38400
 struct termios newtio;
 
 /* 
   BAUDRATE: Set bps rate. You could also use cfsetispeed and 
             cfsetospeed.
   CRTSCTS : output hardware flow control (only used if the
             cable has all necessary lines. See sect. 7 of 
             Serial-HOWTO)
   CS8     : 8n1 (8bit,no parity,1 stopbit)
   CLOCAL  : local connection, no modem contol
   CREAD   : enable receiving characters
 */
 newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
   
 /*
   IGNPAR  : ignore bytes with parity errors
   ICRNL   : map CR to NL (otherwise a CR input on the other
             computer will not terminate input) otherwise make 
             device raw (no other input processing)
 */
 newtio.c_iflag = IGNPAR | ICRNL;
   
 /*
   Raw output.
 */
 newtio.c_oflag = 0;
   
 /*
   ICANON  : enable canonical input
   disable all echo functionality, and don't send signals to
   calling program
 */
 newtio.c_lflag = ICANON;

Die entsprechenden Flags sind in ``termios.h`` definiert.

.. _SPHT: http://www.tldp.org/HOWTO/Serial-Programming-HOWTO/index.html
__ SPHT_
