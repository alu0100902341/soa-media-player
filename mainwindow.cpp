#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    camera(new QCamera),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Forward_clicked()
{

}

void MainWindow::on_Stop_clicked()
{

}

void MainWindow::on_Rewind_clicked()
{

}

void MainWindow::on_Playpause_clicked()
{
    if (ui->Playpause->text()=="Play")
        ui->Playpause->setText("Pause");
    else
        ui->Playpause->setText("Play");
}

void MainWindow::on_Webcam_clicked()
{
    camera->setViewfinder(ui->screen);
    camera->start();

    if (camera->ActiveState){
        camera->stop();
    }else{
        camera->start();
    }

}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionImport_triggered()
{

}
