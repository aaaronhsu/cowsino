#include "pipe_networking.h"
#include "server_functions.h"
#include "account_functions.h"
#include "games.h"
#include "global.h"


int main() {
  int to_client;
  int from_client;
  int f;

  printf("server starting...\n");

  while (1) {
    // handshake stuff
    from_client = server_setup();

     // create account file (up here so that you can access same file each new client)
     char *file = "accounts.txt";

    // fork for many clients
    f = fork();
    if (f) {
      close(from_client);
    } else {
      // handshake stuff
      to_client = server_connect(&from_client);
  
      // create an account for whichever user might log in
      struct account *account = malloc(sizeof(struct account));
      // automatically not logged in
      int logged_in = 0;

      char buffer[BUFFER_SIZE];
      while (read(from_client, buffer, BUFFER_SIZE)) {
        // parse the buffer (command will be the first element of the buffer)
        char *command = strtok(buffer, " ");
        // if "exit", then exit
        if (strcmp(command, "exit")) {
          exit_function(to_client, buffer, BUFFER_SIZE);
        }

        // check if the user is logged in
        if (logged_in) {
          if (strcmp(command, "play") == 0) {
            char *game_name = strtok(NULL, " ");

            if (strcmp(game_name, "flip") == 0) {
              char *bet_amount = strtok(NULL, " ");
              char *bet_guess = strtok(NULL, " ");

              int bet_amount_int = -1;
              int bet_guess_int = -1;
              sscanf(bet_amount, "%d", &bet_amount_int);
              sscanf(bet_guess, "%d", &bet_guess_int);

              // check if the bet amount is an integer
              if (bet_amount_int <= 0 || bet_amount_int > account -> balance) {
                write(to_client, "invalid bet amount.\n", BUFFER_SIZE);
                continue;
              }

              int payout = play_flip(bet_amount_int);
              account -> balance += payout;

              write(to_client, "succesfully played flip", BUFFER_SIZE);

            } else if (strcmp(game_name, "dice") == 0) {
              char *bet_amount = strtok(NULL, " ");
              char *num_dice = strtok(NULL, " ");
              char *bet_guess = strtok(NULL, " ");

              int bet_amount_int = -1;
              int num_dice_int = -1;
              int bet_guess_int = -1;
              sscanf(bet_amount, "%d", &bet_amount_int);
              sscanf(num_dice, "%d", &num_dice_int);
              sscanf(bet_guess, "%d", &bet_guess_int);


              // check if the bet amount is an integer
              if (bet_amount_int <= 0 || bet_amount_int > account -> balance) {
                write(to_client, "invalid bet amount.\n", BUFFER_SIZE);
                continue;
              }

              int payout = play_dice(bet_amount_int, num_dice_int, bet_guess_int);
              account -> balance += payout;

              write(to_client, "succesfully played dice", BUFFER_SIZE);

            } else if (strcmp(game_name, "wheel") == 0) {
              char *num_spins = strtok(NULL, " ");

              int num_spins_int = -1;
              sscanf(num_spins, "%d", &num_spins_int);

              // check if the num spins is an integer
              
              if (num_spins_int <= 0) {
                write(to_client, "invalid spin amount.\n", BUFFER_SIZE);
                continue;
              }

              int * nums = play_wheel(num_spins_int);
              int payout = nums[num_spins_int - 1];
              account -> balance += payout;

              // HERE, SOMEHOW WRITE THE ARRAY TO THE CLIENT AND GIVE THEM THE FINAL NUMBER CLEARLY
              
              write(to_client, "succesfully played spin", BUFFER_SIZE);

            } else {
              write(to_client, "invalid game name", BUFFER_SIZE);
            }
          } else if (strcmp(command, "help") == 0) {
            // if command is "help"
            write(to_client, "help", BUFFER_SIZE);
          } else {
            write(to_client, "invalid command", BUFFER_SIZE);
          }
        } else {
          // IF NOT LOGGED IN:

          // check what the user is trying to do
          if (strcmp(command, "login") == 0) {
            // if command is "login" try to log in
            char *username = strtok(NULL, " ");
            char *password = strtok(NULL, " ");

            struct account * search = check_existance(username, file);

            // check if the user exists
            if (search != NULL) {
              // if the user exists, check if the password is correct
              if (strcmp(search -> password, password) == 0) {
                logged_in = 1;

                strncpy(account -> username, search -> username, sizeof(account -> username));
                strncpy(account -> password, search -> password, sizeof(account -> password));
                account -> balance = search -> balance;

                write(to_client, "logged in", BUFFER_SIZE);
              }
            } else {
              write(to_client, "account not found", BUFFER_SIZE);
            }

          } else if (strcmp(command, "create") == 0) {
            // if command is "create"
            char *username = strtok(NULL, " ");
            char *password = strtok(NULL, " ");

            struct account *search = check_existance(username, file);

            // check if the user exists
            if (search != NULL) {
              write(to_client, "account already exists", BUFFER_SIZE);
            } else {
              // create the user
              add_account(username, password, file);
              write(to_client, "account created", BUFFER_SIZE);
            }

          } else if (strcmp(command, "help") == 0) {
            // if command is "help"
            write(to_client, "help", BUFFER_SIZE);
          } else {
            write(to_client, "invalid command", BUFFER_SIZE);
          }
        }

      }
      exit(0);
    }

    printf("client has connected, but still waiting for new connections\n");
  }
  return 0;
}