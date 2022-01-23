#include "pipe_networking.h"
#include "global.h"

int server_setup() {
  mkfifo(WKP, 0644);
  int from_client = open(WKP, O_RDONLY);
  remove(WKP);
  return from_client;
}

int server_connect(int *from_client) {
  // the pipe already exists now

  // make pipe and wait for connection to pipe  

  // server receives secret pipe from client
  char secret_pipe[HANDSHAKE_BUFFER_SIZE];
  read(*from_client, secret_pipe, HANDSHAKE_BUFFER_SIZE);

  // writes the acknowledgement of receiving secret pipe to client
  int to_client = open(secret_pipe, O_WRONLY);
  write(to_client, ACK, HANDSHAKE_BUFFER_SIZE);
  printf("4. server wrote ack to client\n");

  // final getting of ack
  char ack[HANDSHAKE_BUFFER_SIZE];
  read(*from_client, ack, HANDSHAKE_BUFFER_SIZE);
  if (!strcmp(ack, ACK)) {
    printf("8. successful 3 way handshake!\n");
  }

  return to_client;
}

int client_handshake(int *to_server) {
  // client creates a secret pipe (named pid)
  char secret_pipe[HANDSHAKE_BUFFER_SIZE];
  sprintf(secret_pipe, "%d", getpid());
  mkfifo(secret_pipe, 0644);
  // printf("1. client created secret pipe named pid\n");

  // client sends secret pipe to server
  *to_server = open(WKP, O_WRONLY);
  write(*to_server, secret_pipe, HANDSHAKE_BUFFER_SIZE);
  // printf("2. client sent secret pipe to server\n");

  // client reads the ack from server and deletes secret pipe
  int from_server = open(secret_pipe, O_RDONLY);
  char ack[HANDSHAKE_BUFFER_SIZE];
  read(from_server, ack, HANDSHAKE_BUFFER_SIZE);
  if (!strcmp(ack, ACK)) {
    // printf("5. client successfully read ack from secret_pipe\n");
    remove(secret_pipe);
    // printf("6. clinet removed secret pipe\n");
    // client sends final acknowledgement message
    write(*to_server, ack, HANDSHAKE_BUFFER_SIZE);
    // printf("7. client has sent acknowledgement of final response\n");
  }

  return from_server;
}