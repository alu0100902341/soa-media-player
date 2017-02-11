#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(new QMediaPlayer),
    camera(new QCamera),
    speed_menu_forward(new QMenu),
    speed_menu_rewind(new QMenu)
{
    ui->setupUi(this);
    create_menu_actions();
    create_menu();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete camera;
    delete speed_menu_forward;
    delete speed_menu_rewind;
}

void MainWindow::create_menu_actions()
{

    QAction *Increase_3 = new QAction("0.5", this);
    connect(Increase_3, &QAction::triggered, this, &MainWindow::increase3);

    QAction *Normal = new QAction("1.0", this);
    connect(Normal, &QAction::triggered, this, &MainWindow::Normal);

    QAction *Increase_1 = new QAction("1.5", this);
    connect(Increase_1, &QAction::triggered, this, &MainWindow::increase1);

    QAction *Increase_2 = new QAction("2.0", this);
    connect(Increase_2, &QAction::triggered, this, &MainWindow::increase2);

    QAction *Decrease_1 = new QAction("-1.5", this);
    connect(Decrease_1, &QAction::triggered, this, &MainWindow::decrease1);

    QAction *Decrease_2 = new QAction("-2.0", this);
    connect(Decrease_2, &QAction::triggered, this, &MainWindow::decrease2);

    speed_menu_forward->addAction(Increase_3);
    speed_menu_forward->addAction(Normal);
    speed_menu_forward->addAction(Increase_1);
    speed_menu_forward->addAction(Increase_2);

    speed_menu_rewind->addAction(Normal);
    speed_menu_rewind->addAction(Decrease_1);
    speed_menu_rewind->addAction(Decrease_2);

}

void MainWindow::create_menu()
{

}

void MainWindow::Normal(){ player->setPlaybackRate(1.0); }
void MainWindow::increase3(){ player->setPlaybackRate(0.5); }
void MainWindow::increase1(){ player->setPlaybackRate(1.5); }
void MainWindow::increase2(){ player->setPlaybackRate(2.0); }

void MainWindow::decrease1(){ player->setPlaybackRate(-1.5); }
void MainWindow::decrease2(){ player->setPlaybackRate(-2.0); }


// ------------------------------------------------------------------------------------------------

void MainWindow::on_Forward_clicked(){ ui->Forward->setMenu(speed_menu_forward);}

void MainWindow::on_Rewind_clicked(){ ui->Rewind->setMenu(speed_menu_rewind);}

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


