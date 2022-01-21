#include "pipe_networking.h"
#include "global.h"

int main() {
  printf("type \"exit\" to leave\n");

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  printf("Send string: ");
  char buffer[BUFFER_SIZE];

  while (fgets(buffer, BUFFER_SIZE, stdin)) {
      buffer[strcspn(buffer, "\n")] = 0;
      write(to_server, buffer, BUFFER_SIZE);
      // receiving
      read(from_server, buffer, BUFFER_SIZE);
      printf("received\n");
      if (strcmp(buffer, "exit") == 0) {
        printf("Request to exit!\n");
        exit(0);
      }
      printf("Received response: %s\n", buffer);
      printf("Send string: ");
  }

  return 0;
}