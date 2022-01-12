# cowsino
Aaron Hsu & Eliza Knapp (Period 5)


## Description of Project
Cowsino is a casino where users can log into a server to gamble *currency* by playing simple text-based chance games. User data (username, password, balance) is stored in a file system and multiple users can interact with the cowsino at a time.

The *currency* is not yet named.


## UI

### Interface
On client connect, the user will be prompted to either log in or create an account. After a user sucessfully logs in (by entering a valid username and corresponding password stored in a file system), they will be able to spend their *currency* to play an assortment of text-based chance games that can earn them *currency*. When the user disconnects, the amount of *currency* they own is updated in the server.

### List of commands that can be run:
- `login <username> <password>`: Logs in a user with the given username and password.
- `create <username> <password>`: Creates a new user with the given username and password.
- `balance`: Displays the current balance of the user.
- `play flip <amount> <heads/tails>`: Plays a coinflip game, betting the given amount of *currency* on the given side of the coin.
- `play dice <amount> <number of dice> <sum guess>`: Plays a dice game, betting the given amount of *currency* on the sum of the dice. The closer the user's guess is to actual sum, the higher the payout.
- `exit`: Exits the program.
- `help`: Displays a list of commands that can be run.


## Technical Design

### Topics
- **Allocating memory**: To create structs that store user data and store the game data.
- **Working with files**: User data will be stored in files as structs.
- **Finding information about files**: User data wil be fetched from files on user connect/disconnect.
- **Processes**: Forking processes to have multiple clients connect at a time.
- **Semaphores**: Ensure that a client isn't logged into the server through multiple terminals at the same time.
- **Pipes**: To communicate between the server and the client.
- **Sockets**: If we decide to implement multiplayer games.

### Data Structures/Methods
- User struct: (char * username, char * password, int balance)
- We will be building off of assignments 22/23 to establish client/server communication (3 step handshake, forking processes, and pipes)

### Project Breakdown
- **Aaron**: Parse user input and execute commands with parameters. Implement game logic and modify variables that relate to the game.
- **Eliza**: Create structs and store/retrieve user data from files.

## Project Timeline (due 1/21)
- **1/13**: Start with previous assignment.
- **1/14**: Parse user input (serverside) and run (empty) functions with parameters. Store user data locally within the program.
- **1/17**: Implement user struct and login system (by reading/writing to files). Create a coinflip game.
- **1/18**: MVP (current description of the project)
- **1/19**: Semaphores to make sure that a client isn't logged into the server through multiple terminals at the same time.
- **1/20**: Implement dice game and fix bugs.

If the project is completed on time and the deadline is after 1/21, more games can be implemented.