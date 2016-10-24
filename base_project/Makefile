CFLAGS = -g -Wall -I.
TARGET = gestionLinkedINFO

gestionCHAT_MAIN: $(TARGET)_MAIN.o gestionListeChaineeLinkedINFO.o $(TARGET).o
	gcc -o $(TARGET)_MAIN $(TARGET)_MAIN.o gestionListeChaineeLinkedINFO.o $(TARGET).o $(CFLAGS)
$(TARGET)_MAIN.o: $(TARGET)_MAIN.c gestionListeChaineeLinkedINFO.h
	gcc -c $(TARGET)_MAIN.c $(CFLAGS)
gestionListeChaineeLinkedINFO.o: gestionListeChaineeLinkedINFO.c gestionListeChaineeLinkedINFO.h
	gcc -c gestionListeChaineeLinkedINFO.c $(CFLAGS)
gestionLinkedINFO.o: gestionLinkedINFO.c gestionListeChaineeLinkedINFO.h
	gcc -c gestionLinkedINFO.c $(CFLAGS)

clean:
	$(RM) *.o *.gch $(TARGET)

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
