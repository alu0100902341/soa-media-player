#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(new QMediaPlayer),
    camera(),
    speed_menu_forward(new QMenu),
    speed_menu_rewind(new QMenu),
    infocamera(new QCameraInfo())
{
    ui->setupUi(this);
    create_menus();
    setWindowTitle("Media Player");
    QList<QCameraInfo> devices = QCameraInfo::availableCameras();
    qDebug() << devices[0].deviceName() << endl;
    camera = new QCamera(devices[0]);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete camera;
    delete speed_menu_forward;
    delete speed_menu_rewind;
}

void MainWindow::create_menus()
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

    ui->Forward->setMenu(speed_menu_forward);
    ui->Rewind->setMenu(speed_menu_rewind);

}

void MainWindow::Speed(qreal real){

    if ((player->state() == player->PlayingState) || (player->state() == player->PausedState))
        player->setPlaybackRate(real);
    else
    QMessageBox::warning(this, tr("Warning"),
                         tr("Video must be playing/paused."));
}

void MainWindow::Normal(){ Speed(1.0); }
void MainWindow::increase3(){ Speed(0.5); }
void MainWindow::increase1(){ Speed(1.5); }
void MainWindow::increase2(){ Speed(2.0); }

void MainWindow::decrease1(){ Speed(-1.5); }
void MainWindow::decrease2(){ Speed(-2.0); }


// ------------------------------------------------------------------------------------------------


void MainWindow::on_Stop_clicked()
{

    if (camera->state() == camera->ActiveState)
        camera->stop();

    if ((player->state() == player->PlayingState) || (player->state() == player->PausedState)){
        player->stop();
        ui->Playpause->setText("Play");
        setWindowTitle("Media Player");
    }else{
        QMessageBox::warning(this, tr("Warning"),
                             tr("No video is been displayed."));
    }

    if (player->playbackRate() > 1.0)
        player->setPlaybackRate(1.0);

    if (player->playbackRate() < 1.0)
        player->setPlaybackRate(1.0);
}



void MainWindow::on_Playpause_clicked()
{

    if ((camera->state() == camera->ActiveState) || (player->state() == player->StoppedState)){

        if (camera->state() == camera->ActiveState)
            camera->stop();

        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), QString(),
            tr("Video Files (*.avi);"));

        if (!fileName.isEmpty()) {

            QStringList parts = fileName.split("/");
            QString lastBit = parts.at(parts.size()-1);
            setWindowTitle(lastBit);

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

    if (camera->state() == camera->ActiveState)
        camera->stop();
    else{
        camera->setViewfinder(ui->screen);
        camera->start();
    }
}


