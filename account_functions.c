#include "account_functions.h"
#include "global.h"

// takes in a username and password
struct account * check_existance(char *username, char *file_name) {
  int file = open(file_name, O_CREAT | O_APPEND | O_RDONLY, 0777);

  long long size = get_size(file_name);
  if (size == -1) printf("smth went wrong\n");
  int num_accounts = (size / sizeof(struct account));
  struct account accounts[num_accounts];

  read(file, accounts, size);
  for (int i = 0; i < num_accounts; i++) {
    if (strcmp(accounts[i].username, username) == 0) {
      struct account * ret = malloc(sizeof(struct account));
      strncpy(ret -> username, accounts[i].username, sizeof(ret -> username));
      strncpy(ret -> password, accounts[i].password, sizeof(ret -> password));
      ret -> balance = accounts[i].balance;
      return ret;
    }
  }
  return NULL;
}

// under assumption that this account does not already exist
void add_account(char *username, char *password, char *file_name) {
  struct account *add = malloc(sizeof(struct account));
  strncpy(add -> username, username, sizeof(add -> username));
  strncpy(add -> password, password, sizeof(add -> password));;
  add -> balance = 100;
  int file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
  write(file, add, sizeof(struct account));
}

// under assumption that this account does exist
void add_account2(char *username, char *password, int balance, char *file_name) {
  struct account *add = malloc(sizeof(struct account));
  strncpy(add -> username, username, sizeof(add -> username));
  strncpy(add -> password, password, sizeof(add -> password));;
  add -> balance = balance;
  int file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
  write(file, add, sizeof(struct account));
}

void print_account(struct account *acc, int num) {
  printf("Entry %d:\tUser: %s\tPass: %s\tBalance: %d\n", num, acc -> username, acc -> password, acc -> balance);
}

long long get_size(char *file_name) {
  struct stat status;
  if (stat(file_name, &status) == -1) {
    printf("Error opening file: %s\n", strerror(errno));
    return -1; // error
  }
  return (status.st_size); // in the file stats
}

// for testing, reads out the entire file
void read_info(char *file_name) {
  long long size = get_size(file_name);
  if (size == -1) printf("smth went wrong\n");
  int num_accounts = (size / sizeof(struct account));
  struct account accounts[num_accounts];

  int file = open(file_name, O_RDONLY, 0777);
  read(file, accounts, size);
  for (int i = 0; i < num_accounts; i++) {
    print_account(&(accounts[i]), i);
  }
}

void update_balance2(char *username, int balance, char *file_name) {
  long long size = get_size(file_name);
  if (size == -1) printf("smth went wrong\n");
  int num_accounts = (size / sizeof(struct account));
  struct account accounts[num_accounts];

  int file = open(file_name, O_RDONLY, 0777);
  read(file, accounts, size);

  remove("accounts.txt");
  int new_file = open("accounts.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);

  for (int i = 0; i < num_accounts; i++) {
    if (strcmp(accounts[i].username, username) == 0) {
      accounts[i].balance = balance;
    }
    add_account2(accounts[i].username, accounts[i].password, accounts[i].balance, "accounts.txt");
  }
}

// currently does not work!!
void update_balance(char *username, int balance, char *file_name) {
  printf("updating balance...\n");
  int file = open(file_name, O_CREAT | O_APPEND | O_RDONLY, 0777);

  long long size = get_size(file_name);
  if (size == -1) printf("smth went wrong\n");
  int num_accounts = (size / sizeof(struct account));
  struct account accounts[num_accounts];

  read(file, accounts, size);
  for (int i = 0; i < num_accounts; i++) {
    if (strcmp(accounts[i].username, username) == 0) {
      printf("found username\n");
      accounts[i].balance = balance;
      struct account add = accounts[i];
      print_account(&add, 3);
      
      // THIS HERE DOES NOT WORK IDK WHY
      lseek(file, i * sizeof(struct account), SEEK_SET);
      write(file, &add, sizeof(struct account));
      if (file == -1) {
        printf("error replacing data in the file\n");
      }
      break;
    }
  }
}
