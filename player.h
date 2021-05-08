#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include <scoresheet.h>
#include <QDebug>

/*
 * Simple enum for different types of players
 * */
enum PlayerType{Computer, Human};

/*
 * Player class keeps track of username, scoresheet, id, and check statuses for each player.
 * */
class Player
{
public:

    Player() {};
    virtual ~Player() {};

    virtual std::string returnType() = 0;

    void setUsername(std::string u_name){
        username = u_name;
    }
    void setId(int id){
        player_id = id;
    }
    void setScoreSheet(){
        player_scoresheet = new ScoreSheet();
    }

    std::string getUsername(){
        return username;
    }
    int getId(){
        return player_id;
    }
    ScoreSheet* getScoreSheet(){
        return player_scoresheet;
    }

    //check statuses help keep score sheet section of board check marks updated
    bool check_1 = false;
    bool check_2 = false;
    bool check_3 = false;
    bool check_4 = false;
    bool check_5 = false;
    bool check_6 = false;
    bool check_yahtzee = false;


protected:
    std::string username;
    int player_id;
    ScoreSheet* player_scoresheet;
};

/*
 * Inherited class, implements virtual returnType()
 * */
class ComputerPlayer : public Player
{
public:
    ComputerPlayer() {};

    std::string returnType(){
        qDebug() << "Computer";
        return "Computer";
    }

};

/*
 * Inherited class, implements virtual returnType()
 * */
class HumanPlayer : public Player
{
public:
    HumanPlayer() {};

    std::string returnType(){
        qDebug() << "Human";
        return "Human";
    }
};

#endif // PLAYER_H
