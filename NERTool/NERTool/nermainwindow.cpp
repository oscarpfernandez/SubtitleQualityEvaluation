#include "nermainwindow.h"
#include "ui_nermainwindow.h"

NERMainWindow::NERMainWindow(QWidget *parent) : QMainWindow(parent)
{
	resize(1024,768);
    setWindowTitle(NER_APP_NAME);

	createGuiElements();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
    createDockableWidgets();

	setCentralWidget(mainMdiArea);

	initializeMDIWindows();

    xmlHandler = new XMLHandler();
    transcriptionList = new QList<BlockTRS>();

}

NERMainWindow::~NERMainWindow()
{
    delete transcriptionList;
    delete xmlHandler;

}

void NERMainWindow::createGuiElements()
{
	mainMdiArea = new QMdiArea(this);
    diffTableWid = new NERTableWidget(this);
    subWindowDiffTable = mainMdiArea->addSubWindow(diffTableWid, Qt::CustomizeWindowHint |Qt::WindowTitleHint| Qt::WindowMinMaxButtonsHint);
    subWindowDiffTable->setWindowTitle("Trancription Data");
    subWindowDiffTable->setMinimumSize(800,600);
    //subWindowDiffTable->setWindowIcon();

    propertiesTreeWidget = new PropertiesTreeWidget(this);

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
    closeProjectAction->setShortcut(QKeySequence("Ctrl+Q"));
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
    closeAppAction->setShortcut(QKeySequence("Alt+F4"));
	closeAppAction->setIcon(QIcon(":/resources/pics/closeApp.png"));
	closeAppAction->setStatusTip("About this application");
	connect(closeAppAction, SIGNAL(triggered()), this, SLOT(closeApplicationSlot()));

    viewPropertiesTree = new QAction(tr("&Project Properties"),this);
    viewPropertiesTree->setShortcut(QKeySequence("Ctrl+P"));
    viewPropertiesTree->setIcon(QIcon(":/resources/pics/properties.png"));
    viewPropertiesTree->setStatusTip("Project Properties");
    connect(viewPropertiesTree, SIGNAL(triggered()), this, SLOT(viewProjectPropertiesSlot()));

    loadTransXmlFile = new QAction(tr("Load Transcription"), this);
    loadTransXmlFile->setShortcut(QKeySequence("Ctrl+T"));
    loadTransXmlFile->setStatusTip("Load transcription file...");
    connect(loadTransXmlFile, SIGNAL(triggered()), this, SLOT(loadTranscriptionFileSlot()));

    loadSubtsXmlFile = new QAction(tr("Load Subtitles"), this);
    loadSubtsXmlFile->setShortcut(QKeySequence("Ctrl+U"));
    loadSubtsXmlFile->setStatusTip("Load subtitles file...");
    connect(loadSubtsXmlFile, SIGNAL(triggered()), this, SLOT(loadSubtitlesFileSlot()));

    showComparisonTable = new QAction(tr("Comparison Table"), this);
    showComparisonTable->setStatusTip(tr("Comparison Table"));
    connect(showComparisonTable, SIGNAL(triggered()), this, SLOT(showComparisonTableSlot()));

}

void NERMainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newProjectAction);
    fileMenu->addAction(openProjectAction);
    fileMenu->addAction(saveProjectAction);
    fileMenu->addAction(closeProjectAction);
	fileMenu->addAction(closeAppAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(viewPropertiesTree);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(loadTransXmlFile);
    toolsMenu->addAction(loadSubtsXmlFile);

	windowMenu = menuBar()->addMenu(tr("&Window"));
    windowMenu->addAction(showComparisonTable);
	
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

void NERMainWindow::createDockableWidgets()
{
    projectPropertiesDockWidget = new QDockWidget(tr("Project Details"));
    projectPropertiesDockWidget->setObjectName("projectTreeDockWidget");
    projectPropertiesDockWidget->setWidget(propertiesTreeWidget);
    projectPropertiesDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea
                                                 | Qt::RightDockWidgetArea);
    projectPropertiesDockWidget->setToolTip(tr("Project Details"));
    projectPropertiesDockWidget->setMinimumWidth(150);
    projectPropertiesDockWidget->setMaximumWidth(850);
    projectPropertiesDockWidget->setWindowIcon(QIcon(":/resources/pics/docs.png"));

    addDockWidget(Qt::RightDockWidgetArea, projectPropertiesDockWidget);
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

void NERMainWindow::viewProjectPropertiesSlot()
{

}

void NERMainWindow::enableActionsTransLoaded(){

}

void NERMainWindow::loadTranscriptionFileSlot()
{

    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Open TRS File"),
            QDir::currentPath(),
            tr("TRS file (*.trs)") );

    transcriptionList->clear();

    isTranscriptionLoaded = xmlHandler->readTranscriberXML(fileName, transcriptionList);

    if(isTranscriptionLoaded){
        diffTableWid->deleteTablesContents();
        diffTableWid->loadXMLData(transcriptionList);
    }
}

void NERMainWindow::loadSubtitlesFileSlot(){
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Open TRS File"),
            QDir::currentPath(),
            tr("TRS file (*.trs)") );
    QList<BlockTRS> *trsList = new QList<BlockTRS>();
    xmlHandler->readTranscriberXML(fileName, trsList);
    diffTableWid->loadSubtitlesXMLData(transcriptionList, trsList);
    delete trsList;
    trsList = NULL;
}

void NERMainWindow::showComparisonTableSlot(){

}
























