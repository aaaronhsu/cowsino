#include "server_functions.h"
#include "global.h"

void exit_function(int to_client, char buffer[], int size) {
    write(to_client, buffer, size);
    printf("sent %s to client\n", buffer);
}