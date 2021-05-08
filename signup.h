#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

/*
 * SignUp allows players to type in username or create computer players to play the game
 * */
namespace Ui {
class SignUp;
}
class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    QString getUsernameString();
    ~SignUp();


signals:
    void AddUser();

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
