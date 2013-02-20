#include "mediamngwidget.h"

MediaMngWidget::MediaMngWidget(QWidget *parent, QMdiArea *mainMdiArea) :
    QWidget(parent)
{
    mainMDIArea = mainMdiArea;
    connect(mainMDIArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(setActivatedSubWindow(QMdiSubWindow*)));

    videoPlayer = new Phonon::VideoWidget();
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);

    isVideoAvailable = false;
    isMediaSeekable = false;

    metaInformationResolver = new Phonon::MediaObject(this);
    mediaObject->setTickInterval(50);

    mediaController = new Phonon::MediaController(mediaObject);

    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tickSlot(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChangedSlot(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(finished()), this, SLOT(finished()));
    connect(mediaObject, SIGNAL(seekableChanged(bool)), this, SLOT(seekableChanged(bool)));
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(metaStateChangedSlot(Phonon::State,Phonon::State)));
    connect(metaInformationResolver, SIGNAL(hasVideoChanged(bool)),
            this, SLOT(hasVideochanged(bool)));
    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChangedSlot(Phonon::MediaSource)));


    Phonon::createPath(mediaObject, audioOutput);
    Phonon::createPath(mediaObject, videoPlayer);

    subsTimeoutTimer = new QTimer(this);
    connect(subsTimeoutTimer, SIGNAL(timeout()), this, SLOT(clearVideoSubtitle()));


    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkBlue);
    setPalette(palette);


    createActions();
    setupGUI();

}

MediaMngWidget::~MediaMngWidget()
{

}


void MediaMngWidget::createActions()
{
    loadAudioFileAction = new QAction(tr("&Load Media File..."), this);
    loadAudioFileAction->setShortcut(QKeySequence("Ctrl+F5"));
    loadAudioFileAction->setIcon(QIcon(":/resources/pics/player_load.png"));
    loadAudioFileAction->setStatusTip("Load audio file");
    connect(loadAudioFileAction, SIGNAL(triggered()), this, SLOT(loadMediaFileSlot()));

    playAudioAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    playAudioAction->setShortcut(QKeySequence("Ctrl+p"));
    playAudioAction->setDisabled(true);
    playAudioAction->setIcon(QIcon(":/resources/pics/player_play.png"));
    playAudioAction->setStatusTip("Play media");
    connect(playAudioAction, SIGNAL(triggered()), this, SLOT(playMediaFileSlot()));

    pauseAudioAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    pauseAudioAction->setShortcut(QKeySequence("Ctrl+A"));
    pauseAudioAction->setStatusTip("Pause media");
    pauseAudioAction->setDisabled(true);
    pauseAudioAction->setIcon(QIcon(":/resources/pics/player_pause.png"));
    connect(pauseAudioAction, SIGNAL(triggered()), this, SLOT(pauseMediaFileSlot()));

    stopAudioAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAudioAction->setShortcut(QKeySequence("Ctrl+S"));
    stopAudioAction->setStatusTip("Stop media");
    stopAudioAction->setDisabled(true);
    stopAudioAction->setIcon(QIcon(":/resources/pics/player_stop.png"));
    connect(stopAudioAction, SIGNAL(triggered()), this, SLOT(stopMediaFileSlot()));

}

void MediaMngWidget::setupGUI()
{
    seekSlider = new Phonon::SeekSlider(this);
    seekSlider->setSingleStep(100);
    seekSlider->setMinimumHeight(30);
    seekSlider->setMediaObject(mediaObject);

    volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider->setAudioOutput(audioOutput);
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);

    timeLcd = new QLCDNumber(12,this);
    timeLcd->setAutoFillBackground(true);
    timeLcd->display("00:00:00.000");
    timeLcd->setSegmentStyle(QLCDNumber::Filled);
    timeLcd->setPalette(palette);

    fileNameLoaded = new QLineEdit(this);
    fileNameLoaded->setDisabled(true);
    fileNameLoaded->setAlignment(Qt::AlignLeft);
    fileNamelabel = new QLabel("File Name: ", this);
    fileNamelabel->setPalette(palette);

    loadedMdiWinLabel = new QLabel;
    loadedMdiWinLabel->setText(tr("Window: "));
    loadedMdiWinName = new QLineEdit;
    loadedMdiWinName->setDisabled(true);

    buttonsBar = new QToolBar(this);
    buttonsBar->addAction(loadAudioFileAction);
    buttonsBar->addAction(playAudioAction);
    buttonsBar->addAction(pauseAudioAction);
    buttonsBar->addAction(stopAudioAction);
    buttonsBar->setMaximumWidth(buttonsBar->sizeHint().width());

    fileDescLayout = new QHBoxLayout;
    fileDescLayout->addWidget(fileNamelabel);
    fileDescLayout->addWidget(fileNameLoaded);
    fileDescLayout->addWidget(loadedMdiWinLabel);
    fileDescLayout->addWidget(loadedMdiWinName);

    sliderTimerLayout = new QHBoxLayout;
    sliderTimerLayout->addWidget(buttonsBar);
    sliderTimerLayout->addSpacing(20);
    sliderTimerLayout->addWidget(volumeSlider);
    sliderTimerLayout->addSpacing(20);
    sliderTimerLayout->addWidget(seekSlider);
    sliderTimerLayout->addSpacing(20);
    sliderTimerLayout->addWidget(timeLcd);

    mainVBoxLayout = new QVBoxLayout;
    mainVBoxLayout->addLayout(fileDescLayout);
    mainVBoxLayout->addSpacing(10);
    mainVBoxLayout->addLayout(sliderTimerLayout);

    videoWindow = new QWidget();
    QPalette bvidpalette = videoWindow->palette();
    bvidpalette.setColor(QPalette::Window, Qt::black);
    videoWindow->setWindowTitle(tr("Video Player"));
    videoWindow->setPalette(bvidpalette);
    videoWidLayout = new QVBoxLayout();
    videoSubLabel = new QLabel();
    videoSubLabel->setText(QString("This is a test!\n A real good one!"));
    videoSubLabel->setFont(QFont("Times",12, true));
    videoSubLabel->setFixedHeight(70);
    videoSubLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    videoSubLabel->setAutoFillBackground(true);
    QPalette bpalette = videoSubLabel->palette();
    bpalette.setColor(QPalette::Window, Qt::black);
    bpalette.setColor(QPalette::WindowText, Qt::yellow);
    videoSubLabel->setPalette(bpalette);
    videoWidLayout->addWidget(videoPlayer);
    videoWidLayout->addWidget(videoSubLabel);
    videoWindow->setLayout(videoWidLayout);
    videoWindow->setWindowFlags(Qt::WindowStaysOnTopHint);

    setLayout(mainVBoxLayout);

}


/**************
 * Slots
 *************/
void MediaMngWidget::loadMediaFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Select Music Files"),
                QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

    if (fileName.isEmpty()){
        return;
    }

    fileNameLoaded->setText(QString(fileName));

    source = new Phonon::MediaSource(fileName);
    metaInformationResolver->setCurrentSource(*source);
    mediaObject->stop();
    mediaObject->clearQueue();
    mediaObject->setCurrentSource(*source);

}


void MediaMngWidget::playMediaFileSlot()
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

void MediaMngWidget::stopMediaFileSlot()
{
    if(mediaObject->state() == Phonon::PlayingState
            || mediaObject->state() == Phonon::PausedState)
    {
        mediaObject->stop();
    }

}

void MediaMngWidget::pauseMediaFileSlot()
{
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    if(wasPlaying){
        mediaObject->pause();
    }

}

void MediaMngWidget::finished()
{
    mediaObject->stop();
}

void MediaMngWidget::seekableChanged(bool isSeekChanged)
{
    isMediaSeekable = isSeekChanged;
}

void MediaMngWidget::seekVideo(qint64 time)
{
    if(!isMediaSeekable || time > mediaObject->totalTime() || time < 0)
    {
        //Nothing to do here...
        return;
    }
    mediaObject->seek(time);
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
        loadAudioFileAction->setEnabled(false);
        break;
    case Phonon::StoppedState:
        stopAudioAction->setEnabled(false);
        playAudioAction->setEnabled(true);
        pauseAudioAction->setEnabled(false);
        loadAudioFileAction->setEnabled(true);
        timeLcd->display("00:00:00.000");
        break;
    case Phonon::PausedState:
        pauseAudioAction->setEnabled(false);
        stopAudioAction->setEnabled(true);
        playAudioAction->setEnabled(true);
        loadAudioFileAction->setEnabled(true);
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

    checkForSubtitleAndUpdateVideo(time);

}

void MediaMngWidget::sourceChangedSlot(const Phonon::MediaSource &source)
{
    timeLcd->display("00:00:00.000");
    mediaObject->stop();

}

void MediaMngWidget::metaStateChangedSlot(Phonon::State newState, Phonon::State oldState)
{

}

void MediaMngWidget::hasVideochanged(bool hasVideoChange)
{
    isVideoAvailable = hasVideoChange;
}

void MediaMngWidget::checkForSubtitleAndUpdateVideo(qlonglong timeInMilis)
{
    qlonglong time = timeInMilis - (timeInMilis % SUBTITLE_CHECK_INTERVAL);

    ENGINE_DEBUG << "Subs Chech -- " << time;

    QString sub = subtitles.value(time, QString(""));

    if(sub.count()!=0){
        if(subsTimeoutTimer->isActive()){
            subsTimeoutTimer->stop();
        }

        QString ret = splitSubtitleLine(sub);
        videoSubLabel->setText(ret);

        subsTimeoutTimer->start(SUBTITLE_CLEAN_TIMEOUT);
    }
}

QString MediaMngWidget::splitSubtitleLine(QString sub)
{
    if(sub.count() <= 34){
        return sub;
    }

    QStringList list = sub.split(" ");

    QString ret;
    int countChars = 0;
    for(int i=0; i<list.count(); i++)
    {
        QString word = list.at(i);
        if(countChars <= 34){
            countChars += word.count();
            ret.append(word).append(" ");
        }
        else{
            countChars = word.count();
            ret.append("\n").append(word).append(" ");
        }
    }


    return ret;
}

void MediaMngWidget::loadVideoSubtitlesFromTableData(NERTableWidget *table)
{
    if(table==0 || table->rowCount()==0)
    {
        return;
    }

    QList<BlockTRS> subtitleTable;

    for(int i=0; i<table->rowCount(); i++)
    {
        NERSubTableWidget* subtable = (NERSubTableWidget*)table->item(i, SUBTITLES_COLUMN_INDEX);
        if(subtable!=0){

            for(int k=0; k<subtable->rowCount(); k++){
                BlockTRS btr = subtable->getSubtableRowData(k);
                subtitleTable.append(btr);
            }
        }
    }
}

QWidget* MediaMngWidget::getVideoWindow()
{
    return videoWindow;
}

void MediaMngWidget::setActivatedSubWindow(QMdiSubWindow *subwindow)
{
    if(subwindow==0){
        return;
    }

    NERTableWidget *table = static_cast<NERTableWidget*>(subwindow->widget());
    if(table!=0){
        loadedMdiWinName->setText("New Window");
        subtitles = table->getHashedSubtableData();
    }
}

void MediaMngWidget::clearVideoSubtitle()
{
    videoSubLabel->setText("");
}
