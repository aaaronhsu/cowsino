#include "account_functions.h"

struct account * check_existance(char *username, char *password, char *file) {
  struct account *ret = malloc(sizeof(struct account));
  strncpy(ret -> username, username, sizeof(ret -> username));
  strncpy(ret -> password, password, sizeof(ret -> password));;
  ret -> balance = 0;
  return ret;
}

// add account- stores the values separated by spaces for parsing
// under assumption that this account does not already exist
void add_account(char *username, char *password, char *file) {
  struct account *add = malloc(sizeof(struct account));
  strncpy(add -> username, username, sizeof(add -> username));
  strncpy(add -> password, password, sizeof(add -> password));;
  add -> balance = 0;
  print_account(add, 10);
  write(file, add, sizeof(struct account));
}

void print_account(struct account *acc, int num) {
  printf("Entry %d:\tUser: %s\tPass: %s\tBalance: %d\n", num, acc -> username, acc -> password, acc -> balance);
}

long long get_size(char *file) {
  struct stat status;
  char *name = "accounts.txt";
  if (stat(name, &status) == -1) {
    printf("Error opening file: %s\n", strerror(errno));
    return -1; // error
  }
  return (status.st_size); // in the file stats
}

void read_info(char *file) {
  long long size = get_size(file);
  if (size == -1) printf("smth went wrong\n");
  int num_accounts = (size / sizeof(struct account));
  struct account accounts[num_accounts];
  read(file, accounts, size);
  for (int i = 0; i < num_accounts; i++) {
    print_account(&(accounts[i]), i);
  }
}
