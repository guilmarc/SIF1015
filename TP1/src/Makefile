gestionCHAT_MAIN: gestionLinkedINFO_MAIN.o gestionListeChaineeLinkedINFO.o gestionLinkedINFO.o
	gcc -o gestionLinkedINFO_MAIN gestionLinkedINFO_MAIN.o gestionListeChaineeLinkedINFO.o gestionLinkedINFO.o -lpthread
gestionLinkedINFO_MAIN.o: gestionLinkedINFO_MAIN.c gestionListeChaineeLinkedINFO.h
	gcc -c gestionLinkedINFO_MAIN.c -Wall -I. -lpthread
gestionListeChaineeLinkedINFO.o: gestionListeChaineeLinkedINFO.c gestionListeChaineeLinkedINFO.h
	gcc -c gestionListeChaineeLinkedINFO.c -Wall -I. -lpthread
gestionLinkedINFO.o: gestionLinkedINFO.c gestionListeChaineeLinkedINFO.h
	gcc -c gestionLinkedINFO.c -Wall -I. -lpthread
clean:
	rm *.o
