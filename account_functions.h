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

void print_account(struct account *acc, int num);

long long get_size(char *file_name);

void read_info(char *file_name);

/*

disconnect(username, password, balance, file_with_info)
- called when the client disconnects or runs exit
- updates the account entry with the new balance in the file

*/

#endif