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
#include "about.h"
#include "xmlhandler.h"
#include "nertablewidget.h"
#include "propertiestreewidget.h"
#include "nercommon.h"
#include "mediamngwidget.h"


//QT_BEGIN_NAMESPACE
//class NERTableWidget;
//class XMLHandler;
//QT_END_NAMESPACE


class NERMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NERMainWindow(QWidget *parent = 0);
    ~NERMainWindow();

private:
    void createGuiElements();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockableWidgets();
	void initializeMDIWindows();
    void enableActionsTransLoaded();

    void addNewTableAndTreeNode();

	QMdiArea *mainMdiArea;
	QMdiSubWindow *subWindowDiffTable;

    QList<NERTableWidget *> *nerTablesList;
    NERTableWidget *diffTableWid;
    PropertiesTreeWidget *propertiesTreeWidget;

    MediaMngWidget *mediaMngWidget;

    QMap<QTreeWidgetItem*, NERTableWidget*> mapTableContentTree;

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
    QAction *cascadeSubWindowsAction;
    QAction *tileSubWindowsAction;
    QAction *viewPropertiesDockAction;
    QAction *viewVideoPlayerDockAction;


    QLabel  *statusBarLeftLabel;
    QLabel  *statusBarMiddleLabel;
    QLabel  *statusBarRightLabel;

    QToolBar *fileToolbar;
    QToolBar *toolsToolbar;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *toolsMenu;
	QMenu *windowMenu;
    QMenu *helpMenu;

    QString *projectSaveFilePath;
    XMLHandler *xmlHandler;
    QList<BlockTRS> *transcriptionList;
    QList<Speaker> *speakerList;
    bool isTranscriptionLoaded;


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
    void cascadeWindowsSlot();
    void tileWindowsSlot();




};

#endif // NERMAINWINDOW_H
