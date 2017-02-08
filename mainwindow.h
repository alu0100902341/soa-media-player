#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QCamera"

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

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    QCamera* camera;

};

#endif // MAINWINDOW_H
