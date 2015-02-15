#
# modbus-pwc-interace - a small modbus demo for a particular
#   interface. 
#

CFLAGS= -I/usr/local/include/modbus 
LIBS= -lmodbus -Wl,-rpath=/usr/local/lib/

all: master slave

master: master.c
	$(CC) $(CFLAGS) master.c -o master $(LIBS)

slave: slave.c
	$(CC) $(CFLAGS) slave.c -o slave $(LIBS)

run:
	-rm master slave
	make
	./slave &
	sleep 1
	./master
