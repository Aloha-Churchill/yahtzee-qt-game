#ifndef VIEWSCORESHEET_H
#define VIEWSCORESHEET_H

#include <QDialog>
#include "scoresheet.h"
#include "roll.h"

namespace Ui {
class ViewScoreSheet;
}

class ViewScoreSheet : public QDialog
{
    Q_OBJECT

public:
    explicit ViewScoreSheet(QWidget *parent = nullptr);
    ~ViewScoreSheet();

private slots:
    void on_ones_check_stateChanged(int arg1);

signals:
    void scoreChanged(ScoreType t);

private:
    Ui::ViewScoreSheet *ui;

    //checked
    bool check_1 = false;

};

#endif // VIEWSCORESHEET_H
