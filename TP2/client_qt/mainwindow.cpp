#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDir>
#include "loginscreen.h"
#include "user.h"

const QString MainWindow::TIME_FORMAT = "HH:mm:ss";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->promptForLogin();
    ui->setupUi(this);
    this->transmissionController = new TransmissionController();
    this->receptionController = new ReceptionController();
    this->transmissionListModel = new QStringListModel();
    this->receptionListModel = new QStringListModel();
    this->transmissionMessageList = new QStringList();
    this->receptionMessageList = new QStringList();
    ui->receptionView->setModel(this->receptionListModel);
    ui->transmissionView->setModel(this->transmissionListModel);
    connect(ui->commandInput, SIGNAL(returnPressed()), ui->sendButton, SIGNAL(clicked()));
    this->displayPid();
    this->displayNickname();
    this->transmitLogin();
    mkdir("./tmptest", 0777);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::promptForLogin()
{
    LoginScreen *dialog = new LoginScreen(this);
    dialog->setWindowTitle("Connexion");
    dialog->setModal(true);
    dialog->exec();
}

void MainWindow::refreshTransmissionList()
{
    this->transmissionListModel->setStringList(*this->transmissionMessageList);
}

void MainWindow::refreshReceptionList()
{
    this->receptionListModel->setStringList(*this->receptionMessageList);
}

void MainWindow::pushMessageToTransmissionList(QString text)
{
    this->transmissionMessageList->append(text);
    this->refreshTransmissionList();
}

void MainWindow::pushMessageToReceptionList(QString text)
{
    this->receptionMessageList->append(text);
    this->refreshReceptionList();
}

void MainWindow::displayPid()
{
    ui->pidLabel->setText(QString("PID : %1").arg(this->transmissionController->getPid()));
}

void MainWindow::displayNickname()
{
    QString nickname = QString::fromStdString(User::getLoggedUser()->getNickname());
    ui->nicknameLabel->setText(QString("Nickname : " + nickname));
}

QString MainWindow::getCurrentTime()
{
    QDateTime date = QDateTime::currentDateTime();
    return date.toString(MainWindow::TIME_FORMAT);
}

void MainWindow::on_sendButton_clicked()
{
    QString text = ui->commandInput->text();
    ui->commandInput->setText("");
    this->sendCommand(text);
}

void MainWindow::transmitLogin()
{
    char message[200] = "";
    strcpy(message, User::getLoggedUser()->getAddCommand().c_str());
    this->pushMessageToTransmissionList(QString(message));
    this->transmissionController->send(message);
}

void MainWindow::sendCommand(QString command)
{
    QString message = this->getCurrentTime() + " > " + command;
    this->pushMessageToTransmissionList(message);
    this->pushMessageToTransmissionList("Sending...");
    //  Do the transaction
    this->pushMessageToTransmissionList("Sent");
}
