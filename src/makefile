CC = gcc
CFLAGS = -g -Wall
TARGET = linked_info
CCRED=$(echo -e "\033[0;31m")
CCYELLOW=$(echo -e "\033[0;33m")
CCEND=$(echo -e "\033[0m")

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
	$(RM) *.o *.gch linked_info

module:
	touch $(I).h $(I).c
	echo "#include <stdio.h>" >> $(I).c
	echo "#include <stdlib.h>" >> $(I).c
	echo "#include <"$(I)".h>" >> $(I).c
	echo "#ifndef "$(shell echo $(I) | tr a-z A-Z)_H >> $(I).h
	echo "#define "$(shell echo $(I) | tr a-z A-Z)_H >> $(I).h
	echo "\n" >> $(I).h
	echo "#endif" >> $(I).h
	echo "\nCreated, don't forget to add "$(I)" into the makefile"
