#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QCamera>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QCameraInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_Stop_clicked();
    void on_Playpause_clicked();
    void on_Webcam_clicked();
    void create_menus();
    void increase3();
    void Normal();
    void increase1();
    void increase2();
    void decrease1();
    void decrease2();
    void Speed(qreal real);

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QCamera* camera;
    QMenu* speed_menu_forward;
    QMenu* speed_menu_rewind;
    QCameraInfo* infocamera;
};

#endif // MAINWINDOW_H
