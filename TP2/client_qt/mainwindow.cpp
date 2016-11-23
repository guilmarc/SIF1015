#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDir>
#include "loginscreen.h"
#include "receptioncontroller.h"
#include "user.h"
#include <string.h>

const QString MainWindow::TIME_FORMAT = "HH:mm:ss";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->transmissionController->connectToFifo();
    this->promptForLogin();
    ui->setupUi(this);
    this->transmissionListModel = new QStringListModel();
    this->receptionListModel = new QStringListModel();
    this->transmissionMessageList = new QStringList();
    this->receptionMessageList = new QStringList();
    ui->receptionView->setModel(this->receptionListModel);
    ui->transmissionView->setModel(this->transmissionListModel);
    connect(ui->commandInput, SIGNAL(returnPressed()), ui->sendButton, SIGNAL(clicked()));
    this->receptionController = new ReceptionController(this);
    this->transmissionController = new TransmissionController(this);
    this->displayPid();
    this->displayNickname();
    this->transmitLogin();
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
    QModelIndex indexOfTheCellIWant = transmissionListModel->index(transmissionListModel->rowCount() - 1);
    ui->transmissionView->setCurrentIndex(indexOfTheCellIWant);
}

void MainWindow::refreshReceptionList()
{
    this->receptionListModel->setStringList(*this->receptionMessageList);
}

void MainWindow::pushTransmissionResponse(QString message)
{
    this->pushMessageToTransmissionList(message);
}

void MainWindow::pushReceptionResponse(QString message)
{
    this->pushMessageToReceptionList(message);
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
    QString command = QString::fromStdString(User::getLoggedUser()->getAddCommand());
    this->sendCommand(command);
}

void MainWindow::sendCommand(QString command)
{
    QString message = this->getCurrentTime() + " > " + command;
    char transactionMessage[200];
    this->pushMessageToTransmissionList(message);
    QByteArray array = command.toLocal8Bit();
    strcpy(transactionMessage, array.data());
    this->transmissionController->send(transactionMessage);
}
