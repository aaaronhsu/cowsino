#include "games.h"
#include "global.h"

int play_flip(int money) {
  // return random boolean value
  srand(time(NULL));
  int r = rand() % 2;
  return (r) ? money : -money;
}

int play_dice(int money, int num_dice, int sum_guess) {
  // return random boolean value
  int sum = 0;
  for (int i = 0; i < num_dice; i++) {
    sum += rand() % 6 + 1;
  }
  return (sum == sum_guess) ? money : -money;
}

int play_wheel(int num_spins) {
  return 0;
}