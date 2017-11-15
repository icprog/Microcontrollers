#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("192.168.0.100");
    ui->lineEdit_2->setText("4000");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() // conexao
{
    this->wifiClient = new Client(ui->lineEdit->text(),ui->lineEdit_2->text().toInt());
    connect(this->wifiClient,SIGNAL(connectionSuccessful()),this,SLOT(connectionOK()));
}

void MainWindow::on_pushButton_2_pressed() // parado
{
    if(isConnected)
    {
        ui->textEdit->append("Frente.");
        this->wifiClient->writeData(w);
    }
    else
    {
        erro();
    }
}

void MainWindow::on_pushButton_3_pressed() //parado
{
    if(isConnected)
    {
        ui->textEdit->append("Parado.");
        this->wifiClient->writeData(q);
    }
    else
    {
        erro();
    }
}

void MainWindow::on_pushButton_6_clicked() // Direita
{
    if(isConnected)
    {
        ui->textEdit->append("Direita.");
        this->wifiClient->writeData(d);
    }
    else
    {
        erro();
    }
}

void MainWindow::on_pushButton_4_pressed() // ré
{
    if(isConnected)
    {
        ui->textEdit->append("Ré.");
        this->wifiClient->writeData(s);
    }
    else
    {
        erro();
    }
}

void MainWindow::on_pushButton_5_pressed() // esquerda
{
    if(isConnected)
    {
        ui->textEdit->append("Esquerda.");
        this->wifiClient->writeData(a);
    }
    else
    {
        erro();
    }
}

void MainWindow::connectionOK()
{
    ui->textEdit->append("Conectado!");
    isConnected = 1;
}

void MainWindow::erro()
{
   ui->textEdit->append("Favor estabelecer conexão!");
}
