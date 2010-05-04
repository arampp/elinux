all:
	$(MAKE) -C src
	mkdir -p target
	mv src/logdaemon target
	cp -a src/S99logdaemon target

check:
	$(MAKE) -C test
	mkdir -p target
	mv test/check target

clean:
	rm -rf target
	$(MAKE) clean -C src
	$(MAKE) clean -C test