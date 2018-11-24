#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QProgressBar>
#include <QSlider>

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

private slots:
    void on_actionopen_triggered();

private slots:
    void on_actionplay_triggered();
    
    void on_actionpause_triggered();
    
    void on_actionstop_triggered();

private:
    Ui::VideoPlayer *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QProgressBar* bar;
    QSlider* slider;

};

#endif // VIDEOPLAYER_H
