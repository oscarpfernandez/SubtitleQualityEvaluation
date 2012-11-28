#ifndef NERMAINWINDOW_H
#define NERMAINWINDOW_H

#include <qmainwindow.h>
#include <qaction.h>
#include <qlabel.h>
#include <qmenu.h>
#include <qmdiarea.h>
#include "about.h"
#include "difftablewidget.h"

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

	DiffTableWidget *diffTableWid;

    QAction *newProjectAction;
    QAction *saveProjectAction;
    QAction *openProjectAction;
    QAction *closeProjectAction;
	QAction *closeAppAction;
	QAction *aboutQTAction;
	QAction *aboutAction;

    QLabel  *statusBarLeftLabel;
    QLabel  *statusBarMiddleLabel;
    QLabel  *statusBarRightLabel;

    QToolBar *fileToolbar;
    QToolBar *toolsToolbar;
    QMenu *fileMenu;
	QMenu *windowMenu;
    QMenu *helpMenu;

private slots:
    void newProjectSlot();
    void saveProjectSlot();
    void openProjectSlot();
    void closeProjectSlot();
	void closeApplicationSlot();
	void aboutQTSlot();
	void aboutSlot();


};

#endif // NERMAINWINDOW_H
