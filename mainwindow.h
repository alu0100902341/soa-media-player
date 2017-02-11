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
    void on_Forward_clicked();

    void on_Stop_clicked();

    void on_Rewind_clicked();

    void on_Playpause_clicked();

    void on_Webcam_clicked();


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QCamera* camera;

};

#endif // MAINWINDOW_H
