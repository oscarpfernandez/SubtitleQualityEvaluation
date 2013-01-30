#include "mediamngwidget.h"

MediaMngWidget::MediaMngWidget(QWidget *parent) :
    QWidget(parent)
{

    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    metaInformationResolver = new Phonon::MediaObject(this);
    mediaObject->setTickInterval(50);

    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tickSlot(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChangedSlot(Phonon::State,Phonon::State)));
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(metaStateChangedSlot(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChangedSlot(Phonon::MediaSource)));

    Phonon::createPath(mediaObject, audioOutput);

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkBlue);
    setPalette(palette);

    createActions();
    setupGUI();

    loadAudioFileSlot();

}

MediaMngWidget::~MediaMngWidget()
{

}


void MediaMngWidget::createActions()
{
    //Video Actions
    loadVideoFileAction = new QAction(tr("&Load Video File..."), this);
    loadVideoFileAction->setShortcut(QKeySequence("Ctrl+F6"));
    loadVideoFileAction->setIcon(QIcon(":/resources/pics/player_load.png"));
    loadVideoFileAction->setStatusTip("Load video file");
    connect(loadVideoFileAction, SIGNAL(triggered()), this, SLOT(loadVideoFileSlot()));

    playVideoAction = new QAction(tr("&Play audio..."), this);
    playVideoAction->setShortcut(QKeySequence("Ctrl+m"));
    playVideoAction->setIcon(QIcon(":/resources/pics/player_play.png"));
    playVideoAction->setStatusTip("Load video file");
    connect(playVideoAction, SIGNAL(triggered()), this, SLOT(playVideoFileSlot()));

    stopVideoAction = new QAction(tr("&Play audio..."), this);
    stopVideoAction->setShortcut(QKeySequence("Ctrl+m"));
    stopVideoAction->setIcon(QIcon(":/resources/pics/player_stop.png"));
    stopVideoAction->setStatusTip("Load video file");
    connect(stopVideoAction, SIGNAL(triggered()), this, SLOT(stopVideoFileSlot()));

    //Audio Actions
    loadAudioFileAction = new QAction(tr("&Load Audio File..."), this);
    loadAudioFileAction->setShortcut(QKeySequence("Ctrl+F5"));
    loadAudioFileAction->setIcon(QIcon(":/resources/pics/player_load.png"));
    loadAudioFileAction->setStatusTip("Load audio file");
    connect(loadAudioFileAction, SIGNAL(triggered()), this, SLOT(loadAudioFileSlot()));

    playAudioAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    playAudioAction->setShortcut(QKeySequence("Ctrl+p"));
    playAudioAction->setDisabled(true);
    playAudioAction->setIcon(QIcon(":/resources/pics/player_play.png"));
    playAudioAction->setStatusTip("Play audio file");
    connect(playAudioAction, SIGNAL(triggered()), this, SLOT(playAudioFileSlot()));



    pauseAudioAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    pauseAudioAction->setShortcut(QKeySequence("Ctrl+A"));
    pauseAudioAction->setStatusTip("Pause audio file");
    pauseAudioAction->setDisabled(true);
    pauseAudioAction->setIcon(QIcon(":/resources/pics/player_pause.png"));
    connect(pauseAudioAction, SIGNAL(triggered()), this, SLOT(pauseAudioFileSlot()));

    stopAudioAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAudioAction->setShortcut(QKeySequence("Ctrl+S"));
    stopAudioAction->setStatusTip("Stop audio");
    stopAudioAction->setDisabled(true);
    stopAudioAction->setIcon(QIcon(":/resources/pics/player_stop.png"));
    connect(stopAudioAction, SIGNAL(triggered()), this, SLOT(stopAudioFileSlot()));



}

void MediaMngWidget::setupGUI()
{
    seekSlider = new Phonon::SeekSlider(this);
    seekSlider->setSingleStep(100);
    seekSlider->setMinimumHeight(30);
    seekSlider->setMediaObject(mediaObject);

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);

    timeLcd = new QLCDNumber(12,this);
    timeLcd->setAutoFillBackground(true);
    timeLcd->display("00:00:00.000");
    timeLcd->setSegmentStyle(QLCDNumber::Filled);
//    timeLcd->setMinimumSize(80,30);
    timeLcd->setPalette(palette);

    fileNameLoaded = new QLineEdit(this);
    fileNameLoaded->setDisabled(true);
    fileNameLoaded->setAlignment(Qt::AlignLeft);
    fileNamelabel = new QLabel("File Name: ", this);
    fileNamelabel->setPalette(palette);

    buttonsBar = new QToolBar(this);
    buttonsBar->addAction(playAudioAction);
    buttonsBar->addAction(pauseAudioAction);
    buttonsBar->addAction(stopAudioAction);
    buttonsBar->setMaximumWidth(buttonsBar->sizeHint().width());

    fileDescLayout = new QHBoxLayout;
    fileDescLayout->addWidget(fileNamelabel);
    fileDescLayout->addWidget(fileNameLoaded);


    sliderTimerLayout = new QHBoxLayout;
    sliderTimerLayout->addWidget(buttonsBar);
    sliderTimerLayout->addSpacing(20);
    sliderTimerLayout->addWidget(seekSlider);
    sliderTimerLayout->addSpacing(20);
    sliderTimerLayout->addWidget(timeLcd);

    mainVBoxLayout = new QVBoxLayout;
    mainVBoxLayout->addLayout(fileDescLayout);
    mainVBoxLayout->addSpacing(10);
    mainVBoxLayout->addLayout(sliderTimerLayout);

    setLayout(mainVBoxLayout);

}



/**************
 * Slots
 *************/
void MediaMngWidget::loadAudioFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Music Files"),
                                                      QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

        if (fileName.isEmpty()){
            return;
        }

        fileNameLoaded->setText(QString(fileName));
//        if(source != 0){
//            //if it was already initialized previously...
//            delete source;
//            source=NULL;
//        }
        source = new Phonon::MediaSource(fileName);
        metaInformationResolver->setCurrentSource(*source);
        mediaObject->stop();
        mediaObject->clearQueue();
        mediaObject->setCurrentSource(*source);

}

void MediaMngWidget::loadVideoFileSlot()
{

}

void MediaMngWidget::playAudioFileSlot()
{
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;

    if (mediaObject->state() == Phonon::StoppedState){
        mediaObject->stop();
        mediaObject->clearQueue();
        mediaObject->setCurrentSource(*source);
        mediaObject->play();
    }
    else if(mediaObject->state() == Phonon::PausedState){
        mediaObject->play();
    }

}

void MediaMngWidget::stopAudioFileSlot()
{
    if(mediaObject->state() == Phonon::PlayingState
            || mediaObject->state() == Phonon::PausedState)
    {
        mediaObject->stop();
    }

}

void MediaMngWidget::pauseAudioFileSlot()
{
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    if(wasPlaying){
        mediaObject->pause();
    }

}

void MediaMngWidget::playVideoFileSlot()
{

}

void MediaMngWidget::stopVideoFileSlot()
{

}

void MediaMngWidget::stateChangedSlot(Phonon::State newState, Phonon::State /*oldState*/)
{
    switch (newState) {
    case Phonon::ErrorState:
        if (mediaObject->errorType() == Phonon::FatalError) {
            QMessageBox::warning(this, tr("Fatal Error"),
                                 mediaObject->errorString());
        } else {
            QMessageBox::warning(this, tr("Error"),
                                 mediaObject->errorString());
        }
        break;
    case Phonon::PlayingState:
        playAudioAction->setEnabled(false);
        pauseAudioAction->setEnabled(true);
        stopAudioAction->setEnabled(true);
        break;
    case Phonon::StoppedState:
        stopAudioAction->setEnabled(false);
        playAudioAction->setEnabled(true);
        pauseAudioAction->setEnabled(false);
        timeLcd->display("00:00:00.000");
        break;
    case Phonon::PausedState:
        pauseAudioAction->setEnabled(false);
        stopAudioAction->setEnabled(true);
        playAudioAction->setEnabled(true);
        break;
    case Phonon::BufferingState:
        break;
    default:
        ;
    }
}

void MediaMngWidget::tickSlot(qint64 time)
{
    QTime displayTime(time / (60*60*1000), (time / 60000) % 60, (time / 1000) % 60, time % 1000);

    timeLcd->display(displayTime.toString("hh:mm:ss.zzz"));
}

void MediaMngWidget::sourceChangedSlot(const Phonon::MediaSource &source)
{
    timeLcd->display("00:00:00.000");
    mediaObject->stop();

}

void MediaMngWidget::metaStateChangedSlot(Phonon::State newState, Phonon::State oldState)
{

}
