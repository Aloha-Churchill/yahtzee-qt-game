#include "game.h"
#include "ui_game.h"
#include "scoresheet.h"
#include <cstdlib>
#include <QDebug>
#include <QInputDialog>
#include "player.h"
#include "roll.h"
#include <string>
#include <vector>
#include <map>
#include <QMessageBox>

/*
 * Global variables. Roll just has to be instantiated once.
 * */
std::vector<Player*> player_vector;
Roll *roll = new Roll();

/*
 * Initializes ui
 * */
Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

    //stylizing
    ui->dice_1->setStyleSheet("QPushButton{ background-color: red }");
    ui->dice_2->setStyleSheet("QPushButton{ background-color: red }");
    ui->dice_3->setStyleSheet("QPushButton{ background-color: red }");
    ui->dice4->setStyleSheet("QPushButton{ background-color: red }");
    ui->dice5->setStyleSheet("QPushButton{ background-color: red }");
    ui->magic_roll_button->setStyleSheet("QPushButton{ background-color: white }");
    ui->roll_button->setStyleSheet("QPushButton{ background-color: white }");


    //sign up users
    sign_in_modal = new SignUp();
    connect(sign_in_modal, SIGNAL(AddUser()), this, SLOT(addUserSlot()));

}

/*
 * Destructor
 * */
Game::~Game()
{
    delete ui;
    delete sign_in_modal;
    delete roll;

    //delete players + their score sheets
    for(int i = 0; i<(int)player_vector.size(); i++){
        delete[] player_vector[i];
    }
}

/*
 * Adds users to player vector from signup modal
 * */
void Game::addUserSlot(){
    qDebug() << "USERNAME: " << sign_in_modal->getUsernameString();
    std::string u_name = sign_in_modal->getUsernameString().toStdString();
    if(u_name == "computer"){
        //create new computer object
        ComputerPlayer *cp = new ComputerPlayer();
        cp->setId(player_vector.size());
        cp->setScoreSheet();
        cp->setUsername("computer");
        player_vector.push_back(cp);
    }
    else{
        //create new human object
        HumanPlayer *hp = new HumanPlayer();
        hp->setId(player_vector.size());
        hp->setScoreSheet();
        hp->setUsername(u_name);
        player_vector.push_back(hp);
    }
}


/*
 * shows sign up modal if clicked
 * */
void Game::on_sign_up_modal_button_clicked()
{
    sign_in_modal->show();

}

/*
 * Dice are re-rolled and labels are updated.
 * */
void Game::on_roll_button_clicked()
{
    roll->rollDice();

    //change labels
    std::string d1 = std::to_string(roll->dice_array_[0]->value);
    std::string d2 = std::to_string(roll->dice_array_[1]->value);
    std::string d3 = std::to_string(roll->dice_array_[2]->value);
    std::string d4 = std::to_string(roll->dice_array_[3]->value);
    std::string d5 = std::to_string(roll->dice_array_[4]->value);

    QString qs1(d1.c_str());
    QString qs2(d2.c_str());
    QString qs3(d3.c_str());
    QString qs4(d4.c_str());
    QString qs5(d5.c_str());

    ui->dice_label_1->setText(qs1);
    ui->dice_label_2->setText(qs2);
    ui->dice_label_3->setText(qs3);
    ui->dice_label_4->setText(qs4);
    ui->dice_label_5->setText(qs5);


    //logic checking to make sure player has not rolled too many times without bonus
    if(start && !extra_turn){
        num_rolls ++;
        if(num_rolls == 3){

            QMessageBox msgBox;
            msgBox.setText("You've hit you limit of rolls, please select a score now or loose your turn");
            msgBox.exec();
        }
        if(num_rolls > 3){
            QMessageBox msgBox;
            msgBox.setText("You've tried to roll too many times, next players turn");
            msgBox.exec();
            on_next_turn_button_clicked();
        }
    }

    //logic to make sure player has not rolled too many times with bonus (one extra roll)
    if(start && extra_turn){
        num_rolls ++;
        if(num_rolls == 4){
            QMessageBox msgBox;
            msgBox.setText("You've hit you limit of rolls, please select a score now or loose your turn");
            msgBox.exec();
        }
        if(num_rolls > 4){
            QMessageBox msgBox;
            msgBox.setText("You've tried to roll too many times, next players turn");
            msgBox.exec();
            on_next_turn_button_clicked();
        }
    }

}


/*
 * Methods below activate/inactivate dice to become "kept" dice or continue to be re-rolled
 * */
void Game::on_dice_1_clicked()
{
    if(roll->dice_array_[0]->roll_again == true){
        roll->dice_array_[0]->roll_again = false;
        ui->dice_1->setStyleSheet("QPushButton{ background-color: light gray }");
    }
    else{
        roll->dice_array_[0]->roll_again = true;
        ui->dice_1->setStyleSheet("QPushButton{ background-color: red }");
    }

}

void Game::on_dice_2_clicked()
{
    if(roll->dice_array_[1]->roll_again == true){
        roll->dice_array_[1]->roll_again = false;
        ui->dice_2->setStyleSheet("QPushButton{ background-color: light gray }");
    }
    else{
        roll->dice_array_[1]->roll_again = true;
        ui->dice_2->setStyleSheet("QPushButton{ background-color: red }");
    }

}

void Game::on_dice_3_clicked()
{
    if(roll->dice_array_[2]->roll_again == true){
        roll->dice_array_[2]->roll_again = false;
        ui->dice_3->setStyleSheet("QPushButton{ background-color: light gray }");
    }
    else{
        roll->dice_array_[2]->roll_again = true;
        ui->dice_3->setStyleSheet("QPushButton{ background-color: red }");
    }

}

void Game::on_dice4_clicked()
{
    if(roll->dice_array_[3]->roll_again == true){
        roll->dice_array_[3]->roll_again = false;
        ui->dice4->setStyleSheet("QPushButton{ background-color: light gray }");
    }
    else{
        roll->dice_array_[3]->roll_again = true;
        ui->dice4->setStyleSheet("QPushButton{ background-color: red }");
    }

}

void Game::on_dice5_clicked()
{
    if(roll->dice_array_[4]->roll_again == true){
        roll->dice_array_[4]->roll_again = false;
        ui->dice5->setStyleSheet("QPushButton{ background-color: light gray }");
    }
    else{
        roll->dice_array_[4]->roll_again = true;
        ui->dice5->setStyleSheet("QPushButton{ background-color: red }");
    }

}


/*
 * Updates total score label
 * */
void Game::updateTotalScore(){
    player_vector[current_player]->getScoreSheet()->setScore(ScoreType::total, (int)player_vector[current_player]->getScoreSheet()->totalScore());
    std::string t = "Total: "+ std::to_string(player_vector[current_player]->getScoreSheet()->totalScore());
    QString qst(t.c_str());
    ui->total_label->setText(qst);
}

/*
 * Computer player logic, computer only rolls once
 * and choose highest possible score each time --> simple greedy algorithm
 * */
void Game::computerTurn(){
    roll->rollDice();
    int highest_score = -1;
    int highest_num = 0;
    for(int i=1; i<7; i++){
        if(roll->upperScore(i) > highest_score){
            highest_score = roll->upperScore(i);
            highest_num = i;
        }
    }

    if(roll->yahtzee() > highest_score){
        highest_num = 7;
        highest_score = roll->yahtzee();
    }

    if(highest_num == 1){
        //set scoresheet
        player_vector[current_player]->getScoreSheet()->setScore(ScoreType::ones, highest_score);
    }
    else if(highest_num == 2){
       player_vector[current_player]->getScoreSheet()->setScore(ScoreType::twos, highest_score);
    }
    else if(highest_num == 3){
       player_vector[current_player]->getScoreSheet()->setScore(ScoreType::threes, highest_score);
    }
    else if(highest_num == 4){
       player_vector[current_player]->getScoreSheet()->setScore(ScoreType::fours, highest_score);
    }
    else if(highest_num == 5){
       player_vector[current_player]->getScoreSheet()->setScore(ScoreType::fives, highest_score);
    }
    else if(highest_num == 6){
       player_vector[current_player]->getScoreSheet()->setScore(ScoreType::sixes, highest_score);
    }
    else if(highest_num == 6){
       player_vector[current_player]->getScoreSheet()->setScore(ScoreType::yahtzee, highest_score);
    }
}

/*
 * Initializes game state
 * */
void Game::on_start_game_button_clicked()
{
    //dont allow users to sign up any more players
    ui->start_game_button->setVisible(false);
    ui->sign_up_modal_button->setVisible(false);
    ui->cover->setVisible(false);

    //since start is true, we start keeping score
    start = true;
    current_player = 0;
    num_rolls = 0;
    curr_num_turns = 0;
    limit_turns = 7*(int)player_vector.size() + 1;

    on_next_turn_button_clicked();

}

/*
 * Allows user to play turn or automates turn for computer player
 * keeps track of game state
 * */
void Game::on_next_turn_button_clicked()
{

    curr_num_turns ++;

    //updates player and player info
    current_player ++;
    if(current_player >= (int)player_vector.size()){
        current_player = 0;
    }

    num_rolls = 0;
    extra_turn = false;
    double_score = false;

    //sets dice to null value
    std::string dicestring = "-";
    QString qsdice(dicestring.c_str());
    ui->dice_label_1->setText(qsdice);
    ui->dice_label_2->setText(qsdice);
    ui->dice_label_3->setText(qsdice);
    ui->dice_label_4->setText(qsdice);
    ui->dice_label_5->setText(qsdice);


    //check if game is over
    if(curr_num_turns == limit_turns){
        //go through player vector and find out who has highest score
        int highest_score = -1;
        std::string highest_player = "";
        for(int i = 0; i<(int)player_vector.size();i++){
            if(player_vector[i]->getScoreSheet()->totalScore() > highest_score){
                highest_score = player_vector[i]->getScoreSheet()->totalScore();
                highest_player = player_vector[i]->getUsername();
            }
        }

        QMessageBox msgBox;
        msgBox.setText("Congrats to " + QString::fromStdString(highest_player) + "! You've won the game!");
        msgBox.exec();
        QApplication::quit();
    }

    //automates turn if computer player
    if(player_vector[current_player]->returnType() == "Computer"){
        //qmessage
        QMessageBox msgBox;
        msgBox.setText("It is the computer's turn, press ok to continue.");
        msgBox.exec();
        computerTurn();
        player_vector[current_player]->getScoreSheet()->setScore(ScoreType::total, (int)player_vector[current_player]->getScoreSheet()->totalScore());

        std::string computer_total = std::to_string(player_vector[current_player]->getScoreSheet()->totalScore());

        QMessageBox msgBox1;
        msgBox1.setText("The computer's score is now: " + QString::fromStdString(computer_total));
        msgBox1.exec();

        on_next_turn_button_clicked();

        return;
    }

    //update username that is displayed
    std::string u_name = "Username: "+ player_vector[current_player]->getUsername();
    QString qs1(u_name.c_str());
    ui->username_label->setText(qs1);
    //updateScoreSheet();

    //UPDATING SCORE SHEET
    std::string ones_score = "Score: " + std::to_string(player_vector[current_player]->getScoreSheet()->getScoreTracker()[ScoreType::ones]);
    QString q1 = (ones_score.c_str());
    ui->ones_label->setText(q1);
    update();

    std::string twos_score = "Score: " + std::to_string(player_vector[current_player]->getScoreSheet()->getScoreTracker()[ScoreType::twos]);
    QString q2 = (twos_score.c_str());
    ui->twos_label->setText(q2);
    update();

    std::string threes_score = "Score: " + std::to_string(player_vector[current_player]->getScoreSheet()->getScoreTracker()[ScoreType::threes]);
    QString q3 = (threes_score.c_str());
    ui->threes_label->setText(q3);
    update();

    std::string fours_score = "Score: " + std::to_string(player_vector[current_player]->getScoreSheet()->getScoreTracker()[ScoreType::fours]);
    QString q4 = (fours_score.c_str());
    ui->fours_label->setText(q4);
    update();

    std::string fives_score = "Score: " + std::to_string(player_vector[current_player]->getScoreSheet()->getScoreTracker()[ScoreType::fives]);
    QString q5 = (fives_score.c_str());
    ui->fives_label->setText(q5);
    update();

    std::string sixes_score = "Score: " + std::to_string(player_vector[current_player]->getScoreSheet()->getScoreTracker()[ScoreType::sixes]);
    QString q6 = (sixes_score.c_str());
    ui->sixes_label->setText(q6);
    update();

    std::string y_score = "Score: " + std::to_string(player_vector[current_player]->getScoreSheet()->getScoreTracker()[ScoreType::yahtzee]);
    QString qy = (y_score.c_str());
    ui->yahtzee_label->setText(qy);
    update();

    std::string total_score = "Total Score: " + std::to_string(player_vector[current_player]->getScoreSheet()->getScoreTracker()[ScoreType::total]);
    QString q7 = (total_score.c_str());
    ui->total_label->setText(q7);
    update();


    //updating checkboxes for score sheet
    if(player_vector[current_player]->check_1){
        //checkbox has button has already been clicked, dont do anything
        ui->ones_check->setCheckState(Qt::Checked);
    }
    else{
        ui->ones_check->setCheckState(Qt::Unchecked);
    }

    if(player_vector[current_player]->check_2){
        ui->twos_check->setCheckState(Qt::Checked);
    }
    else{
        ui->twos_check->setCheckState(Qt::Unchecked);
    }

    if(player_vector[current_player]->check_3){
        ui->threes_check->setCheckState(Qt::Checked);
    }
    else{
        ui->threes_check->setCheckState(Qt::Unchecked);
    }

    if(player_vector[current_player]->check_4){
        ui->fours_check->setCheckState(Qt::Checked);
    }
    else{
        ui->fours_check->setCheckState(Qt::Unchecked);
    }

    if(player_vector[current_player]->check_5){
        ui->fives_check->setCheckState(Qt::Checked);
    }
    else{
        ui->fives_check->setCheckState(Qt::Unchecked);
    }

    if(player_vector[current_player]->check_6){
        ui->sixes_check->setCheckState(Qt::Checked);
    }
    else{
        ui->sixes_check->setCheckState(Qt::Unchecked);
    }

    if(player_vector[current_player]->check_yahtzee){
        ui->yahtzee_check->setCheckState(Qt::Checked);
    }
    else{
        ui->yahtzee_check->setCheckState(Qt::Unchecked);
    }


    //update dice to be all not clicked again
    for(int i=0; i< 5; i++){
        roll->dice_array_[i]->roll_again = true;
    }
    //restylizing
    ui->dice_1->setStyleSheet("QPushButton{ background-color: red }");
    ui->dice_2->setStyleSheet("QPushButton{ background-color: red }");
    ui->dice_3->setStyleSheet("QPushButton{ background-color: red }");
    ui->dice4->setStyleSheet("QPushButton{ background-color: red }");
    ui->dice5->setStyleSheet("QPushButton{ background-color: red }");
    ui->magic_roll_button->setStyleSheet("QPushButton{ background-color: white }");


}

//generate random number
//60 percent of the time it will do nothing
//20 percent of the time it will give you double score
//20 percent of time it will let you roll again
void Game::on_magic_roll_button_clicked()
{
    srand((unsigned)time(0));
    int random_num = rand()%10+1; //random num between 1-10

    if(random_num == 1 || random_num == 2){
        ui->magic_roll_button->setStyleSheet("QPushButton{ background-color: blue }");
        QMessageBox msgBox;
        msgBox.setText("Congrats, you get extra roll!");
        msgBox.exec();
        extra_turn = true;

    }
    if(random_num == 3 || random_num == 4){
        ui->magic_roll_button->setStyleSheet("QPushButton{ background-color: yellow }");
        QMessageBox msgBox;
        msgBox.setText("Congrats, you get a double value bonus!");
        msgBox.exec();

        double_score = true;
    }
}


/*
 * Methods below change score of scoreboard and update board when score is chosen by player
 * */
void Game::on_ones_check_clicked()
{
    if(start){
        player_vector[current_player]->check_1 = true;

        int set_score = roll->upperScore(1);
        if(double_score){
            set_score = 2*roll->upperScore(1);
        }

        player_vector[current_player]->getScoreSheet()->setScore(ScoreType::ones, set_score);
        std::string d1 = "Score: "+ std::to_string(set_score);
        QString qs1(d1.c_str());
        ui->ones_label->setText(qs1);
        updateTotalScore();
    }
}

void Game::on_twos_check_clicked()
{
    if(start){
        player_vector[current_player]->check_2 = true;

        int set_score = roll->upperScore(2);
        if(double_score){
            set_score = 2*roll->upperScore(2);
        }

        player_vector[current_player]->getScoreSheet()->setScore(ScoreType::twos, set_score);
        std::string d1 = "Score: "+ std::to_string(set_score);

        QString qs1(d1.c_str());
        ui->twos_label->setText(qs1);
        updateTotalScore();
    }
}


void Game::on_threes_check_clicked()
{
    if(start){
        player_vector[current_player]->check_3 = true;
        int set_score = roll->upperScore(3);
        if(double_score){
            set_score = 2*roll->upperScore(3);
        }

        player_vector[current_player]->getScoreSheet()->setScore(ScoreType::threes, set_score);
        std::string d1 = "Score: "+ std::to_string(set_score);
        QString qs1(d1.c_str());
        ui->threes_label->setText(qs1);
        updateTotalScore();
    }

}

void Game::on_fours_check_clicked()
{
    if(start){
        player_vector[current_player]->check_4 = true;
        int set_score = roll->upperScore(4);
        if(double_score){
            set_score = 2*roll->upperScore(4);
        }

        player_vector[current_player]->getScoreSheet()->setScore(ScoreType::fours, set_score);
        std::string d1 = "Score: "+ std::to_string(set_score);
        QString qs1(d1.c_str());
        ui->fours_label->setText(qs1);
        updateTotalScore();
    }
}

void Game::on_fives_check_clicked()
{
    if(start){
        player_vector[current_player]->check_5 = true;
        int set_score = roll->upperScore(5);
        if(double_score){
            set_score = 2*roll->upperScore(5);
        }

        player_vector[current_player]->getScoreSheet()->setScore(ScoreType::fives, set_score);
        std::string d1 = "Score: "+ std::to_string(set_score);
        QString qs1(d1.c_str());
        ui->fives_label->setText(qs1);
        updateTotalScore();
    }

}

void Game::on_sixes_check_clicked()
{
    if(start){
        player_vector[current_player]->check_6 = true;
        int set_score = roll->upperScore(6);
        if(double_score){
            set_score = 2*roll->upperScore(6);
        }

        player_vector[current_player]->getScoreSheet()->setScore(ScoreType::sixes, set_score);
        std::string d1 = "Score: "+ std::to_string(set_score);
        QString qs1(d1.c_str());
        ui->sixes_label->setText(qs1);
        updateTotalScore();
    }

}

void Game::on_yahtzee_check_clicked()
{
    if(start){
        player_vector[current_player]->check_yahtzee = true;
        int set_score = roll->yahtzee();
        if(double_score){
            set_score = 2*roll->yahtzee();
        }

        player_vector[current_player]->getScoreSheet()->setScore(ScoreType::yahtzee, set_score);
        std::string d1 = "Score: "+ std::to_string(set_score);
        QString qs1(d1.c_str());
        ui->yahtzee_label->setText(qs1);
        updateTotalScore();
    }

}
