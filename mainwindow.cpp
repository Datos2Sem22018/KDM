#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <csignal>
#include "clientsocket.h"

#include <QApplication>
#include <QFileDialog>
#include <QVideoWidget>

static QString videoName;

void MainWindow::setVideoName(QString name){
    video_Name = name;
}

QString MainWindow::getVideoName(){
    return video_Name;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    videoPlayer.show();
    this->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str = ui->lineEdit->text();
    video_Name = str;
    ui->lineEdit->setText("Buscando: " + video_Name);

    for(int i = 0; i< 30; i++){
        ui->listWidget->addItem(video_Name);

    }
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
ClientSocket tcp;

void sig_exit(int s)
{
    tcp.exit();
    exit(0);
}

void MainWindow::startClient(){
    signal(SIGINT, sig_exit);

        tcp.setup("192.168.1.134",8080);
        while(1)
        {
            srand(time(NULL));
            tcp.Send(to_string(rand()%25000));
            string rec = tcp.receive();
            if( rec != "" )
            {
                cout << "Server Response:" << rec << endl;
            }
            sleep(1);
        }
}
