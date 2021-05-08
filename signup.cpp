#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    //connects sign up button clicked to Add user signal
    ui->setupUi(this);
    connect(ui->sign_up_button, SIGNAL(clicked()), this, SIGNAL(AddUser()));
}

SignUp::~SignUp()
{
    delete ui;
}

/*
 * Class to allow main game class to get the user's username
 * */
QString SignUp::getUsernameString(){
    return ui->enter_username->text();
}
