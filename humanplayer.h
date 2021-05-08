#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <string>
#include <scoresheet.h>


class HumanPlayer
{
public:
    HumanPlayer(std::string u_name, int id);
    std::string username;
    int player_id;
    ScoreSheet* player_scoresheet;
};

#endif // HUMANPLAYER_H
