#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QCamera"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    camera(new Qcamera),
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

}

void MainWindow::on_Webcam_clicked()
{
    camera->setViewfinder(ui->screen);
    camera->start();
}
