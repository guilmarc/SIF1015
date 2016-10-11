CC = gcc
CFLAGS = -g -Wall
TARGET = linked_info

default: $(TARGET)

$(TARGET): main.o linked_list.o member_info.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o linked_list.o member_info.o

main.o: main.c main.h
	$(CC) -c main.c $(CFLAGS) -I.

linked_list.o: linked_list.c linked_list.h
	$(CC) -c linked_list.c $(CFLAGS) -I.

member_info.o: member_info.c member_info.h
	$(CC) -c member_info.c $(CFLAGS) -I.

clean:
	$(RM) *.o linked_info
