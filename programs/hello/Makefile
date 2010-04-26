all:
	avr32-linux-gcc -g hello.c -o hello

deploy: all
	cp -av hello /srv/ngw100/home/avr32/hello

clean:
	rm -rf hello