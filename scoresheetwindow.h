#ifndef SCORESHEETWINDOW_H
#define SCORESHEETWINDOW_H

#include <QMainWindow>

namespace Ui {
class ScoreSheetWindow;
}

class ScoreSheetWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScoreSheetWindow(QWidget *parent = nullptr);
    ~ScoreSheetWindow();

private:
    Ui::ScoreSheetWindow *ui;
};

#endif // SCORESHEETWINDOW_H
