#ifndef GAMES_H
#define GAMES_H

/*

play flip(money you are betting, whether you think it's heads or tails)
- returns -+ the money you are betting

play dice (money you betting, number dice, sum guess)
- returns +- the money you are betting

play wheel(number of spins [size of the end array])
- the wheel is just a list of +- numbers 
- returns a list of numbers that you spun so they can be rendered in the terminal

check wheel
- returns the amount you actually got 



*/

int play_flip(int money);
int play_dice(int money, int num_dice, int sum_guess);
int play_wheel(int num_spins);

#endif