all: main.o games.o
	gcc -o wheel main.o games.o

main.o: main.c global.h games.h
	gcc -c main.c

games.o: games.c games.h global.h
	gcc -c games.c

run:
	./wheel