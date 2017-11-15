#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isConnected = 0;
    QString w = "w", a = "a", s = "s", d = "d", q = "q";

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_6_clicked();

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void connectionOK();

    void erro();

private:
    Ui::MainWindow *ui;
    Client *wifiClient;
};

#endif // MAINWINDOW_H
