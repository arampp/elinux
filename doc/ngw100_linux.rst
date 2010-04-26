GPIO
====

LEDs über sysfs ansteuern
-------------------------

Im Verzeichnis /sys/class/leds gibt es für jede LED ein Verzeichnis.
LED einschalten: echo 255 > brightness
LED ausschalten: echo 0 > brightness
Blinken: echo heartbeat > trigger
Blinken aus: echo none > trigger
