#include "account_functions.h"

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

void exit_function(int to_client, char buffer[], int size, struct account *account);
void help_function(int to_client, char buffer[]);
void balance_function(int to_client, struct account *account);

#endif