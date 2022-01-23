#ifndef ACCOUNT_FUNCTIONS_H
#define ACCOUNT_FUNCTIONS_H

#define ACCOUNT_ITEM_SIZE 1000

// constraint: no spaces in username/password (seems reasonable)
struct account {
  char username[ACCOUNT_ITEM_SIZE];
  char password[ACCOUNT_ITEM_SIZE];
  int balance;
};

struct account * check_existance(char *username, char *file_name);

void add_account(char *username, char *password, char *file_name);
void add_account2(char *username, char *password, int balance, char *file_name);

void print_account(struct account *acc, int num);

long long get_size(char *file_name);

void read_info(char *file_name);

void update_balance(char *username, int balance, char *file_name);
void update_balance2(char *username, int balance, char *file_name);

#endif