CC=/home/alex/studium/semester_6/embedded_linux/buildroot-2010.02/output/staging/usr/bin/avr32-linux-gcc

all: compile

deploy: compile
	cp target/read_value /srv/ngw100/usr/bin

compile:
	$(MAKE) -C src
	mkdir -p target
	mv src/read_value target

clean:
	rm -rf target
	$(MAKE) clean -C src
