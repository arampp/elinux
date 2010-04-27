GCCFLAGS = -g -Wall
GCC = gcc $(GCCFLAGS)
AVRGCC = avr32-linux-gcc $(GCCFLAGS)

compile: clean
	$(GCC) -c src/*.c
	$(GCC) -o logdaemon *.o

crosscompile: clean
	$(AVRGCC) -c src/*.c
	$(AVRGCC) -o logdaemon *.o

install: crosscompile
	cp logdaemon /srv/ngw100/usr/bin/
	cp S99logdaemon /srv/ngw100/etc/init.d/
	chmod a+x  /srv/ngw100/etc/init.d/S99logdaemon

uninstall:
	rm -f /srv/ngw100/usr/bin/logdaemon
	rm -f /srv/ngw100/etc/init.d/S99logdaemon

check: clean
	$(GCC) -c src/logdaemon.c src/util.c test/*.c
	$(GCC) *.o -lcheck -o check

tags:
	etags *

clean:
	rm -rf *.o logdaemon check