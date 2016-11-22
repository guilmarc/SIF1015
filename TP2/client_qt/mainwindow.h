#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "transmissioncontroller.h"
#include "receptioncontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    static const QString TIME_FORMAT;

public:
    explicit MainWindow(QWidget *parent = 0);
    void refreshTransmissionList();
    void refreshReceptionList();
    void pushMessageToTransmissionList(QString text);
    void pushMessageToReceptionList(QString text);
    void displayPid();
    void displayNickname();
    void transmitLogin();
    void sendCommand(QString command);
    void promptForLogin();
    QString getCurrentTime();
    ~MainWindow();

private slots:
    void on_sendButton_clicked();

private:
    Ui::MainWindow *ui;
    TransmissionController* transmissionController;
    ReceptionController* receptionController;
    QStringList *receptionMessageList;
    QStringListModel *receptionListModel;
    QStringList *transmissionMessageList;
    QStringListModel *transmissionListModel;
};

#endif // MAINWINDOW_H
