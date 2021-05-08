#include "roll.h"

/*
 * Roll constructor initializes all dice to value 1 and roll again value to true
 * it also puts all dice into the dice array.
 * */
Roll::Roll(){
    for(int i = 0; i<5; i++){
        Dice  *d = new Dice();
        d->value = 1;
        d->roll_again = true;
        dice_array_[i] = d;
    }
}


/*
 * This method re-rolls dice that are not kept by the player
 * */
void Roll::rollDice(){
    //seed random number generator
    srand((unsigned)time(0));
    for(int i = 0; i<5; i++){
        if(dice_array_[i]->roll_again == true){
            dice_array_[i]->value = rand()%6+1;
        }
    }
}

/*
 * Calculates the score for current dice for user choice.
 * Score = choice*(number of dice with value choice)
 * */
int Roll::upperScore(int choice){
    int sum = 0;
    for(int i=0; i<5; i++){
        if(dice_array_[i]->value == choice){
            sum += choice;
        }
    }
    return sum;
}

/*
 * If there is a yahtzee, then returns score of 50. Otherwise, returns score of 0.
 * */
int Roll::yahtzee(){
    int num_1 = dice_array_[0]->value;
    for(int i=1; i<5; i++){
        if(dice_array_[i]->value != num_1){
            return 0;
        }
    }
    return 50;
}
