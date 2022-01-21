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

int * play_wheel(int num_spins) {
  // right now, you can earn up to 1000 dollars
  int nums[] = {5, 10, 50, 100, 200, 500, 1000, 5000};
  srand(time(NULL));
  int r = rand() % 8; // returns a random num 0-7
  if (r > 2) r = rand() % 8; // if the value is higher than 50, then respin to make it less likely
  if (r > 4) r = rand() % 8; // more respins to make less likely
  if (r > 6) r = rand() % 8; // in this case, only if it is 7 will it get 5000
  int final = nums[r];

  int spins[num_spins];
  int i;
  for (i = 0; i < num_spins - 1; i++) {
    int index = rand() % 8;
    spins[i] = nums[index];
  }
  spins[num_spins - 1] = final;

  return spins;
}