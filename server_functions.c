#include "server_functions.h"
#include "global.h"
#include "account_functions.h"

void exit_function(int to_client, char buffer[], int size, struct account *account) {

    // includes another parameter of the account struct from the file
    // find the account in the file and update its balance!


    write(to_client, buffer, size);
    printf("sent %s to client\n", buffer);
}