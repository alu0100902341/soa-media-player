#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(new QMediaPlayer),
    camera(),
    camera_devices()
{
    ui->setupUi(this);

    webcam_configuraion();
    create_icons();
    create_menus();
    error_management();

    setWindowTitle("Media Player");


}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete camera;
}


// ---------------------------------- WebCam Context Menu + Configuration Option --------------------------------------------------------------

void MainWindow::webcam_configuraion()
{

    camera_devices = QCameraInfo::availableCameras();
    qDebug() << camera_devices[0].deviceName() << endl;
    camera = new QCamera(camera_devices[0]);

    foreach(QCameraInfo c, camera_devices){
        ui->comboBox->addItem(c.deviceName());
    }
    ui->comboBox->setMinimumWidth(6);

    ui->Webcam->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->Webcam, &QWidget::customContextMenuRequested ,this ,&MainWindow::webcamContextMenu);
}

void MainWindow::webcamContextMenu()
{
   QMenu contextMenu;
   QAction config_action("Configuration", this);
   connect(&config_action, &QAction::triggered, this, &MainWindow::configuration_action);
   contextMenu.addAction(&config_action);
   contextMenu.exec(mapToGlobal(ui->Webcam->pos()));
}

void MainWindow::configuration_action()
{
    QMessageBox::information(this, tr("Information"),
                         tr("Functionality not tested."));
}

// ---------------------------------- Icons --------------------------------------------------------------
void MainWindow::create_icons()
{
    QPixmap pixmap0(":/images/play.png");
    QIcon play(pixmap0);
    ui->Playpause->setIcon(play);
    ui->Playpause->setIconSize(pixmap0.rect().size());

    QPixmap pixmap1(":/images/stop.png");
    QIcon stop(pixmap1);
    ui->Stop->setIcon(stop);
    ui->Stop->setIconSize(pixmap1.rect().size());

    QPixmap pixmap2(":/images/forward.png");
    QIcon forward(pixmap2);
    ui->Forward->setIcon(forward);
    ui->Forward->setIconSize(pixmap2.rect().size());

    QPixmap pixmap3(":/images/rewind.png");
    QIcon rewind(pixmap3);
    ui->Rewind->setIcon(rewind);
    ui->Rewind->setIconSize(pixmap3.rect().size());

    QPixmap pixmap4(":/images/webcam.png");
    QIcon webcam(pixmap4);
    ui->Webcam->setIcon(webcam);
    ui->Webcam->setIconSize(pixmap4.rect().size());

}

void MainWindow::play_icon()
{
    QPixmap pixmap0(":/images/play.png");
    QIcon play(pixmap0);
    ui->Playpause->setIcon(play);
    ui->Playpause->setIconSize(pixmap0.rect().size());
}

void MainWindow::pause_icon()
{
    QPixmap pixmap00(":/images/pause.png");
    QIcon pause(pixmap00);
    ui->Playpause->setIcon(pause);
    ui->Playpause->setIconSize(pixmap00.rect().size());
}

// --------------------------------Forward and Rewind Pop-Up menus----------------------------------------------------------------
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

    QMenu* speed_menu_forward = new QMenu;
    QMenu* speed_menu_rewind = new QMenu;

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
// ----------------------------------Speed Controls--------------------------------------------------------------
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

// -------------------------------Error Management-----------------------------------------------------------------

void MainWindow::error_management()
{
    //Static_cast es como a toi. Convierte un puntero a (&QMediaPlayer::error) a un puntero
    //a una función perteneciente a QMediaPlater (QMediaPlayer::*) que tiene como parámetro
    // (QMediaPlayer::Error)
    //float f=0.0;
    //int a = static_cast<int>(f)
    connect(player, static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error),this, &MainWindow::playerError );
    connect(camera, static_cast<void(QCamera::*)(QCamera::Error)>(&QCamera::error),this, &MainWindow::cameraError );
}

void MainWindow::playerError(QMediaPlayer::Error)
{
    ui->Playpause->setEnabled(false);
    const QString errorString = player->errorString();
    QString message = "Error: ";
    if (errorString.isEmpty())
        message += " #" + QString::number(int(player->error()));
    else
        message += errorString;

    QMessageBox::critical(this, tr("Error"),
                         message);

}

void MainWindow::cameraError(QCamera::Error)
{
    ui->Webcam->setEnabled(false);
    const QString errorString = camera->errorString();
    QString message = "Error: ";
    if (errorString.isEmpty())
        message += " #" + QString::number(int(camera->error()));
    else
        message += errorString;

    QMessageBox::critical(this, tr("Error"),
                         message);

}

// ----------------------------------Button Slots--------------------------------------------------------------


void MainWindow::on_Stop_clicked()
{

    if (camera->state() == camera->ActiveState)
        camera->stop();

    if ((player->state() == player->PlayingState) || (player->state() == player->PausedState)){

        player->stop();

        play_icon();

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
            tr("AVI Files (*.avi);; MP4 Files (*.mp4"));

        if (!fileName.isEmpty()) {

            QStringList parts = fileName.split("/");
            QString lastBit = parts.at(parts.size()-1);
            setWindowTitle(lastBit);

            player->setVideoOutput(ui->screen);
            player->setMedia(QUrl::fromLocalFile(fileName));
            qDebug() << fileName << endl;
            ui->screen->show();
            player->play();
            pause_icon();

        }

    }else{

        if ((player->state() == player->PausedState) || (player->state() == player->StoppedState)){
            player->play();
            pause_icon();
        }else{
            player->pause();
            play_icon();
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

    if (camera->state() == camera->ActiveState){
        camera->stop();
        setWindowTitle("Media Player");
    }else{
        setWindowTitle(camera_devices[0].deviceName());
        camera->setViewfinder(ui->screen);
        camera->start();
    }
}




void MainWindow::on_comboBox_activated(int index)
{
    camera = new QCamera(camera_devices[index]);
    setWindowTitle(camera_devices[index].deviceName());
    camera->setViewfinder(ui->screen);
    camera->start();
}
