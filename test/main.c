#include "account_functions.h"

int main() {
  char *file = "accounts.txt";
  char *username = "bob";
  char *password = "bobiscool";
  add_account(username, password, file);
  read_info(file);
  return 0;
}