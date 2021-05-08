#ifndef SCORESHEET_H
#define SCORESHEET_H

#include <cstdlib>
#include <map>
#include <QObject>

#include "roll.h"

/*
 * Enum class for type of score
 * */
enum class ScoreType {ones, twos, threes, fours, fives, sixes, yahtzee, total};

/*
 * Score sheet keeps track of a player's overall score and score in each category.
 * */
class ScoreSheet : public QObject
{
public:
    ScoreSheet();
    int totalScore();

    //setter method
    void setScore(ScoreType t, int val){
        score_tracker[t] = val;
    }

    //getter method
    std::map<ScoreType, int> getScoreTracker(){
        return score_tracker;
    }

private:
    std::map<ScoreType, int> score_tracker;

};

#endif // SCORESHEET_H
