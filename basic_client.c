#include "pipe_networking.h"
#include "global.h"

int main() {
  printf("type \"exit\" to leave\n");

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  printf("Enter a command: ");
  char buffer[BUFFER_SIZE];

  while (fgets(buffer, BUFFER_SIZE, stdin)) {
      buffer[strcspn(buffer, "\n")] = 0;
      write(to_server, buffer, BUFFER_SIZE);
      // receiving
      read(from_server, buffer, BUFFER_SIZE);
      // printf("received\n");
      if (strcmp(buffer, "exit") == 0) {
        exit(0);
      }
      printf("\n%s\n", buffer);

      printf("Enter a command: ");
  }

  return 0;
}