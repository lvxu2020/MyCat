.PHONY:clean all
#CC=$(CC)
#CFLAGS=-Wall -g -lstdc++ -pthread -l dbus-1 -w
CC=gcc
CFLAGS=-Wall -g  -pthread  -w
LIBS = -l paho-mqtt3c

BIN=server

SUBDIR=$(shell ls -d */)
APPINCLUDE = -I./
ROOTSRC=$(wildcard *.c)
ROOTOBJ=$(ROOTSRC:%.c=%.o)

SUBSRC=$(shell find $(SUBDIR) -name '*.c')
SUBOBJ=$(SUBSRC:%.c=%.o)

$(BIN):$(ROOTOBJ) $(SUBOBJ)
	$(CC) $(CFLAGS)   $(APPINCLUDE) $(ROOTOBJ) $(SUBOBJ) -o $(BIN) $(LIBS)
.c.o:
	$(CC) $(CFLAGS) $(APPINCLUDE) -c $< -o $@
clean:
	rm -f *.o $(BIN) $(ROOTOBJ) $(SUBOBJ)
