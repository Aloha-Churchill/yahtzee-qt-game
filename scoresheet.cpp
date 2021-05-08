#include "scoresheet.h"

/*
 * Initializes all elements of score sheet to 0
 * */
ScoreSheet::ScoreSheet(){

    //initialize board
    score_tracker[ScoreType::ones] = 0;
    score_tracker[ScoreType::twos] = 0;
    score_tracker[ScoreType::threes] = 0;
    score_tracker[ScoreType::fours] = 0;
    score_tracker[ScoreType::fives] = 0;
    score_tracker[ScoreType::sixes] = 0;
    score_tracker[ScoreType::yahtzee] = 0;
    score_tracker[ScoreType::total] = 0;

}

/*
 * Sums elements to find total score;
 * */
int ScoreSheet::totalScore(){
    int sum = score_tracker[ScoreType::ones] + score_tracker[ScoreType::twos] +
            score_tracker[ScoreType::threes] + score_tracker[ScoreType::fours] +
            score_tracker[ScoreType::fives] + score_tracker[ScoreType::sixes] +
            score_tracker[ScoreType::yahtzee];

    return sum;
}
