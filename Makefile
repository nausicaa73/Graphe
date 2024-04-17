CFLAGS = -Wall -g

all: test_graphe

test_graphe: test_graphe.o graphe.o io_graphe.o file.o
	gcc $(CFLAGS) -o test_graphe test_graphe.o graphe.o io_graphe.o file.o

graphe.o: graphe.c graphe.h
	gcc $(CFLAGS) -c graphe.c

io_graphe.o: io_graphe.c graphe.h
	gcc $(CFLAGS) -c io_graphe.c

test_graphe.o: test_graphe.c graphe.h 
	gcc $(CFLAGS) -c test_graphe.c

file.o: file.c file.h
	gcc $(CFLAGS) -c file.c

clean:
	rm -f *.o test_graphe *~ data/*~
