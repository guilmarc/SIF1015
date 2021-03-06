#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QDialog>

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QDialog
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent = 0);
    ~LoginScreen();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LoginScreen *ui;
};

#endif // LOGINSCREEN_H
