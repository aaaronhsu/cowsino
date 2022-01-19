#ifndef ACCOUNT_FUNCTIONS_H
#define ACCOUNT_FUNCTIONS_H

/*

[called on login]
check_existance(username, password, file_with_info)
 - returns an account if it's found
 - returns NULL if not exists

[called on create account]
add_account(username, password, file_with_info)
- runs check_existance and returns NULL if can't complete (error!)

account struct

find(user, pass)

disconnect(username, password, balance, file_with_info)
- called when the client disconnects or runs exit
- updates the account entry with the new balance in the file




*/

#endif