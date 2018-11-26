#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <csignal>
#include <iostream>
using namespace std;
#include <QApplication>
#include <QFileDialog>
#include <QVideoWidget>

static QString videoName;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sockDisc()
{
    socket->deleteLater();
}

void MainWindow::sockReady()
{
    if (socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        Data = socket->readAll();
        qDebug()<<Data;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    videoPlayer.show();
    this->hide();
}

void MainWindow::on_upload_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File (*.*)");
    ui->listWidget->addItem(filename);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString text = ui->listWidget->currentItem()->text();
    ui->title->setText(text);
}

void MainWindow::on_btn_Search_clicked()
{
    QString str = ui->text_Search->text();
    ui->listWidget->clear();
    if(str!=""){
        ui->text_Search->setText("");

        for(int i = 0; i< 30; i++){
            ui->listWidget->addItem(str);
        }
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    socket->connectToHost("192.168.1.120", 8080);
}
