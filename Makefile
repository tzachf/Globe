MyGlobe: main.o Countries.o HashTable.o LinkedList.o KeyValuePair.o
	gcc main.o Countries.o HashTable.o LinkedList.o KeyValuePair.o -o MyGlobe
Countries.o: Countries.c Countries.h Defs.h
	gcc -c Countries.c
HashTable.o: HashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c HashTable.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
main.o: main.c KeyValuePair.h Defs.h LinkedList.h HashTable.h Countries.h
	gcc -c main.c

