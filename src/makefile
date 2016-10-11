CC = gcc
CFLAGS = -g -Wall
TARGET = linked_info

default: $(TARGET)

$(TARGET): main.o linked_list.o member_info.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o linked_list.o member_info.o

main.o: main.c main.h
	gcc -c main.c -Wall -I.

linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c -Wall -I.

member_info.o: member_info.c member_info.h
	gcc -c member_info.c -Wall -I.

clean:
	$(RM) *.o
