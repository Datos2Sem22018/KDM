#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QVideoWidget>

static QString videoName;

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
    videoName = str;
    ui->lineEdit->setText("Buscando: " + videoName);

    for(int i = 0; i< 30; i++){
        ui->listWidget->addItem(videoName);

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
