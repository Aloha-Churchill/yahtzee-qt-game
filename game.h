#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <string>

#include "signup.h"
#include "roll.h"
#include "scoresheet.h"
#include "player.h"

/*
 * Game is the main window and the majority of the program. It keeps track of players, number of turns, and
 * state of play in general.
 * */
QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

    void updateScoreSheet();
    void nextTurn();
    void updateTotalScore();
    void computerTurn();



public slots:
    void addUserSlot();

private slots:
    void on_roll_button_clicked();
    void on_dice_1_clicked();
    void on_dice_2_clicked();
    void on_dice_3_clicked();
    void on_dice4_clicked();
    void on_dice5_clicked();
    void on_sign_up_modal_button_clicked();
    void on_start_game_button_clicked();
    void on_next_turn_button_clicked();
    void on_magic_roll_button_clicked();
    void on_ones_check_clicked();
    void on_twos_check_clicked();
    void on_threes_check_clicked();
    void on_fours_check_clicked();
    void on_fives_check_clicked();
    void on_sixes_check_clicked();
    void on_yahtzee_check_clicked();

private:
    Ui::Game *ui;
    SignUp *sign_in_modal;

    //indicates whether game has been started
    bool start = false;

    //keeps track of number of rolls each player has per turn
    int num_rolls = 0;

    //keeps track of current player's id
    int current_player;

    //keeps track if player has gotten an extra turn
    bool extra_turn = false;

    //keeps track if player has gotten a double score
    bool double_score = false;

    //variables to end game after appropriate amount of rounds
    int limit_turns;
    int curr_num_turns;

};
#endif // GAME_H
