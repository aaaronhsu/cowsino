#include "server_functions.h"
#include "global.h"
#include "account_functions.h"

void exit_function(int to_client, char buffer[], int size, struct account *account) {

    // includes another parameter of the account struct from the file
    // find the account in the file and update its balance!


    write(to_client, buffer, size);
    printf("sent exit to client\n");
}

void help_function(int to_client, int logged_in) {

    char * buffer = malloc(256);

    if (logged_in == 1) {
      // the user is logged in, show game commands
      sprintf(buffer, "Commands:\nplay flip <bet amount> <bet guess>\nplay dice <bet amount> <num dice> <bet guess>\nbalance\nexit\n");
    } else {
      // the user is not logged in, show login commands
      sprintf(buffer, "Commands:\nlogin <username> <password>\ncreate <username> <password>\nexit\n");
    }
    write(to_client, buffer, 256);
    printf("sent help to client\n");
}

void balance_function(int to_client, struct account *account) {
      
    char * buffer = malloc(100);
    sprintf(buffer, "Your balance is: %d\n", account -> balance);
    write(to_client, buffer, 100);
    printf("sent balance to client\n");
}