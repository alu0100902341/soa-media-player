#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(new QMediaPlayer),
    camera(new QCamera)
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

    if ((camera->state() == camera->ActiveState) || (player->NoMedia)){


        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), QString(),
            tr("Video Files (*.mp4);"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"),
                    tr("Could not open file"));
                return;
            }

            player->setVideoOutput(ui->screen);
            player->setMedia(QUrl::fromLocalFile(fileName));
            ui->screen->show();
            player->play();


            //ui->Title->setText(in.readAll());
            file.close();
        }

    }else{

        if (player->state() == player->StoppedState){
            ui->Playpause->setText("Pause");
            player->play();
        }else{
            ui->Playpause->setText("Play");
            player->pause();
        }
    }
}

void MainWindow::on_Webcam_clicked()
{
    camera->setViewfinder(ui->screen);
    camera->start();

    if (camera->state() == camera->ActiveState){
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
