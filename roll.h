#ifndef ROLL_H
#define ROLL_H

#include <cstdlib>
#include <ctime>

/*
 * Each dice has value from 1-6 and is in either a roll again or keep state
 * */
struct Dice{
    int value;
    bool roll_again;
};

/*
 * Roll class allows dice to be pseudo-randomly rolled and
 * calculates different scores for the rolled dice.
 * */
class Roll
{
public:
    Roll();
    void rollDice();
    int upperScore(int choice);
    int yahtzee();
    Dice* dice_array_[5];


};

#endif // ROLL_H
