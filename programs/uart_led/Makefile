LINT=splint
LINTFLAGS = +posixlib

all: uartclient uartserver

check-syntax:
	$(MAKE) syntax-target SYNTAX="-fsyntax-only"

syntax-target: uartclient uartserver

uartclient: client.o util.o
	$(CC) $(LDFLAGS) -o $@ $?

uartserver: server.o util.o
	$(CC) $(LDFLAGS) -o $@ $?

util.o: util.c
client.o: client.c
server.o: server.c

clean:
	$(RM) *.o uartserver uartclient