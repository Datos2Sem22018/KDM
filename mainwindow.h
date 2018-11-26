#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QProgressBar>
#include <QSlider>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
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

    QTcpSocket* socket;
    QByteArray Data;

public slots:
    void sockReady();
    void sockDisc();

private slots:
    void on_pushButton_3_clicked();
    void on_upload_clicked();
    void on_pushButton_4_clicked();
    void on_btn_Search_clicked();

    void on_pushButton_2_clicked();

private:
    static QString video_Name;
    Ui::MainWindow *ui;
    VideoPlayer videoPlayer;
};

#endif // MAINWINDOW_H
