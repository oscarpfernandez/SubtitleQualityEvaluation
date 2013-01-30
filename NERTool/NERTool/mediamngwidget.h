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
#include <QFileDialog>
#include <QDesktopServices>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

class MediaMngWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MediaMngWidget(QWidget *parent = 0);
    ~MediaMngWidget();

private:
    void createActions();
    void setupGUI();

    Phonon::MediaSource *source;
    Phonon::SeekSlider *seekSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    Phonon::VolumeSlider *volumeSlider;

    QLCDNumber *timeLcd;
    QToolBar *buttonsBar;

    QLabel *fileNamelabel;
    QLineEdit *fileNameLoaded;

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


    
public slots:
    void loadAudioFileSlot();
    void playAudioFileSlot();
    void pauseAudioFileSlot();
    void stopAudioFileSlot();
    void loadVideoFileSlot();
    void playVideoFileSlot();
    void stopVideoFileSlot();
    void stateChangedSlot(Phonon::State newState, Phonon::State oldState);
    void tickSlot(qint64 time);
    void sourceChangedSlot(const Phonon::MediaSource &source);
    void metaStateChangedSlot(Phonon::State newState, Phonon::State oldState);
    
};

#endif // MEDIAMNGWIDGET_H
