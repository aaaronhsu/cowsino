#include "server_functions.h"
#include "pipe_networking.h"

void exit_function(int to_client, char buffer[]) {
    write(to_client, buffer, BUFFER_SIZE);
    printf("sent %s to client\n", buffer);
}