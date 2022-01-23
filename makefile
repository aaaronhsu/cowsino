all: client server

client: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o

server: basic_server.o pipe_networking.o server_functions.o account_functions.o games.o
	gcc -o server basic_server.o pipe_networking.o server_functions.o account_functions.o games.o

basic_client.o: basic_client.c pipe_networking.h global.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h server_functions.h account_functions.h global.h games.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h global.h
	gcc -c pipe_networking.c

server_functions.o: server_functions.c server_functions.h global.h account_functions.h pipe_networking.h
	gcc -c server_functions.c

account_functions.o: account_functions.c account_functions.h global.h
	gcc -c account_functions.c

games.o: games.c games.h global.h
	gcc -c games.c

clean:
	rm *.o
	rm *~

p:
	git add .
	git commit -m"update to run on school computer"
	git push