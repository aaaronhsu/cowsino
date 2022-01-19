#include "pipe_networking.h"
#include "server_functions.h"


int main() {
  int to_client;
  int from_client;
  int f;

  printf("server starting...\n");

  while (1) {

    from_client = server_setup();

    f = fork();
    if (f) {
      close(from_client);
    } else {
      to_client = server_connect(&from_client);

      // struct account here (check all the data stuff)
      char *file = "accounts.txt";
      struct account *account = malloc(sizeof(struct account));
      int logged_in = 0;

      char buffer[BUFFER_SIZE];
      while (read(from_client, buffer, BUFFER_SIZE)) {

        // parse the buffer
        char *command = strtok(buffer, " ");

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

              // check if the bet amount is an integer
              int bet_amount_int = atoi(bet_amount);
              if (bet_amount_int <= 0 || bet_amount_int > account -> balance) {
                write(to_client, "invalid bet amount.\n", BUFFER_SIZE);
                continue;
              }

              int payout = play_flip(bet_amount);
              account -> balance += payout;

              write(to_client, "succesfully played flip", BUFFER_SIZE);

            } else if (strcmp(game_name, "dice") == 0) {
              char *bet_amount = strtok(NULL, " ");
              char *num_dice = strtok(NULL, " ");
              char *bet_guess = strtok(NULL, " ");


              // check if the bet amount is an integer
              int bet_amount_int = atoi(bet_amount);
              if (bet_amount_int <= 0 || bet_amount_int > account -> balance) {
                write(to_client, "invalid bet amount.\n", BUFFER_SIZE);
                continue;
              }

              int payout = play_dice(bet_amount, num_dice, bet_guess);
              account -> balance += payout;

              write(to_client, "succesfully played dice", BUFFER_SIZE);

            } else if (strcmp(game_name, "wheel") == 0) {
              char *num_spins = strtok(NULL, " ");

              // check if the num spins is an integer
              int num_spins_int = atoi(bet_amount);
              if (num_spins_int <= 0) {
                write(to_client, "invalid spin amount.\n", BUFFER_SIZE);
                continue;
              }

              int payout = play_wheel(num_spins);
              account -> balance += payout;

              write(to_client, "succesfully played spin", BUFFER_SIZE);

            } else {
              write(to_client, "invalid game name", BUFFER_SIZE);
            }
          } else if (strcmp(command, "help") == 0) {
            // if command is "help"
            write(to_client, "help", BUFFER_SIZE);
          }
        } else {
          // check what the user is trying to do
          if (strcmp(command, "login") == 0) {
            // if command is "login" try to log in
            char *username = strtok(NULL, " ");
            char *password = strtok(NULL, " ");

            struct account *check_existance = check_existance(username, password, file);

            // check if the user exists
            if (account != NULL) {
              // if the user exists, check if the password is correct
              if (strcmp(check_existance -> password, password) == 0) {
                logged_in = 1;

                account -> username = check_username -> username;
                account -> password = check_existance -> password;
                account -> balance = check_existance -> balance;

                write(to_client, "logged in", BUFFER_SIZE);
              }
            } else {
              write(to_client, "account not found", BUFFER_SIZE);
            }

          } else if (strcmp(command, "create") == 0) {
            // if command is "create"
            char *username = strtok(NULL, " ");
            char *password = strtok(NULL, " ");

            struct account *check_existance = check_existance(username, password, file);

            // check if the user exists
            if (check_existance != NULL) {
              write(to_client, "account already exists", BUFFER_SIZE);
            } else {
              // create the user
              add_account(username, password, file);
              write(to_client, "account created", BUFFER_SIZE);
            }

          } else if (strcmp(command, "help") == 0) {
            // if command is "help"
            write(to_client, "help", BUFFER_SIZE);
          }

      }
      exit(0);
    }

    printf("client has connected, but still waiting for new connections\n");
  }
  return 0;
}