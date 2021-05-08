#include "viewscoresheet.h"
#include "ui_viewscoresheet.h"
#include "QDebug"
#include "scoresheet.h"

ViewScoreSheet::ViewScoreSheet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewScoreSheet)
{
    ui->setupUi(this);
}

ViewScoreSheet::~ViewScoreSheet()
{
    delete ui;
}

void ViewScoreSheet::on_ones_check_stateChanged(int arg1)
{
    if(check_1){
        //checkbox has button has already been clicked, dont do anything
        ui->ones_check->setCheckState(Qt::Checked);
        return;
    }
    else{
        check_1 = true;
        emit scoreChanged(ScoreType::ones);
        //sends a signal to a custom slot to change score sheet
        //update this players score sheet to reflect a change
        //change score sheet
        //update();
    }

}
