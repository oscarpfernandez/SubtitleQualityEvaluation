#ifndef NERMAINWINDOW_H
#define NERMAINWINDOW_H

#include <qmainwindow.h>
#include <qaction.h>
#include <qlabel.h>
#include <qmenu.h>
#include <qmdiarea.h>
#include <qfiledialog.h>
#include <qdir.h>
#include "about.h"
#include "xmlhandler.h"
#include "nertablewidget.h"


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
	void initializeMDIWindows();

	QMdiArea *mainMdiArea;
	QMdiSubWindow *subWindowDiffTable;

    NERTableWidget *diffTableWid;

    QAction *newProjectAction;
    QAction *saveProjectAction;
    QAction *openProjectAction;
    QAction *closeProjectAction;
	QAction *closeAppAction;
	QAction *aboutQTAction;
	QAction *aboutAction;
    QAction *viewPropertiesTree;
    QAction *loadTransXmlFile;
    QAction *loadSubtsXmlFile;

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

    XMLHandler *xmlHandler;

private slots:
    void newProjectSlot();
    void saveProjectSlot();
    void openProjectSlot();
    void closeProjectSlot();
	void closeApplicationSlot();
    void viewProjectPropertiesSlot();
	void aboutQTSlot();
	void aboutSlot();
    void loadTranscriptionFileSlot();
    void loadSubtitlesFileSlot();


};

#endif // NERMAINWINDOW_H
