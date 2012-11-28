#include "nermainwindow.h"
#include "ui_nermainwindow.h"

NERMainWindow::NERMainWindow(QWidget *parent) : QMainWindow(parent)
{
	resize(1024,768);

	createGuiElements();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	setCentralWidget(mainMdiArea);

	initializeMDIWindows();

}

NERMainWindow::~NERMainWindow()
{

}

void NERMainWindow::createGuiElements()
{
	mainMdiArea = new QMdiArea(this);
	diffTableWid = new DiffTableWidget(this);
	subWindowDiffTable = mainMdiArea->addSubWindow(diffTableWid);
	subWindowDiffTable->setWindowTitle("Evaluation");
	subWindowDiffTable->setMinimumSize(400,400);
    //subWindowDiffTable->setWindowIcon();

}

void NERMainWindow::createActions()
{
    newProjectAction = new QAction(tr("&New Project..."), this);
    newProjectAction->setShortcut(QKeySequence::New);
    newProjectAction->setIcon(QIcon(":/resources/pics/new.png"));
    newProjectAction->setStatusTip("Creates a new project");
    connect(newProjectAction, SIGNAL(triggered()), this, SLOT(newProjectSlot()));

    openProjectAction = new QAction(tr("&Open Project..."), this);
    openProjectAction->setShortcut(QKeySequence::Open);
    openProjectAction->setIcon(QIcon(":/resources/pics/open.png"));
    openProjectAction->setStatusTip("Opens an existing project");
    connect(openProjectAction, SIGNAL(triggered()), this, SLOT(openProjectSlot()));

    saveProjectAction = new QAction(tr("&Save Project..."), this);
	saveProjectAction->setShortcut(QKeySequence::Save);
    saveProjectAction->setIcon(QIcon(":/resources/pics/save.png"));
    saveProjectAction->setStatusTip("Saves the current project");
    connect(saveProjectAction, SIGNAL(triggered()), this, SLOT(saveProjectSlot()));

	closeProjectAction = new QAction(tr("&Close Project"), this);
	closeProjectAction->setShortcut(QKeySequence::Close);
	closeProjectAction->setIcon(QIcon(":/resources/pics/close.png"));
	closeProjectAction->setStatusTip("Closes Current Project");
	connect(closeProjectAction, SIGNAL(triggered()), this, SLOT(closeProjectSlot()));

	aboutAction = new QAction(tr("&About"), this);
	aboutAction->setShortcut(QKeySequence("Ctrl+A"));
	aboutAction->setIcon(QIcon(":/resources/pics/about.png"));
	aboutAction->setStatusTip("About this application");
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutSlot()));

    aboutQTAction = new QAction(tr("&About QT"), this);
	aboutQTAction->setShortcut(QKeySequence("Ctrl+I"));
	aboutQTAction->setIcon(QIcon(":/resources/pics/qt-logo.png"));
	aboutQTAction->setStatusTip("About QT Framework");
	connect(aboutQTAction, SIGNAL(triggered()), this, SLOT(aboutQTSlot()));

	closeAppAction = new QAction(tr("&Exit"), this);
	closeAppAction->setShortcut(QKeySequence("Ctrl+A"));
	closeAppAction->setIcon(QIcon(":/resources/pics/closeApp.png"));
	closeAppAction->setStatusTip("About this application");
	connect(closeAppAction, SIGNAL(triggered()), this, SLOT(closeApplicationSlot()));

}

void NERMainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newProjectAction);
    fileMenu->addAction(openProjectAction);
    fileMenu->addAction(saveProjectAction);
    fileMenu->addAction(closeProjectAction);
	fileMenu->addAction(closeAppAction);

	windowMenu = menuBar()->addMenu(tr("&Window"));
	

	helpMenu = menuBar()->addMenu(tr("Help"));
	helpMenu->addAction(aboutQTAction);
	helpMenu->addAction(aboutAction);
}

void NERMainWindow::createToolBars(){
    fileToolbar = addToolBar(tr("&File"));
    fileToolbar->addAction(newProjectAction);
    fileToolbar->addAction(openProjectAction);
    fileToolbar->addAction(saveProjectAction);
    fileToolbar->addAction(closeProjectAction);
	fileToolbar->addAction(aboutAction);
}

void NERMainWindow::createStatusBar(){
    statusBarLeftLabel = new QLabel(this);
    statusBarLeftLabel->setAlignment(Qt::AlignCenter);
    statusBarLeftLabel->setMinimumSize(statusBarLeftLabel->sizeHint());

    statusBarMiddleLabel = new QLabel(this);
    statusBarMiddleLabel->setAlignment(Qt::AlignRight);
    statusBarMiddleLabel->setMinimumSize(statusBarMiddleLabel->sizeHint());
	statusBarMiddleLabel->setText("Ready!");

	statusBar()->addWidget(statusBarLeftLabel);
	statusBar()->addWidget(statusBarMiddleLabel, 1);

}

void NERMainWindow::newProjectSlot()
{

}

void NERMainWindow::saveProjectSlot()
{

}

void NERMainWindow::openProjectSlot()
{

}

void NERMainWindow::closeProjectSlot()
{

}

void NERMainWindow::initializeMDIWindows()
{

	
	subWindowDiffTable->showNormal();

}

void NERMainWindow::closeApplicationSlot()
{
	QApplication::quit();
}

void NERMainWindow::aboutQTSlot()
{
    QApplication::aboutQt();
}

void NERMainWindow::aboutSlot()
{
    About *aboutDialog = new About(this);
	aboutDialog->setAttribute(Qt::WA_DeleteOnClose);
	aboutDialog->show();
}























