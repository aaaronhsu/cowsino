all: client server

client: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o

server: basic_server.o pipe_networking.o
	gcc -o server basic_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h server_functions.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

server_functions.o: server_functions.c server_functions.h pipe_networking.h
	gcc -c server_functions.c

clean:
	rm *.o
	rm *~