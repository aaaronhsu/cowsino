#include "account_functions.h"

int main() {
  printf("here\n");
  int file = open("accounts.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
  printf("past file\n");
  char *username = "bob";
  char *password = "bobiscool";
  add_account(username, password, file);
  read_info(file);
  return 0;
}