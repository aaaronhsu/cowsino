#include "global.h"
#include "games.h"

int main() {
  
  int * nums = play_wheel(5);
  int i;
  for (i = 0; i < 5; i++) {
    printf("%d: %d\n", i, nums[i]);
  }
  return 0;
}