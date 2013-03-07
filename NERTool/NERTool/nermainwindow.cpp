#include "nermainwindow.h"
#include "ui_nermainwindow.h"
#include "nergraphwidget.h"

/*******************************************************************************
 * NER Main Application Window
 ******************************************************************************/
NERMainWindow::NERMainWindow(QWidget *parent) : QMainWindow(parent)
{
	resize(1024,768);
    setWindowTitle(NER_APP_NAME);

    projectSaveFilePath = new QString();
	createGuiElements();
    createDockableWidgets();
    showDockableWidgets(false);
	createActions();
    enableActions(false);
	createMenus();
	createToolBars();
	createStatusBar();

    isProjectloaded = false;
    isTranscriptionLoaded = false;
    isSubtitlesLoaded = false;

	setCentralWidget(mainMdiArea);

	initializeMDIWindows();

    QString s1 = "First line of text";
    QString s2 = "Second time line of the text";

    diff_match_patch diff;
    QList<Diff> list = diff.diff_main(s1,s2, false);

    for(int i=0;i<list.count(); i++){
        Diff d = list.at(i);
        ENGINE_DEBUG << i << d.toString();
    }

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
    xmlHandler = new XMLHandler(this);
    transcriptionList = new QList<BlockTRS>();
    speakerList = new QList<Speaker>();
    nerTablesList = new QList<NERTableWidget*>();

	mainMdiArea = new QMdiArea(this);

    propertiesTreeWidget = new PropertiesTreeWidget(this);

    mediaMngWidget = new MediaMngWidget(this, mainMdiArea);

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
    saveProjectAction->setStatusTip("Save the current project");
    connect(saveProjectAction, SIGNAL(triggered()),
            this, SLOT(saveProjectSlot()));

    saveAsProjectAction = new QAction(tr("&Save as Project..."), this);
    saveAsProjectAction->setShortcut(QKeySequence::Save);
    saveAsProjectAction->setIcon(QIcon(":/resources/pics/save.png"));
    saveAsProjectAction->setStatusTip("Save As the current project");
    connect(saveAsProjectAction, SIGNAL(triggered()),
            this, SLOT(saveAsProjectSlot()));

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

    viewPropertiesDockAction = projectPropertiesDockWidget->toggleViewAction();
    viewPropertiesDockAction->setIcon(QIcon(":/resources/pics/docs.png"));

    viewVideoPlayerDockAction = audioWaveFormDockWidget->toggleViewAction();
    viewVideoPlayerDockAction->setIcon(QIcon(":/resources/pics/video_player.png"));

    showVideoAction = videoPlayerDockWidget->toggleViewAction();
    showVideoAction->setStatusTip(tr("Show video..."));

}

void NERMainWindow::enableActions(bool enable)
{
    saveProjectAction->setEnabled(enable);
    loadSubtsXmlFile->setEnabled(enable);
    loadTransXmlFile->setEnabled(enable);
    saveAsProjectAction->setEnabled(enable);
    closeProjectAction->setEnabled(enable);
    viewPropertiesDockAction->setEnabled(enable);
    viewVideoPlayerDockAction->setEnabled(enable);
    showVideoAction->setEnabled(enable);
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
    fileMenu->addAction(saveAsProjectAction);
    fileMenu->addAction(closeProjectAction);
	fileMenu->addAction(closeAppAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(viewPropertiesTree);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(loadTransXmlFile);
    toolsMenu->addAction(loadSubtsXmlFile);

	windowMenu = menuBar()->addMenu(tr("&Window"));
    windowMenu->addAction(cascadeSubWindowsAction);
    windowMenu->addAction(tileSubWindowsAction);
    windowMenu->addSeparator();
    windowMenu->addAction(viewPropertiesDockAction);
    windowMenu->addAction(viewVideoPlayerDockAction);
	
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
    fileToolbar->addAction(viewVideoPlayerDockAction);
    fileToolbar->addAction(viewPropertiesDockAction);
    fileToolbar->addAction(showVideoAction);
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

    QDesktopWidget *mydesk = QApplication::desktop();
    int docksWidth = 0.30 * mydesk->width();

    projectPropertiesDockWidget = new QDockWidget(tr("Project Details"));
    projectPropertiesDockWidget->setObjectName("projectTreeDockWidget");
    projectPropertiesDockWidget->setWidget(propertiesTreeWidget);
    projectPropertiesDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    projectPropertiesDockWidget->setToolTip(tr("Project Details"));
    projectPropertiesDockWidget->setFixedWidth(docksWidth);
    projectPropertiesDockWidget->setWindowIcon(QIcon(":/resources/pics/docs.png"));
    addDockWidget(Qt::RightDockWidgetArea, projectPropertiesDockWidget);

    audioWaveFormDockWidget = new QDockWidget(tr("Media Player"));
    audioWaveFormDockWidget->setObjectName("mediaControlDockWidget");
    audioWaveFormDockWidget->setWidget(mediaMngWidget);
    audioWaveFormDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    audioWaveFormDockWidget->setToolTip(tr("Media player for audio and video content..."));
    addDockWidget(Qt::BottomDockWidgetArea, audioWaveFormDockWidget);


    videoPlayerDockWidget = new QDockWidget(tr("Video Player"));
    videoPlayerDockWidget->setObjectName("videoControlDockWidget");
    videoPlayerDockWidget->setWidget(mediaMngWidget->getVideoWindow());
    videoPlayerDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea
                                           | Qt::RightDockWidgetArea
                                           | Qt::TopDockWidgetArea);
    videoPlayerDockWidget->setToolTip(tr("Video window..."));
    videoPlayerDockWidget->setFixedWidth(docksWidth);
    videoPlayerDockWidget->setFixedHeight(0.75*docksWidth);
    videoPlayerDockWidget->setAutoFillBackground(true);
    QPalette bvidpalette = videoPlayerDockWidget->palette();
    bvidpalette.setColor(QPalette::Window, Qt::black);
    videoPlayerDockWidget->setPalette(bvidpalette);
    addDockWidget(Qt::RightDockWidgetArea, videoPlayerDockWidget);


}

void NERMainWindow::showDockableWidgets(bool enable)
{
    if(enable){
        projectPropertiesDockWidget->show();
        audioWaveFormDockWidget->show();
        videoPlayerDockWidget->show();
    }
    else{
        projectPropertiesDockWidget->hide();
        audioWaveFormDockWidget->hide();
        videoPlayerDockWidget->hide();
    }
}


/*******************************************************************************
 * Creates and initializes a new NER project, and closing a current open one.
 ******************************************************************************/
void NERMainWindow::newProjectSlot()
{
    enableActions(true);
    closeProjectSlot();
    isProjectloaded = true;
    showDockableWidgets(true);
}

/*******************************************************************************
 * Save current project, and export XML file.
 ******************************************************************************/
void NERMainWindow::saveProjectSlot()
{
    if(projectSaveFilePath->isEmpty()){
        QString xmlFileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Save NER Project"),
                    QDir::currentPath(),
                    tr("NER Files (*.xner)"));

        if(!xmlFileName.endsWith(".xner")){
            xmlFileName.append(".xner");
        }

        *projectSaveFilePath = xmlFileName;
    }

    if(projectSaveFilePath->isEmpty()){
        return; //Nothing to do.
    }

    xmlHandler->writeProjectExportXML(*projectSaveFilePath,
                                      speakerList,
                                      transcriptionList,
                                      propertiesTreeWidget->getTranslationNode(),
                                      propertiesTreeWidget->getTreeSubWindowsMap());

}

/*******************************************************************************
 * Save As current project, and export XML file.
 ******************************************************************************/
void NERMainWindow::saveAsProjectSlot()
{
    QString xmlFileName = QFileDialog::getSaveFileName(
            this,
            tr("Save NER Project"),
            QDir::currentPath(),
            tr("NER Files (*.xner)"));

    if(xmlFileName.isEmpty()){
        return; //Nothing to do.
    }

    if(!xmlFileName.endsWith(".xner")){
        xmlFileName.append(".xner");
    }

    xmlHandler->writeProjectExportXML(xmlFileName,
                                      speakerList,
                                      transcriptionList,
                                      propertiesTreeWidget->getTranslationNode(),
                                      propertiesTreeWidget->getTreeSubWindowsMap());

}

/*******************************************************************************
 * Opens an existing NER project file.
 ******************************************************************************/
void NERMainWindow::openProjectSlot()
{
    QString xmlFileName = QFileDialog::getOpenFileName(
            this,
            tr("Open NER Project"),
            QDir::currentPath(),
            tr("NER Files (*.xner)"));

    if(xmlFileName.isEmpty()){
        return; //Nothing to do.
    }

    ENGINE_DEBUG << "open project";

    *projectSaveFilePath = xmlFileName;

    xmlHandler->readProjectExportXML(xmlFileName,
                                     speakerList,
                                     transcriptionList,
                                     nerTablesList,
                                     mediaMngWidget,
                                     propertiesTreeWidget);

    for(int i=0; i<nerTablesList->count(); i++){
        ENGINE_DEBUG << "Table insertion";

        NERTableWidget* table = nerTablesList->at(i);
        addTableInMdiArea(table, table->getTableName());
    }

    loadSubtsXmlFile->setEnabled(true);

    enableActions(true);
    showDockableWidgets(true);
    isProjectloaded=true;

}

/*******************************************************************************
 * Closest the current open project and all the associated widgets.
 ******************************************************************************/
void NERMainWindow::closeProjectSlot()
{
    if(!isProjectloaded){
        return;
    }

    QMessageBox box;
    box.setInformativeText("Are you sure ?\nAll unsaved modifications will be lost!");
    box.setText("Close project                                           ");
    box.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    box.setIcon(QMessageBox::Question);
    box.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    int result = box.exec();
    switch (result){
    case QMessageBox::No :
        return;
    }

    speakerList->clear();
    transcriptionList->clear();

    //Close subwindows and free memory...
    mainMdiArea->closeAllSubWindows();
    int numOfTables = nerTablesList->count();
    for(int i=0; i<numOfTables;i++){
        NERTableWidget *tableToRemove = nerTablesList->first();
        mainMdiArea->removeSubWindow(tableToRemove);
    }
    nerTablesList->clear();

    //Stop media playing...
    mediaMngWidget->stopMediaFileSlot();

    //Remove tree child nodes...
    propertiesTreeWidget->clearAllTreeData();
    propertiesTreeWidget->getTreeSubWindowsMap()->clear();

    isTranscriptionLoaded = false;
    isSubtitlesLoaded = false;
    isProjectloaded = false;
    enableActions(false);
    showDockableWidgets(false);



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

    if(isTranscriptionLoaded && isSubtitlesLoaded){
        QMessageBox box;
        box.setText("Do you wish to reload Transcription table ?");
        box.setInformativeText("This will delete any Subtitle tables loaded and cannot be undone!\nProceed ?");
        box.setBaseSize(150,60);
        box.setIcon(QMessageBox::Warning);
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        box.setDefaultButton(QMessageBox::No);
        int ret = box.exec();
        switch (ret) {
        case QMessageBox::No:
            return;//cancel all this...
        case QMessageBox::Yes:
            propertiesTreeWidget->removeAllSubNodes();
            isSubtitlesLoaded = false;
            break;
        default:
            // should never be reached
            break;
        }
    }

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

    isTranscriptionLoaded = xmlHandler->readTranscriberXML(fileName,
                                                           transcriptionList,
                                                           speakerList);

    QString s;
    QFileInfo info(fileName);
    QString baseName = info.baseName();
    propertiesTreeWidget->insertNewTranslation(baseName, s, s);
    loadSubtsXmlFile->setEnabled(true);

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
        table->setMediaWidget(mediaMngWidget);
        table->deleteTablesContents();
        table->loadXMLData(transcriptionList);
        table->loadSubtitlesXMLData(transcriptionList, trsList);

        //Append this loaded subtitles to the global list.
        nerTablesList->append(table);

        QString title;
        QFileInfo info(file);
        title.append(info.baseName());

        addTableInMdiArea(table, title);

        isSubtitlesLoaded = true;


        delete trsList;
        trsList = NULL;
    }
}

void NERMainWindow::addTableInMdiArea(NERTableWidget* table, QString title)
{
    //Add a new subwindow
    QMdiSubWindow *subWindow = mainMdiArea->addSubWindow(table,
                                                         /*Qt::CustomizeWindowHint
                                                           |*/ Qt::WindowTitleHint
                                                         | Qt::WindowMinMaxButtonsHint
                                                         | Qt::WindowCloseButtonHint);

    //Display new subwindow
    subWindow->setWindowTitle(title);
    subWindow->setMinimumSize(800,600);
    subWindow->show();

    QString s;

    //Insert new item in the tree...
    propertiesTreeWidget->insertNewSubtitle(title, subWindow, s, s);
}


void NERMainWindow::cascadeWindowsSlot()
{
    mainMdiArea->cascadeSubWindows();
}

void NERMainWindow::tileWindowsSlot()
{
    mainMdiArea->tileSubWindows();
}
























