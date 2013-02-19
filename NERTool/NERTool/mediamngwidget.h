#ifndef MEDIAMNGWIDGET_H
#define MEDIAMNGWIDGET_H

#include <QWidget>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QToolBar>
#include <QLabel>
#include <QLineEdit>
#include <QStyle>
#include <QMessageBox>
#include <QTime>
#include <QPushButton>
#include <QFileDialog>
#include <QDesktopServices>
#include <QComboBox>
#include <QTimer>
#include <phonon/audiooutput.h>
#include <phonon/videowidget.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <phonon/MediaController>
#include "nertablewidget.h"

class NERTableWidget;

class MediaMngWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MediaMngWidget(QWidget *parent = 0, QMdiArea *mMdiArea=0);
    ~MediaMngWidget();
    QWidget* getVideoWindow();

private:
    void createActions();
    void setupGUI();

    Phonon::MediaSource *source;
    Phonon::SeekSlider *seekSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    Phonon::VideoWidget *videoPlayer;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::MediaController *mediaController;

    QMdiArea *mainMDIArea;
    QLabel *loadedMdiWinLabel;
    QLineEdit *loadedMdiWinName;
    QHash<qint64,QString> subtitles;
    QTimer *subsTimeoutTimer;

    QLCDNumber *timeLcd;
    QToolBar *buttonsBar;

    QLabel *fileNamelabel;
    QLineEdit *fileNameLoaded;

    bool isVideoAvailable;
    bool isMediaSeekable;

    QAction *loadAudioFileAction;
    QAction *playAudioAction;
    QAction *pauseAudioAction;
    QAction *stopAudioAction;
    QAction *loadVideoFileAction;
    QAction *playVideoAction;
    QAction *stopVideoAction;

    QVBoxLayout *mainVBoxLayout;
    QHBoxLayout *fileDescLayout;
    QHBoxLayout *sliderTimerLayout;

    QWidget *videoWindow;
    QLabel *videoSubLabel;
    QVBoxLayout *videoWidLayout;

    
public slots:
    void loadMediaFileSlot();
    void playMediaFileSlot();
    void pauseMediaFileSlot();
    void stopMediaFileSlot();
    void stateChangedSlot(Phonon::State newState, Phonon::State oldState);
    void tickSlot(qint64 time);
    void sourceChangedSlot(const Phonon::MediaSource &source);
    void metaStateChangedSlot(Phonon::State newState, Phonon::State oldState);
    void hasVideochanged(bool hasVideoChange);
    void seekableChanged(bool isSeekChanged);
    void seekVideo(qint64 time);
    void finished();
//    void showVideoPlayer();
    void loadVideoSubtitlesFromTableData(NERTableWidget *table);
    void setActivatedSubWindow(QMdiSubWindow* subwindow);
    void clearVideoSubtitle();
    
private:
    void checkForSubtitleAndUpdateVideo(qlonglong timeInMilis);
    QString splitSubtitleLine(QString sub);
};

#endif // MEDIAMNGWIDGET_H
