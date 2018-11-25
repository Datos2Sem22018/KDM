#include "videoplayer.h"
#include "ui_videoplayer.h"

#include <QFileDialog>
#include <QVideoWidget>
#include "mainwindow.h"

VideoPlayer::VideoPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    this->setCentralWidget(vw);

    slider = new QSlider(this);
    bar = new QProgressBar(this);
    slider->setOrientation(Qt::Horizontal);

    ui->stBar->addPermanentWidget(slider);
    ui->stBar->addPermanentWidget(bar);

    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);

    connect(player, &QMediaPlayer::durationChanged, bar, &QProgressBar::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, bar, &QProgressBar::setValue);
}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

void VideoPlayer::on_actionplay_triggered()
{
    player->play();
    ui->stBar->showMessage("Playing");
}

void VideoPlayer::on_actionpause_triggered()
{
    player->pause();
    ui->stBar->showMessage("Paused");
}

void VideoPlayer::on_actionstop_triggered()
{
    player->stop();
    ui->stBar->showMessage("Stopped");
}

void VideoPlayer::on_actionopen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File (*.*)");
    on_actionstop_triggered();

    player->setMedia(QUrl::fromLocalFile(MainWindow::getVideoName()));
    on_actionplay_triggered();
}
