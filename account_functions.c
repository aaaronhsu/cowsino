#include "account_functions.h"

struct account * check_existance(char *username, char *password, int file) {
  struct account *ret = malloc(sizeof(struct account));
  strncpy(ret -> username, username, sizeof(ret -> username));
  strncpy(ret -> password, password, sizeof(ret -> password));;
  ret -> balance = 0;
  return ret;
}

// add account- stores the values separated by spaces for parsing