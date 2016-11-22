#include "loginscreen.h"
#include "ui_loginscreen.h"
#include "user.h"

LoginScreen::LoginScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::on_buttonBox_accepted()
{
    User::logUser(ui->nicknameInput->text().toStdString(), ui->specialtyInput->text().toStdString(), ui->scholarshipsInput->text().toStdString(), ui->experiencesSpinInput->text().toInt());
}

