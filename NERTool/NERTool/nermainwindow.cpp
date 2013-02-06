#include "nermainwindow.h"
#include "ui_nermainwindow.h"


/*******************************************************************************
 * NER Main Application Window
 ******************************************************************************/
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

}

NERMainWindow::~NERMainWindow()
{
    delete transcriptionList;
    delete xmlHandler;

}


/*******************************************************************************
 * Creates and initializes main application widgets.
 ******************************************************************************/
void NERMainWindow::createGuiElements()
{
    xmlHandler = new XMLHandler();
    transcriptionList = new QList<BlockTRS>();
    speakerList = new QList<Speaker>();
    nerTablesList = new QList<NERTableWidget*>();

	mainMdiArea = new QMdiArea(this);
    diffTableWid = new NERTableWidget(this);

    //mapTableContentTree = new QMap<QTreeWidgetItem*, NERTableWidget*>();

//    subWindowDiffTable = mainMdiArea->addSubWindow(diffTableWid,
//                                                   Qt::CustomizeWindowHint
//                                                   | Qt::WindowTitleHint
//                                                   | Qt::WindowMinMaxButtonsHint);

//    subWindowDiffTable->setWindowTitle("Trancription Data");
//    subWindowDiffTable->setMinimumSize(800,600);

    propertiesTreeWidget = new PropertiesTreeWidget(this);

    mediaMngWidget = new MediaMngWidget(this);

}

/*******************************************************************************
 * Initiatlizes associated widget actions, connecting them to the management
 * slots.
 ******************************************************************************/
void NERMainWindow::createActions()
{
    newProjectAction = new QAction(tr("&New Project..."), this);
    newProjectAction->setShortcut(QKeySequence::New);
    newProjectAction->setIcon(QIcon(":/resources/pics/new.png"));
    newProjectAction->setStatusTip("Creates a new project");
    connect(newProjectAction, SIGNAL(triggered()),
            this, SLOT(newProjectSlot()));

    openProjectAction = new QAction(tr("&Open Project..."), this);
    openProjectAction->setShortcut(QKeySequence::Open);
    openProjectAction->setIcon(QIcon(":/resources/pics/open.png"));
    openProjectAction->setStatusTip("Opens an existing project");
    connect(openProjectAction, SIGNAL(triggered()),
            this, SLOT(openProjectSlot()));

    saveProjectAction = new QAction(tr("&Save Project..."), this);
	saveProjectAction->setShortcut(QKeySequence::Save);
    saveProjectAction->setIcon(QIcon(":/resources/pics/save.png"));
    saveProjectAction->setStatusTip("Saves the current project");
    connect(saveProjectAction, SIGNAL(triggered()),
            this, SLOT(saveProjectSlot()));

	closeProjectAction = new QAction(tr("&Close Project"), this);
    closeProjectAction->setShortcut(QKeySequence("Ctrl+Q"));
	closeProjectAction->setIcon(QIcon(":/resources/pics/close.png"));
	closeProjectAction->setStatusTip("Closes Current Project");
    connect(closeProjectAction, SIGNAL(triggered()),
            this, SLOT(closeProjectSlot()));

	aboutAction = new QAction(tr("&About"), this);
    aboutAction->setShortcut(QKeySequence("Ctrl+A"));
	aboutAction->setIcon(QIcon(":/resources/pics/about.png"));
	aboutAction->setStatusTip("About this application");
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(aboutSlot()));

    aboutQTAction = new QAction(tr("&About QT"), this);
	aboutQTAction->setShortcut(QKeySequence("Ctrl+I"));
	aboutQTAction->setIcon(QIcon(":/resources/pics/qt-logo.png"));
	aboutQTAction->setStatusTip("About QT Framework");
    connect(aboutQTAction, SIGNAL(triggered()),
            this, SLOT(aboutQTSlot()));

	closeAppAction = new QAction(tr("&Exit"), this);
    closeAppAction->setShortcut(QKeySequence("Alt+F4"));
	closeAppAction->setIcon(QIcon(":/resources/pics/closeApp.png"));
	closeAppAction->setStatusTip("About this application");
    connect(closeAppAction, SIGNAL(triggered()),
            this, SLOT(closeApplicationSlot()));

    viewPropertiesTree = new QAction(tr("&Project Properties"),this);
    viewPropertiesTree->setShortcut(QKeySequence("Ctrl+P"));
    viewPropertiesTree->setIcon(QIcon(":/resources/pics/properties.png"));
    viewPropertiesTree->setStatusTip("Project Properties");
    connect(viewPropertiesTree, SIGNAL(triggered()),
            this, SLOT(viewProjectPropertiesSlot()));

    loadTransXmlFile = new QAction(tr("Load Transcription"), this);
    loadTransXmlFile->setShortcut(QKeySequence("Ctrl+T"));
    loadTransXmlFile->setStatusTip("Load transcription file...");
    connect(loadTransXmlFile, SIGNAL(triggered()),
            this, SLOT(loadTranscriptionFileSlot()));

    loadSubtsXmlFile = new QAction(tr("Load Subtitles"), this);
    loadSubtsXmlFile->setShortcut(QKeySequence("Ctrl+U"));
    loadSubtsXmlFile->setStatusTip("Load subtitles file...");
    loadSubtsXmlFile->setEnabled(false);
    connect(loadSubtsXmlFile, SIGNAL(triggered()),
            this, SLOT(loadSubtitlesFileSlot()));

    cascadeSubWindowsAction = new QAction(tr("C&ascade windows"),this);
    cascadeSubWindowsAction->setStatusTip(tr("Cascade all windows"));
    cascadeSubWindowsAction->setEnabled(true);
    connect(cascadeSubWindowsAction, SIGNAL(triggered()), this, SLOT(cascadeWindowsSlot()));

    tileSubWindowsAction = new QAction(tr("&Tile windows"), this);
    tileSubWindowsAction->setStatusTip(tr("Tile all windows"));
    tileSubWindowsAction->setEnabled(true);
    connect(tileSubWindowsAction, SIGNAL(triggered()), this, SLOT(tileWindowsSlot()));

    showComparisonTable = new QAction(tr("Comparison Table"), this);
    showComparisonTable->setStatusTip(tr("Comparison Table"));
    connect(showComparisonTable, SIGNAL(triggered()),
            this, SLOT(showComparisonTableSlot()));

}


/*******************************************************************************
 * Manages application top menu handlers
 ******************************************************************************/
void NERMainWindow::createMenus()
{
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
    windowMenu->addAction(cascadeSubWindowsAction);
    windowMenu->addAction(tileSubWindowsAction);
	
	helpMenu = menuBar()->addMenu(tr("Help"));
	helpMenu->addAction(aboutQTAction);
	helpMenu->addAction(aboutAction);
}

/*******************************************************************************
 * Manages application top menu toolbar icons.
 ******************************************************************************/
void NERMainWindow::createToolBars()
{
    fileToolbar = addToolBar(tr("&File"));
    fileToolbar->addAction(newProjectAction);
    fileToolbar->addAction(openProjectAction);
    fileToolbar->addAction(saveProjectAction);
    fileToolbar->addAction(closeProjectAction);
	fileToolbar->addAction(aboutAction);
}

/*******************************************************************************
 * Manages application bottom status bar for displying actions hints.
 ******************************************************************************/
void NERMainWindow::createStatusBar()
{
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


/*******************************************************************************
 * Creates and initializes the dockable widgets of the main application.
 ******************************************************************************/
void NERMainWindow::createDockableWidgets()
{
    projectPropertiesDockWidget = new QDockWidget(tr("Project Details"));
    projectPropertiesDockWidget->setObjectName("projectTreeDockWidget");
    projectPropertiesDockWidget->setWidget(propertiesTreeWidget);
    projectPropertiesDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    projectPropertiesDockWidget->setToolTip(tr("Project Details"));
    projectPropertiesDockWidget->setMinimumWidth(150);
    projectPropertiesDockWidget->setMaximumWidth(850);
    projectPropertiesDockWidget->setWindowIcon(QIcon(":/resources/pics/docs.png"));

    addDockWidget(Qt::RightDockWidgetArea, projectPropertiesDockWidget);

    audioWaveFormDockWidget = new QDockWidget(tr("Media Player"));
    audioWaveFormDockWidget->setObjectName("mediaControlDockWidget");
    audioWaveFormDockWidget->setWidget(mediaMngWidget);
    audioWaveFormDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    audioWaveFormDockWidget->setToolTip(tr("Media player for audio and video content..."));

    addDockWidget(Qt::BottomDockWidgetArea, audioWaveFormDockWidget);

//    videoPlayerDockWidget = new QDockWidget(tr("Video Player"));
//    videoPlayerDockWidget->setObjectName("mediaControlDockWidget");
//    videoPlayerDockWidget->setWidget(mediaMngWidget->getVideoPlayer());
//    videoPlayerDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
//    videoPlayerDockWidget->setToolTip(tr("Video player..."));

//    addDockWidget(Qt::AllDockWidgetAreas, videoPlayerDockWidget, Qt::Vertical);


}


/*******************************************************************************
 * Creates and initializes a new NER project, and closing a current open one.
 ******************************************************************************/
void NERMainWindow::newProjectSlot()
{

}

/*******************************************************************************
 * Save current project, and export XML file.
 ******************************************************************************/
void NERMainWindow::saveProjectSlot()
{
    QString xmlFileName = QFileDialog::getSaveFileName(
            this,
            tr("Save NER Project"),
            QDir::currentPath(),
            tr("NER Files (*.xner)"));

    if(xmlFileName.isEmpty()){
        return; //Nothing to do.
    }

    xmlHandler->writeProjectExportXML(xmlFileName,
                                      speakerList,
                                      transcriptionList,
                                      nerTablesList);

}

/*******************************************************************************
 * Opens an existing NER project file.
 ******************************************************************************/
void NERMainWindow::openProjectSlot()
{

}

/*******************************************************************************
 * Closest the current open project and all the associated widgets.
 ******************************************************************************/
void NERMainWindow::closeProjectSlot()
{

}

/*******************************************************************************
 * Close the NER application.
 ******************************************************************************/
void NERMainWindow::closeApplicationSlot()
{
    QApplication::exit(0);
}

/*******************************************************************************
 * Show QT information slot.
 ******************************************************************************/
void NERMainWindow::aboutQTSlot()
{
    QApplication::aboutQt();
}

/*******************************************************************************
 * Show some Ner info.
 ******************************************************************************/
void NERMainWindow::aboutSlot()
{
    About *aboutDialog = new About(this);
	aboutDialog->setAttribute(Qt::WA_DeleteOnClose);
	aboutDialog->show();
}

void NERMainWindow::initializeMDIWindows()
{
    //subWindowDiffTable->showNormal();

}

void NERMainWindow::viewProjectPropertiesSlot()
{

}

void NERMainWindow::enableActionsTransLoaded(){

}

/*******************************************************************************
 * Loads a "transcriber" XML file importing it to NER table.
 ******************************************************************************/
void NERMainWindow::loadTranscriptionFileSlot()
{

    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Open TRS File"),
            QDir::currentPath(),
            tr("TRS file (*.trs)") );

    if(fileName.isEmpty()){
        return; //Nothing to do...
    }

    transcriptionList->clear();
    speakerList->clear();

    isTranscriptionLoaded = xmlHandler->readTranscriberXML(fileName, transcriptionList, speakerList);

    QString s;
    QFileInfo info(fileName);
    QString baseName = info.baseName();
    propertiesTreeWidget->insertNewTranslation(baseName, s, s);
    loadSubtsXmlFile->setEnabled(true);

}

void NERMainWindow::addNewTableAndTreeNode()
{


}

/*******************************************************************************
 * Loads a "transcriber" XML file containing "subtitle" content.
 ******************************************************************************/
void NERMainWindow::loadSubtitlesFileSlot(){
    QStringList fileNames = QFileDialog::getOpenFileNames(
            this,
            tr("Open TRS File"),
            QDir::currentPath(),
            tr("TRS file (*.trs)") );

    if(fileNames.count()==0){
        return; //Nothing to do...
    }


    //Multiple file loading...
    for(int i=0; i<fileNames.count(); i++){

        //Load XML
        QList<BlockTRS> *trsList = new QList<BlockTRS>();
        QString file = fileNames.at(i);

        bool loaded = xmlHandler->readSubtitleXML(file, trsList);
        if(!loaded){
            //Check if XML file is OK.
            QMessageBox box;
            box.setWindowTitle("File loading failed!");
            QString detail;
            detail.append("Import of ")
                    .append(file)
                    .append(" XML failed. This file was ignored.");
            box.setInformativeText(detail);
            box.setIcon(QMessageBox::Warning);
            box.setStandardButtons(QMessageBox::Ok);
            box.exec();

            continue; //proceed to next file...
        }

        NERTableWidget *table = new NERTableWidget(this);
        table->deleteTablesContents();
        table->loadXMLData(transcriptionList);
        table->loadSubtitlesXMLData(transcriptionList, trsList);

        //Append this loaded subtitles to the global list.
        nerTablesList->append(table);

        //Add a new subwindow
        QMdiSubWindow *subWindow = mainMdiArea->addSubWindow(table,
                                                             /*Qt::CustomizeWindowHint
                                                                                                              |*/ Qt::WindowTitleHint
                                                             | Qt::WindowMinMaxButtonsHint
                                                             | Qt::WindowCloseButtonHint);
        QString title;
        QFileInfo info(file);
        title.append(info.baseName());

        //Display new subwindow
        subWindow->setWindowTitle(title);
        subWindow->setMinimumSize(800,600);
        subWindow->showNormal();

        QString s;

        //Insert new item in the tree...
        propertiesTreeWidget->insertNewSubtitle(title, s, s);

        delete trsList;
        trsList = NULL;
    }
}

void NERMainWindow::showComparisonTableSlot(){

}

void NERMainWindow::cascadeWindowsSlot()
{
    mainMdiArea->cascadeSubWindows();
}

void NERMainWindow::tileWindowsSlot()
{
    mainMdiArea->tileSubWindows();
}
























