#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QProgressBar>
#include <QSlider>
#include "videoplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static void startClient();
    void setVideoName(QString name);
    static QString getVideoName();


private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

    void on_upload_clicked();

    void on_pushButton_4_clicked();

private:
    QString video_Name;
    Ui::MainWindow *ui;
    VideoPlayer videoPlayer;
};

#endif // MAINWINDOW_H
