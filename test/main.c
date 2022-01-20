#include "account_functions.h"

int main() {
  char *file = "accounts.txt";
  char *username = "bob";
  char *password = "bobiscool";
  add_account(username, password, file);
  read_info(file);
  struct account * end_val = check_existance(username, file);
  print_account(end_val, 18);
  return 0;
}