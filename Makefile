CC = gcc
CFLAGS = -Werror -Wall -pedantic

all : driver

driver : main.o generic_linked_list.o
	$(CC) $(CFLAGS) -o driver main.o generic_linked_list.o

main.o : main.c generic_linked_list.h
	$(CC) $(CFLAGS) -c main.c

generic_linked_list.o : generic_linked_list.c generic_linked_list.h
	$(CC) $(CFLAGS) -c generic_linked_list.c

clean :
	rm -f *.o driver
