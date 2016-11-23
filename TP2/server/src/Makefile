server: main.o server.o linkedList.o client.o handleTransaction.o
	gcc -o ../../bin/server main.o handleTransaction.o server.o linkedList.o client.o -lpthread
server.o: server.c server.h
	gcc -c server.c -Wall -I. -lpthread
linkedList.o: linkedList.c linkedList.h
	gcc -c linkedList.c -Wall -I. -lpthread
client.o: client.c client.h
	gcc -c client.c -Wall -I. -lpthread
handleTransaction.o: handleTransaction.c handleTransaction.h
	gcc -c handleTransaction.c -Wall -I. -lpthread
main.o: main.c
	gcc -c main.c -Wall -I. -lpthread
clean:
	rm *.o
