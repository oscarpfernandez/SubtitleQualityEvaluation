#ifndef NERMAINWINDOW_H
#define NERMAINWINDOW_H

#include <qmainwindow.h>
#include <qaction.h>
#include <qlabel.h>
#include <qmenu.h>
#include <qmdiarea.h>
#include <qfiledialog.h>
#include <qdir.h>
#include <qdockwidget.h>
#include <QMap>
#include <QDesktopWidget>
#include "about.h"
#include "xmlhandler.h"
#include "nertablewidget.h"
#include "propertiestreewidget.h"
#include "nercommon.h"
#include "mediamngwidget.h"
#include "nerstatsviewerwidget.h"
#include "nergraphwidget.h"
#include "utils.h"
#include "licencemanager.h"



//QT_BEGIN_NAMESPACE
//class NERTableWidget;
//class XMLHandler;
//QT_END_NAMESPACE


class NERMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NERMainWindow(QWidget *parent = 0);
    LIC_ERROR_TYPE checkLicence();
    ~NERMainWindow();

private:
//    void checkLicence();
    void createGuiElements();
    void createActions();
    void enableActions(bool enable);
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockableWidgets();
    void showDockableWidgets(bool enable);
	void initializeMDIWindows();
    void enableActionsTransLoaded();
    void addTableInMdiArea(NERTableWidget* table, QString title);
    void computeWordDifferences(NERTableWidget *table);

    LicenceManager *licenceMng;


    bool isProjectloaded;

	QMdiArea *mainMdiArea;
	QMdiSubWindow *subWindowDiffTable;

    QList<NERTableWidget *> *nerTablesList;
    PropertiesTreeWidget *propertiesTreeWidget;

    MediaMngWidget *mediaMngWidget;

    QDockWidget *projectPropertiesDockWidget;
    QDockWidget *audioWaveFormDockWidget;
    QDockWidget *videoPlayerDockWidget;

    QAction *newProjectAction;
    QAction *saveProjectAction;
    QAction *saveAsProjectAction;
    QAction *openProjectAction;
    QAction *closeProjectAction;
	QAction *closeAppAction;
	QAction *aboutQTAction;
	QAction *aboutAction;
    QAction *viewPropertiesTree;
    QAction *loadTransXmlFile;
    QAction *loadSubtsXmlFile;
    QAction *loadSRTXmlFile;
    QAction *cascadeSubWindowsAction;
    QAction *tileSubWindowsAction;
    QAction *viewPropertiesDockAction;
    QAction *viewVideoPlayerDockAction;
    QAction *showVideoAction;
    QAction *computerNerStats;
    QAction *recomputeTableDifferences;



    QLabel  *statusBarLeftLabel;
    QLabel  *statusBarMiddleLabel;
    QLabel  *statusBarRightLabel;

    QToolBar *fileToolbar;
    QToolBar *toolsToolbar;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *toolsMenu;
    QMenu *subTitlesMenu;
	QMenu *windowMenu;
    QMenu *helpMenu;

    QString *projectSaveFilePath;
    XMLHandler *xmlHandler;
    QList<BlockTRS> *transcriptionList;
    QList<Speaker> *speakerList;
    bool isTranscriptionLoaded;
    bool isSubtitlesLoaded;

    NERStatsViewerWidget *nerStatsViewer;


private slots:
    void newProjectSlot();
    void saveProjectSlot();
    void saveAsProjectSlot();
    void openProjectSlot();
    void closeProjectSlot();
	void closeApplicationSlot();
    void viewProjectPropertiesSlot();
	void aboutQTSlot();
	void aboutSlot();
    void loadTranscriptionFileSlot();
    void loadSubtitlesFileSlot();
    void loadSRTSubtitlesFileSlot();
    void cascadeWindowsSlot();
    void tileWindowsSlot();
    void computerNERStatistics();
    void showNerStatsWindow();
    void recomputeTableDiff();

signals:
    void setNERStatistics(double &N, double &ner);


};

#endif // NERMAINWINDOW_H
