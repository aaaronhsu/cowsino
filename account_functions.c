#include "account_functions.h"

struct account * check_existance(char *username, char *password, int file) {
  struct account *ret = malloc(sizeof(struct account));
  strncpy(ret -> username, username, sizeof(ret -> username));
  strncpy(ret -> password, password, sizeof(ret -> password));;
  ret -> balance = 0;
  return ret;
}

// add account- stores the values separated by spaces for parsing
// under assumption that this account does not already exist
void add_account(char *username, char *password, int file) {
  char *to_add;
  strcat(to_add, username);
  strcat(to_add, " ");
  strcat(to_add, password);
  strcat(to_add, " 0\n"); // auto sets the balance to 0
  write(file, *to_add, 2 * ACCOUNT_ITEM_SIZE + 3);
}
