.PHONY: all clean


CC=gcc
LFLAGS = -g -W -Wall -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual -o
CFLAGS = -c -g -W -Wall -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual 
LDFLAGS_NET=



PROGS= codi1 lecMedEsc codideco restesDe2erreurs codeWordsP2 sender receiver medium 
FSAUVE=TP3Network.tgz
ifeq (coding2.c,$(wildcard coding2.c))
  PROGS+= sender2 receiver2
  FSAUVE=TP3Network_cor.tgz
endif

SOCKETS=s_medsend s_medrec sock_send sock_rec

all: $(PROGS)

sender: sending.o sockettoolbox.o rutinesBits.o codification.o decodification.o poly.o bitsBase.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

receiver: receiving.o sockettoolbox.o rutinesBits.o codification.o decodification.o poly.o bitsBase.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

sender2: sending.o sockettoolbox.o rutinesBits.o codification.o decodification.o poly.o bitsBase.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

receiver2: receiving.o sockettoolbox.o rutinesBits.o codification.o decodification.o poly.o bitsBase.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

medium : medium.o error.o sockettoolbox.o 
	$(CC) -o $@ $^ $(LDFLAGS_NET) -lm

error.o: error.c headers/error.h


lecMedEsc: lecMedEsc.o rutinesBits.o codification.o decodification.o poly.o bitsBase.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

codi1  : codi1.o rutines1.o 
	$(CC) -o $@ $^ $(LDFLAGS_NET)

codideco: codideco.o rutinesBits.o codification.o decodification.o poly.o bitsBase.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

restesDe2erreurs: restesDe2erreurs.o rutinesBits.o codification.o decodification.o poly.o bitsBase.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

codeWordsP2: codeWordsP2.o rutinesBits.o codification.o decodification.o poly.o bitsBase.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

.c.o:
	$(CC) $(CFLAGS) -c $<

sockclean:force
	rm -f $(SOCKETS)

clean0: force
	rm -f *.o $(PROGS) $(SOCKETS) .depend .*.bak aaa

dep:force
	touch .depend
	makedepend -f .depend *.c
force:

ifeq (.depend,$(wildcard .depend))
include .depend
endif

sauve:force
	tar cvf - Makefile GNUmakefile *.c headers/*.h | gzip > $(FSAUVE)

#gmake test with freeBSD
test:force $(PROGS) sockclean
	killall medium receiver sender || true
	./medium 1& sleep 1; ./receiver aaa& sleep 1; ./sender receiving.c
	diff aaa receiving.c




clean: clean0 clean1


clean1:
	rm -f *.o codi1	lecMedEsc codideco restesDe2erreurs codeWordsP2



