all: main.o account_functions.o
	gcc -o account main.o account_functions.o

main.o: main.c account_functions.h
	gcc -c main.c

account_functions.o: account_functions.c account_functions.h
	gcc -c account_functions.c

run:
	./account