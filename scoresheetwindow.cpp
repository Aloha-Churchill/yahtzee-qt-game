#include "scoresheetwindow.h"
#include "ui_scoresheetwindow.h"

ScoreSheetWindow::ScoreSheetWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScoreSheetWindow)
{
    ui->setupUi(this);
}

ScoreSheetWindow::~ScoreSheetWindow()
{
    delete ui;
}
