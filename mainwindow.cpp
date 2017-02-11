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
    delete player;
    delete camera;
}

void MainWindow::on_Forward_clicked()
{

    if (player->playbackRate() <= 1.0){

        if (player->state() == player->PlayingState)
            player->setPlaybackRate(1.5);
    }else
        player->setPlaybackRate(1.0);


}

void MainWindow::on_Stop_clicked()
{

    if ((player->state() == player->PlayingState) || (player->state() == player->PausedState)){
        player->stop();
        ui->Playpause->setText("Play");
    }

    if (player->playbackRate() > 1.0)
        player->setPlaybackRate(1.0);

    if (player->playbackRate() < 1.0)
        player->setPlaybackRate(1.0);


}

void MainWindow::on_Rewind_clicked()
{

    if (player->playbackRate() == 1.0){

        if (player->state() == player->PlayingState)
            player->setPlaybackRate(-1.5);
    }else
        player->setPlaybackRate(1.0);

}

void MainWindow::on_Playpause_clicked()
{

    if ((camera->state() == camera->ActiveState) || (player->mediaStatus() == player->NoMedia)){

        if (camera->state() == camera->ActiveState)
            camera->stop();

        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), QString(),
            tr("Video Files (*.avi);"));

        if (!fileName.isEmpty()) {

            player->setVideoOutput(ui->screen);
            player->setMedia(QUrl::fromLocalFile(fileName));
            qDebug() << fileName << endl;
            ui->screen->show();
            player->play();
            ui->Playpause->setText("Pause");

        }


    }else{

        if ((player->state() == player->PausedState) || (player->state() == player->StoppedState)){
            player->play();
            ui->Playpause->setText("Pause");
        }else{
            player->pause();
            ui->Playpause->setText("Play");
        }
    }
}

void MainWindow::on_Webcam_clicked()
{
    if (player->state() != player->StoppedState){
        player->stop();

        if (player->playbackRate() > 1.0)
            player->setPlaybackRate(1.0);

        if (player->playbackRate() < 1.0)
            player->setPlaybackRate(1.0);

    }
    camera->setViewfinder(ui->screen);

    if (camera->state() == camera->ActiveState)
        camera->stop();
    else
        camera->start();


}


void MainWindow::on_pushButton_clicked()
{
    if (player->playbackRate() != 1.0){
        if (player->playbackRate() > 1.0)
           player->setPlaybackRate(player->playbackRate()+0.5);
        else
            player->setPlaybackRate(player->playbackRate()-0.5);
    }
}

void MainWindow::on_pushButton_2_clicked()
{

    if (player->playbackRate() != 1.0){
        if (player->playbackRate() > 1.0)
           player->setPlaybackRate(player->playbackRate()-0.5);
        else
            player->setPlaybackRate(player->playbackRate()+0.5);
    }

}

void MainWindow::on_toolButton_clicked()
{
    QMenu *menu = new QMenu(this);
    menu->addAction(new QAction("Action 1", this));
    menu->addAction(new QAction("Action 2", this));
    menu->addAction(new QAction("Action 3", this));
    ui->toolButton->setMenu(menu);
}
