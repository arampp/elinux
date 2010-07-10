CC=/home/alex/studium/semester_6/embedded_linux/buildroot-2010.02/output/staging/usr/bin/avr32-linux-gcc

all: compile

readtest:
	$(CC) -o read_uart read_uart.c
	cp read_uart /srv/ngw100/usr/bin

compile:
	$(CC) -c main.c
	$(CC) -o read_value *.o

tags:
	etags *

clean:
	rm -rf *.o read_value