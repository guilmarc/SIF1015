#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDir>
#include "loginscreen.h"
#include "receptioncontroller.h"
#include "user.h"
#include <string.h>
#include <QCloseEvent>
#include <QMessageBox>

const QString MainWindow::TIME_FORMAT = "HH:mm:ss";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->boot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::boot()
{
    this->initControllers();
    this->promptForLogin();
    this->initListModels();
    this->initLayout();
    this->receptionController->initRead();
    this->transmitLogin();
}

void MainWindow::initControllers()
{
    std::string receptionName = BaseController::getQualifiedClienFifoName(getpid());
    std::string transmissionName = SERVER_FIFO_NAME;
    this->receptionController = new ReceptionController(receptionName);
    this->transmissionController = new TransmissionController(transmissionName);
    this->receptionController->setContext(this);
    this->transmissionController->setContext(this);
}

void MainWindow::initLayout()
{
    this->displayPid();
    this->displayNickname();
    connect(ui->commandInput, SIGNAL(returnPressed()), ui->sendButton, SIGNAL(clicked()));
}

void MainWindow::initListModels()
{
    this->transmissionListModel = new QStringListModel();
    this->receptionListModel = new QStringListModel();
    this->transmissionMessageList = new QStringList();
    this->receptionMessageList = new QStringList();
    ui->receptionView->setModel(this->receptionListModel);
    ui->transmissionView->setModel(this->transmissionListModel);
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
    QModelIndex lastCellIndex = transmissionListModel->index(transmissionListModel->rowCount() - 1);
    ui->transmissionView->setCurrentIndex(lastCellIndex);
}

void MainWindow::refreshReceptionList()
{
    this->receptionListModel->setStringList(*this->receptionMessageList);
    QModelIndex lastCellIndex = receptionListModel->index(receptionListModel->rowCount() - 1);
    ui->receptionView->setCurrentIndex(lastCellIndex);
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
    ui->pidLabel->setText(QString("PID : %1").arg(getpid()));
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
    if(text.compare("quit") == 0) {
        this->close();
    } else {
        ui->commandInput->setText("");
        this->sendCommand(text);
    }
}

std::string MainWindow::getRemoveCommand()
{
    return "E " + User::getLoggedUser()->getNickname();
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

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton responseBtn = QMessageBox::question(this, "Client", tr("Êtes-vous sur de vouloir vous déconnecter?\n"),
                                                                QMessageBox::Cancel | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (responseBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        this->sendCommand(QString::fromStdString(this->getRemoveCommand()));
        this->receptionController->getFifo()->destroy();
        event->accept();
    }
}
