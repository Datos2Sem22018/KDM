#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <csignal>
#include "clientsocket.h"

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
        connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::sockDisc(){
    socket->abort();
    socket->deleteLater();
}

void MainWindow::sockReady(){
    if(socket->waitForConnected(500)){
        socket->waitForReadyRead(500);
        Data = socket->readAll();

        doc = QJsonDocument::fromJson(Data, &docError);

        if(docError.errorString().toInt()==QJsonParseError::NoError){
            if((doc.object().value("type").toString() == "connect") && (doc.object().value("status").toString() == "yes")){
                QMessageBox::information(this, "Conectado","Coneccion exitosa");
            }else{
                QMessageBox::information(this, "No se ha consultado conectar","Intentar de nuevo");
            }
        }else{
            QMessageBox::information(this, "No se ha podido conectar","Ha habido un error: " + docError.errorString());
        }
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
    socket->connectToHost("192.168.1.120", 5555);
}
