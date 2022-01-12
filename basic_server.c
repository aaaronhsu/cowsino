#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;
  int f;

  printf("server starting...\n");

  while (1) {

    from_client = server_setup();

    f = fork();
    if (f) {
      close(from_client);
    } else {
      to_client = server_connect(&from_client);
      char buffer[BUFFER_SIZE];
      while (read(from_client, buffer, BUFFER_SIZE)) {
          char response[BUFFER_SIZE];
          int i = 0;
          while (buffer[i]) {
            response[i] = (buffer[i] + 1);
            i++;
          }
          write(to_client, response, BUFFER_SIZE);
          printf("sent %s to client\n", response);
      }
      exit(0);
    }

    printf("client has connected, but still waiting for new connections\n");
  }
  return 0;
}