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
        
        char * line = buffer;
        // printf("entire line: %s\n", line);
        char ** args = calloc(2, sizeof(char *));
        args[0] = line;
        if (strsep(&line, " ") != NULL) args[1] = line;
 
        char *command = args[0];
        char *stuff_after = args[1];

        // printf("the primary command is: %s\n", command);
        // printf("the arguments are: %s\n", stuff_after);

        // if "exit", then exit
        if (strcmp(command, "exit") == 0) {
          printf("THE EXIT FUNCTION IS BEING RUN!!!\n");
          update_balance(account -> username, account -> balance, file);
          exit_function(to_client, buffer, account);
          break;
        } else if (strcmp(command, "help") == 0) {
          printf("THE HELP FUNCTION IS BEING RUN!!!\n");
          help_function(to_client, logged_in);
          continue;
        }

        // check if the user is logged in
        if (logged_in) {
          if (strcmp(command, "balance") == 0) {

            balance_function(to_client, account);

          } else if (strcmp(command, "play") == 0) {
            char ** game_holder = calloc(2, sizeof(char *));
            game_holder[0] = stuff_after;
            if (strsep(&stuff_after, " ") != NULL) game_holder[1] = stuff_after;

            char *game_name = game_holder[0];
            char *game_args = game_holder[1];

            if (game_args == NULL) {
              write(to_client, "USAGE:\nplay flip <amount> <heads/tails>\nplay dice <amount> <number of dice> <sum guess>\nplay wheel <amount spun>\n", BUFFER_SIZE);
              continue;
            }

            if (strcmp(game_name, "flip") == 0) {
              char ** bet_info = calloc(2, sizeof(char *));
              bet_info[0] = game_args;
              if (strsep(&game_args, " ") != NULL) bet_info[1] = game_args;
              
              char *bet_amount = bet_info[0];
              char *bet_guess = bet_info[1];
              // printf("bet amount: %s\n", bet_amount);

              if (bet_guess == NULL || strchr(bet_guess, ' ') != NULL) {
                write(to_client, "USAGE:\nplay flip <amount> <heads/tails>\n", BUFFER_SIZE);
                continue;
              }

              int bet_amount_int = -1;

              // doesn't use bet guess, it's just to make it immersive
              int bet_guess_int = -1;
              sscanf(bet_amount, "%d", &bet_amount_int);
              // printf("bet amount int: %d\n", bet_amount_int);

              // check if the bet amount is an integer
              if (bet_amount_int <= 0 || bet_amount_int > account -> balance) {
                write(to_client, "Please enter a valid bet amount\n", BUFFER_SIZE);
                continue;
              }

              int payout = play_flip(bet_amount_int);
              account -> balance += payout;
              update_balance(account -> username, account -> balance, file);

              if (payout >= 0) { 
                write(to_client, "You guessed the flip correctly and won your bet!\n", BUFFER_SIZE);
              } else {
                write(to_client, "Oh no! You lost your bet... Try again!\n", BUFFER_SIZE);
              }

            } else if (strcmp(game_name, "dice") == 0) {
              char ** bet_info = calloc(3, sizeof(char *));
              bet_info[0] = game_args;
              if (strsep(&game_args, " ") != NULL) bet_info[1] = game_args;
              if (strsep(&game_args, " ") != NULL) bet_info[2] = game_args;

              if (bet_info[0] == NULL || bet_info[1] == NULL || bet_info[2] == NULL || strchr(bet_info[2], ' ') != NULL) {
                write(to_client, "USAGE:\nplay dice <amount> <number of dice> <sum guess>\n", BUFFER_SIZE);
                continue;
              }

              char *bet_amount = bet_info[0];
              char *num_dice = bet_info[1];
              char *bet_guess = bet_info[2];

              int bet_amount_int = -1;
              int num_dice_int = -1;
              int bet_guess_int = -1;
              sscanf(bet_amount, "%d", &bet_amount_int);
              sscanf(num_dice, "%d", &num_dice_int);
              sscanf(bet_guess, "%d", &bet_guess_int);


              // check if the bet amount is an integer
              if (bet_amount_int <= 0 || bet_amount_int > account -> balance) {
                write(to_client, "Please enter a valid bet amount\n", BUFFER_SIZE);
                continue;
              }

              int payout = play_dice(bet_amount_int, num_dice_int, bet_guess_int);
              account -> balance += payout;
              update_balance(account -> username, account -> balance, file);


              if (payout > 0) { 
                write(to_client, "You guessed the sum correctly and won 3 times your bet!\n", BUFFER_SIZE);
              } else {
                write(to_client, "Oh no! You lost your bet... Try again!\n", BUFFER_SIZE);
              }

            } else if (strcmp(game_name, "wheel") == 0) {
              // game_args is the info
              if (strchr(game_args, ' ') != NULL) {
                write(to_client, "USAGE:\nplay wheel <amount spun>\n", BUFFER_SIZE);
                continue;
              }

              char *num_spins = game_args;

              int num_spins_int = -1;
              sscanf(num_spins, "%d", &num_spins_int);

              // check if the num spins is an integer
              
              if (num_spins_int <= 0) {
                write(to_client, "Please enter a valid number of spins.\n", BUFFER_SIZE);
                continue;
              }

              int * nums = play_wheel(num_spins_int);
              int payout = nums[num_spins_int - 1];
              account -> balance += payout;
              update_balance(account -> username, account -> balance, file);


              // HERE, SOMEHOW WRITE THE ARRAY TO THE CLIENT AND GIVE THEM THE FINAL NUMBER CLEARLY
              
              if (payout > 0) { 
                write(to_client, "You have won!\n", BUFFER_SIZE);
              } else {
                write(to_client, "Oh no! You lost. Try again!\n", BUFFER_SIZE);
              }

            } else {
              write(to_client, "USAGE:\nplay flip <amount> <heads/tails>\nplay dice <amount> <number of dice> <sum guess>\nplay wheel <amount spun>\n", BUFFER_SIZE);
            }
          } else if (strcmp(command, "help") == 0) {
            // if command is "help"
            write(to_client, "help", BUFFER_SIZE);
          } else {
            printf("CLIENT TRIED TO RUN SOMETHING THAT DOESN'T EXIST WHILE LOGGED IN\n");
            write(to_client, "invalid command\n", BUFFER_SIZE);
          }
        } else {
          // IF NOT LOGGED IN:

          // check what the user is trying to do
          if (strcmp(command, "login") == 0) {
            // if command is "login" try to log in
            printf("THE CLIENT IS TRYING TO LOG IN!!!\n");

            printf("login info: %s\n", stuff_after);
            char ** user_pass = calloc(2, sizeof(char *));
            args[0] = stuff_after;
            if (strsep(&stuff_after, " ") != NULL) args[1] = stuff_after;

            char *username = args[0];
            char *password = args[1];

            char *temp_check = args[1];
            if (temp_check == NULL || strchr(temp_check, ' ') != NULL) {
              printf("wrong number of login arguments\n");
              write(to_client, "login takes in 2 arguments- username and password", BUFFER_SIZE);
              continue;
            }

            printf("%s %s\n", username, password);

            struct account * search = check_existance(username, file);

            // check if the user exists
            if (search != NULL) {
              // if the user exists, check if the password is correct
              if (strcmp(search -> password, password) == 0) {
                logged_in = 1;

                strncpy(account -> username, search -> username, sizeof(account -> username));
                strncpy(account -> password, search -> password, sizeof(account -> password));
                account -> balance = search -> balance;

                char * welcome_message = malloc(BUFFER_SIZE);
                sprintf(welcome_message, "Welcome back, %s! You have %d moonies.\n", account -> username, account -> balance);

                write(to_client, welcome_message, BUFFER_SIZE);
              }
            } else {
              write(to_client, "Account not found", BUFFER_SIZE);
            }

          } else if (strcmp(command, "create") == 0) {
            // if command is "create"
            printf("THE CLIENT IS TRYING TO CREATE AN ACCOUNT!!!\n");

            // printf("create account info: %s\n", stuff_after);
            char ** user_pass = calloc(2, sizeof(char *));
            args[0] = stuff_after;
            if (strsep(&stuff_after, " ") != NULL) args[1] = stuff_after;

            char *username = args[0];
            char *password = args[1];

            char *temp_check = args[1];
            if (temp_check == NULL || strchr(temp_check, ' ') != NULL) {
              // printf("wrong number of create account arguments\n");
              write(to_client, "USAGE:create <username> <password>\n", BUFFER_SIZE)
              continue;
            }

            printf("%s %s\n", username, password);
            
            struct account *search = check_existance(username, file);

            // check if the user exists
            if (search != NULL) {
              write(to_client, "This account already exists. Try logging in.\n", BUFFER_SIZE);
            } else {
              // create the user
              add_account(username, password, file);
              write(to_client, "The account has been created!\n", BUFFER_SIZE);
            }

          } else {
            printf("CLIENT TRIED TO RUN SOMETHING THAT DOESN'T EXIST WHILE NOT LOGGED IN\n");
            write(to_client, "USAGE:\nlogin <username> <password>\ncreate <username> <password>\n", BUFFER_SIZE);
          }
        }

      }
      exit(0);
    }

    printf("client has connected, but still waiting for new connections\n");
  }
  return 0;
}