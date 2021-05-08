#include "humanplayer.h"

HumanPlayer::HumanPlayer(std::string u_name, int id)
{
    this->username = u_name;
    this->player_id = id;
    this->player_scoresheet = new ScoreSheet();
}
