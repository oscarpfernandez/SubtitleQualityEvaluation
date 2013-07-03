#include "nermainwindow.h"
#include "ui_nermainwindow.h"


/*******************************************************************************
 * NER Main Application Window
 ******************************************************************************/
NERMainWindow::NERMainWindow(QWidget *parent) : QMainWindow(parent)
{
	resize(1024,768);
    setWindowTitle(NER_APP_NAME);

    licenceMng = new LicenceManager(parent);

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

}

NERMainWindow::~NERMainWindow()
{
    delete transcriptionList;
    delete xmlHandler;
}

void NERMainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    QMessageBox box;
    box.setInformativeText("Exit Application ?\nAll unsaved modifications will be lost!");
    box.setText("Close Application                                      ");
    box.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    box.setIcon(QMessageBox::Question);
    box.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    int result = box.exec();
    switch (result){
    case QMessageBox::No :
        break;
    case QMessageBox::Yes :
        event->accept();
        break;
    }
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

    nerSummary = new NERSummaryWidget(this);
    connect(nerSummary, SIGNAL(computeNERValues()),
            this, SLOT(computerNERStatistics()));
    connect(this, SIGNAL(setNERStatistics(NERStatsData&)),
            nerSummary, SLOT(setNERStatistics(NERStatsData&)));
    connect(nerSummary, SIGNAL(viewNerStats()), this, SLOT(showNerStatsWindow()));

    nerStatsViewer = new NERStatsViewerWidget();
    connect(nerStatsViewer, SIGNAL(refreshNERData()), this, SLOT(showNerStatsWindow()));

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
    saveAsProjectAction->setShortcut(QKeySequence::SaveAs);
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
    closeAppAction->setShortcut(QKeySequence::Quit);
	closeAppAction->setIcon(QIcon(":/resources/pics/closeApp.png"));
	closeAppAction->setStatusTip("About this application");
    connect(closeAppAction, SIGNAL(triggered()),
            this, SLOT(closeApplicationSlot()));

    viewPropertiesTree = new QAction(tr("&Project Properties"),this);
    viewPropertiesTree->setShortcut(QKeySequence("Ctrl+P"));
    viewPropertiesTree->setIcon(QIcon(":/resources/pics/properties.png"));
    viewPropertiesTree->setStatusTip("Project Properties");
//    connect(viewPropertiesTree, SIGNAL(triggered()),
//            this, SLOT(viewProjectPropertiesSlot()));

    loadTransXmlFile = new QAction(tr("Load Transcription"), this);
    loadTransXmlFile->setShortcut(QKeySequence("Ctrl+T"));
    loadTransXmlFile->setStatusTip("Load transcription file...");
    connect(loadTransXmlFile, SIGNAL(triggered()),
            this, SLOT(loadTranscriptionFileSlot()));

    loadTransSRTFile = new QAction(tr("Load SRT Transcription"), this);
    loadTransSRTFile->setShortcut(QKeySequence("Ctrl+Y"));
    loadTransSRTFile->setStatusTip(tr("Load SRT Trancription File..."));
    connect(loadTransSRTFile, SIGNAL(triggered()), this, SLOT(loadSRTTranscriptionFileSlot()));

    loadSubtsXmlFile = new QAction(tr("Load TRS Subtitles"), this);
    loadSubtsXmlFile->setShortcut(QKeySequence("Ctrl+U"));
    loadSubtsXmlFile->setStatusTip("Load subtitles file...");
    loadSubtsXmlFile->setEnabled(false);
    connect(loadSubtsXmlFile, SIGNAL(triggered()),
            this, SLOT(loadSubtitlesFileSlot()));

    loadSRTXmlFile = new QAction(tr("Load SRT Subtitles"), this);
    loadSRTXmlFile->setShortcut(QKeySequence("Ctrl+U"));
    loadSRTXmlFile->setStatusTip("Load subtitles file...");
    loadSRTXmlFile->setEnabled(false);
    connect(loadSRTXmlFile, SIGNAL(triggered()),
            this, SLOT(loadSRTSubtitlesFileSlot()));

    cascadeSubWindowsAction = new QAction(tr("C&ascade windows"),this);
    cascadeSubWindowsAction->setStatusTip(tr("Cascade all windows"));
    cascadeSubWindowsAction->setEnabled(true);
    connect(cascadeSubWindowsAction, SIGNAL(triggered()), this, SLOT(cascadeWindowsSlot()));

    tileSubWindowsAction = new QAction(tr("&Tile windows"), this);
    tileSubWindowsAction->setStatusTip(tr("Tile all windows"));
    tileSubWindowsAction->setEnabled(true);
    connect(tileSubWindowsAction, SIGNAL(triggered()), this, SLOT(tileWindowsSlot()));

    computerNerStats = new QAction(tr("Calculate NER"), this);
    computerNerStats->setStatusTip(tr("Computer the NER statistics..."));
    computerNerStats->setEnabled(false);
    connect(computerNerStats, SIGNAL(triggered()), this, SLOT(computerNERStatistics()));

    viewPropertiesDockAction = projectPropertiesDockWidget->toggleViewAction();
    viewPropertiesDockAction->setIcon(QIcon(":/resources/pics/docs.png"));

    viewVideoPlayerDockAction = audioWaveFormDockWidget->toggleViewAction();
    viewVideoPlayerDockAction->setIcon(QIcon(":/resources/pics/video_player.png"));

    showVideoAction = videoPlayerDockWidget->toggleViewAction();
    showVideoAction->setStatusTip(tr("Show video..."));
    showVideoAction->setIcon(QIcon(":/resources/pics/video_display.png"));

    showNerSummaryAction = nerStatsDockWidget->toggleViewAction();
    showNerSummaryAction->setStatusTip(tr("Show a NER statistics summary."));
    showNerSummaryAction->setIcon(QIcon(":/resources/pics/stats.png"));

    recomputeTableDifferences = new QAction(tr("Recompute Diff"), this);
    recomputeTableDifferences->setStatusTip(tr("Recompute table difference by performing a diff..."));
    recomputeTableDifferences->setEnabled(false);
    connect(recomputeTableDifferences, SIGNAL(triggered()), this, SLOT(recomputeTableDiff()));

    generateNerReport = new QAction(tr("Generate Report"), this);
    generateNerReport-> setStatusTip(tr("Generate NER final report"));
    generateNerReport->setEnabled(false);
    connect(generateNerReport, SIGNAL(triggered()), this, SLOT(generateNERReport()));

}

void NERMainWindow::enableActions(bool enable)
{
    saveProjectAction->setEnabled(enable);
    loadTransXmlFile->setEnabled(enable);
    loadTransSRTFile->setEnabled(enable);
    saveAsProjectAction->setEnabled(enable);
    closeProjectAction->setEnabled(enable);
    viewPropertiesDockAction->setEnabled(enable);
    viewVideoPlayerDockAction->setEnabled(enable);
    showVideoAction->setEnabled(enable);
    computerNerStats->setEnabled(enable);
    showNerSummaryAction->setEnabled(enable);
    generateNerReport->setEnabled(enable);
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

    //viewMenu = menuBar()->addMenu(tr("&View"));
    //viewMenu->addAction(viewPropertiesTree);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    transcMenu = new QMenu(tr("Load Transcription"), this);
    transcMenu->addAction(loadTransXmlFile);
    transcMenu->addAction(loadTransSRTFile);

    subTitlesMenu = new QMenu(tr("Load Subtitles"), this);
    subTitlesMenu->addAction(loadSubtsXmlFile);
    subTitlesMenu->addAction(loadSRTXmlFile);

    toolsMenu->addMenu(transcMenu);
    toolsMenu->addMenu(subTitlesMenu);
    toolsMenu->addSeparator();
    toolsMenu->addAction(computerNerStats);
    toolsMenu->addAction(recomputeTableDifferences);
    toolsMenu->addSeparator();
    toolsMenu->addAction(generateNerReport);

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
    fileToolbar->addAction(showVideoAction);
    fileToolbar->addAction(viewPropertiesDockAction);
    fileToolbar->addAction(showNerSummaryAction);
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
    int valWidth = mydesk->width();
    if(valWidth > 1024){
        valWidth = 1024;
    }
    int docksWidth = 0.30 * valWidth;

    projectPropertiesDockWidget = new QDockWidget(tr("Project Details"));
    projectPropertiesDockWidget->setObjectName("projectTreeDockWidget");
    projectPropertiesDockWidget->setWidget(propertiesTreeWidget);
    projectPropertiesDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    projectPropertiesDockWidget->setToolTip(tr("Project Details"));
    projectPropertiesDockWidget->setMinimumWidth(docksWidth);
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
    videoPlayerDockWidget->setMinimumWidth(docksWidth);
    videoPlayerDockWidget->setMinimumHeight(0.75*docksWidth);
    videoPlayerDockWidget->setAutoFillBackground(true);
    QPalette bvidpalette = videoPlayerDockWidget->palette();
    bvidpalette.setColor(QPalette::Window, Qt::black);
    videoPlayerDockWidget->setPalette(bvidpalette);
    addDockWidget(Qt::RightDockWidgetArea, videoPlayerDockWidget);

    nerStatsDockWidget = new QDockWidget("NER Stats Summary");
    nerStatsDockWidget->setWidget(nerSummary);
    nerStatsDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    nerStatsDockWidget->setWindowIcon(QIcon(":/resources/pics/stats.png"));
    addDockWidget(Qt::BottomDockWidgetArea, nerStatsDockWidget);

}

void NERMainWindow::showDockableWidgets(bool enable)
{
    if(enable){
        projectPropertiesDockWidget->show();
        audioWaveFormDockWidget->show();
        videoPlayerDockWidget->show();
        nerStatsDockWidget->show();
    }
    else{
        projectPropertiesDockWidget->hide();
        audioWaveFormDockWidget->hide();
        videoPlayerDockWidget->hide();
        nerStatsDockWidget->hide();
    }
}


/*******************************************************************************
 * Creates and initializes a new NER project, and closing a current open one.
 ******************************************************************************/
void NERMainWindow::newProjectSlot()
{
    closeProjectSlot();
    enableActions(true);
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
    int numOfWindows = mainMdiArea->subWindowList().count();

    if(isProjectloaded && numOfWindows>0){
        QMessageBox box;
        box.setInformativeText("Close current project?\nAll unsaved modifications will be lost!");
        box.setText("Close project                                           ");
        box.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        box.setIcon(QMessageBox::Question);
        box.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        int result = box.exec();
        switch (result){
        case QMessageBox::No :
            return;
        case QMessageBox::Yes :
            closeProjectSlot();
        }
    }

    QString xmlFileName = QFileDialog::getOpenFileName(
            this,
            tr("Open NER Project"),
            QDir::currentPath(),
            tr("NER Files (*.xner)"));

    if(xmlFileName.isEmpty()){
        return; //Nothing to do.
    }

    openProjectSetup(xmlFileName);

//    ENGINE_DEBUG << "open project";

//    *projectSaveFilePath = xmlFileName;

//    xmlHandler->readProjectExportXML(xmlFileName,
//                                     speakerList,
//                                     transcriptionList,
//                                     nerTablesList,
//                                     mediaMngWidget,
//                                     propertiesTreeWidget);


//     for(int i=0; i<nerTablesList->count(); i++){
//        ENGINE_DEBUG << "Table insertion";

//        NERTableWidget* table = nerTablesList->at(i);

////        //Reapply differences in the translation side, since this is not saved
////        //because it can be recalculated on-the-fly.
////        QString transText = table->getAllTranslationText();
////        QString subsText = table->getAllSubtableText();
////        QList<Diff> diffList = table->computeDifferences(transText, subsText);
////        QList<Diff> noInsertionsList = table->removeInsertions(diffList);
////        table->applyEditionPropertiesToTranscription(noInsertionsList);

//        addTableInMdiArea(table, table->getTableName());
//    }


//    loadSubtsXmlFile->setEnabled(true);
//    loadSRTXmlFile->setEnabled(true);
//    recomputeTableDifferences->setEnabled(true);

//    enableActions(true);
//    showDockableWidgets(true);
//    isProjectloaded=true;

}

void NERMainWindow::openProjectSetup(QString &xmlFileName)
{
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

//        //Reapply differences in the translation side, since this is not saved
//        //because it can be recalculated on-the-fly.
//        QString transText = table->getAllTranslationText();
//        QString subsText = table->getAllSubtableText();
//        QList<Diff> diffList = table->computeDifferences(transText, subsText);
//        QList<Diff> noInsertionsList = table->removeInsertions(diffList);
//        table->applyEditionPropertiesToTranscription(noInsertionsList);

        addTableInMdiArea(table, table->getTableName());
    }


    loadSubtsXmlFile->setEnabled(true);
    loadSRTXmlFile->setEnabled(true);
    recomputeTableDifferences->setEnabled(true);

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

    int numOfWindows = mainMdiArea->subWindowList().count();

    if(numOfWindows>0){
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
    loadSubtsXmlFile->setEnabled(false);
    loadSRTXmlFile->setEnabled(false);
    showDockableWidgets(false);
    recomputeTableDifferences->setEnabled(false);
    nerStatsViewer->close();

    projectSaveFilePath->clear();



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
    loadSRTXmlFile->setEnabled(true);

}

void NERMainWindow::loadSRTTranscriptionFileSlot()
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
            tr("Open Transcription File"),
            QDir::currentPath(),
            tr("TRS file (*.srt)") );

    if(fileName.isEmpty()){
        return; //Nothing to do...
    }

    transcriptionList->clear();
    speakerList->clear();

    isTranscriptionLoaded = xmlHandler->readSRTTranscription(fileName, transcriptionList);

    QString s;
    QFileInfo info(fileName);
    QString baseName = info.baseName();
    propertiesTreeWidget->insertNewTranslation(baseName, s, s);
    loadSubtsXmlFile->setEnabled(true);
    loadSRTXmlFile->setEnabled(true);
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
            box.setWindowTitle("File loading failed!                         ");
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

        computeWordDifferences(table);

        recomputeTableDifferences->setEnabled(true);

        isSubtitlesLoaded = true;


        delete trsList;
        trsList = NULL;
    }
}

void NERMainWindow::computeWordDifferences(NERTableWidget* table)
{
    if(table==0){
        return;
    }

    QString transText = table->getAllTranslationText();
    transText.remove(".").remove(",").remove("!").remove("¡").remove("?").remove("¿").remove(";").remove(":");
    transText = transText.toLower().simplified();

    QString subsText = table->getAllSubtableText();
    subsText.remove(".").remove(",").remove("!").remove("¡").remove("?").remove("¿").remove(";").remove(":");
    subsText = subsText.toLower().simplified();

    //Computes the diff...
    QList<Diff> diffList = table->computeDifferences(transText, subsText);
    //Removes the deletions from the global comparison string.
    QList<Diff> noDelsList = table->removeDeletions(diffList);

    //Removes the deletions from the global comparison string
    //leaving only deletion and equal.
    QList<Diff> noInsertionsList = table->removeInsertions(diffList);

    QList<DragLabel*> dsubLabsList = table->getAllSubtableLabels();

    ENGINE_DEBUG << "Labels Size" << dsubLabsList.count();
    ENGINE_DEBUG << "Diffs Size = " << noDelsList.count();

    table->applyEditionProperties(noDelsList);
    table->applyEditionPropertiesToTranscription(noInsertionsList);
}

void NERMainWindow::recomputeTableDiff()
{
    if(mainMdiArea->subWindowList().count()==0){
        return;
    }

    QMdiSubWindow* subWindow = mainMdiArea->activeSubWindow();
    NERTableWidget* table = static_cast<NERTableWidget*>(subWindow->widget());

    if(table==0){
        return;
    }

    QMessageBox box;
    box.setInformativeText("Are you sure ?\nAll table errors and weights will be reset!");
    box.setText("Close project                                           ");
    box.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    box.setIcon(QMessageBox::Question);
    box.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    int result = box.exec();
    switch (result){
    case QMessageBox::No :
        return;
    }

    computeWordDifferences(table);
}

void NERMainWindow::generateNERReport()
{

    if(mainMdiArea->subWindowList().count()==0){
        return;
    }

    QString reportFileName = QFileDialog::getSaveFileName(
                this,
                tr("Save NER Export"),
                QDir::currentPath(),
                tr("NER Files (*.htm)"));

    if(!reportFileName.endsWith(".htm")){
        reportFileName.append(".htm");
    }

    if(reportFileName.isEmpty()){
        return;
    }

    computeAllNERStatistics();

    QList<QMdiSubWindow*> subWindowList = mainMdiArea->subWindowList();

    ReportExport::writeHeader(reportFileName);

    for(int i=0; i<subWindowList.count(); i++)
    {
        QMdiSubWindow* subWindow = subWindowList.at(i);
        NERTableWidget* table = static_cast<NERTableWidget*>(subWindow->widget());

        if(table==0){
            continue;
        }

        QFileInfo file(reportFileName);
        QString imgfilePath = file.path();
        QString name = QString::number(QTime::currentTime().second()*1000 + QTime::currentTime().msec());
        name.append(name).append(".jpg");

        imgfilePath.append("/").append(name);

        showNerStatsWindow(table);
        nerStatsViewer->hide();
        QString base64Img = nerStatsViewer->saveWidgetToImg(imgfilePath);

        ReportExport::generateExportFile(reportFileName, base64Img, table);

    }
    ReportExport::writeFooter(reportFileName);
}

/*******************************************************************************
 * Loads a SRT file containing "subtitle" content.
 ******************************************************************************/
void NERMainWindow::loadSRTSubtitlesFileSlot()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
            this,
            tr("Open TRS File"),
            QDir::currentPath(),
            tr("TRS file (*.srt)") );

    if(fileNames.count()==0){
        return; //Nothing to do...
    }


    //Multiple file loading...
    for(int i=0; i<fileNames.count(); i++){

        //Load XML
        QList<BlockTRS> *trsList = new QList<BlockTRS>();
        QString file = fileNames.at(i);

        bool loaded = xmlHandler->readSubtitleSRT(file, trsList);
        if(!loaded){
            //Check if XML file is OK.
            QMessageBox box;
            box.setWindowTitle("File loading failed!                         ");
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

        QString transText = table->getAllTranslationText().simplified();
        QString subsText = table->getAllSubtableText().simplified();

        QList<Diff> diffList = table->computeDifferences(transText, subsText);
        QList<Diff> noDelsList = table->removeDeletions(diffList);

        QList<DragLabel*> dLabsList = table->getAllSubtableLabels();

        ENGINE_DEBUG << "Labels Size" << dLabsList.count();
        ENGINE_DEBUG << "Diffs Size = " << noDelsList.count();

        computeWordDifferences(table);

        recomputeTableDifferences->setEnabled(true);
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

void NERMainWindow::showNerStatsWindow()
{
    if(mainMdiArea->subWindowList().count()==0){
        return;
    }

    QMdiSubWindow* subWindow = mainMdiArea->activeSubWindow();
    NERTableWidget* table = static_cast<NERTableWidget*>(subWindow->widget());

    NERStatsData ner = table->computeNERStats_NerValue();

    nerStatsViewer->clearGraphsData();
    nerStatsViewer->loadGraphsData(ner);
    nerStatsViewer->replotGraphs();
    nerStatsViewer->setWindowFlags(nerStatsViewer->windowFlags() | Qt::Tool);
    nerStatsViewer->show();
}

void NERMainWindow::showNerStatsWindow(NERTableWidget *table)
{
    if(table==0){
        return;
    }

    NERStatsData ner = table->computeNERStats_NerValue();

    nerStatsViewer->clearGraphsData();
    nerStatsViewer->loadGraphsData(ner);
    nerStatsViewer->replotGraphs();
    nerStatsViewer->setWindowFlags(nerStatsViewer->windowFlags() | Qt::Tool);
    nerStatsViewer->show();
}

void NERMainWindow::computerNERStatistics()
{
    if(mainMdiArea->subWindowList().count()==0){
        return;
    }

    QMdiSubWindow* subWindow = mainMdiArea->activeSubWindow();
    NERTableWidget* table = static_cast<NERTableWidget*>(subWindow->widget());

    NERStatsData ner = table->computeNERStats_NerValue();


    emit setNERStatistics(ner);

    ENGINE_DEBUG << "NER Value = "          << ner.getNerValue() << "\n\t"
                 << "Edition Error = "      << ner.getEditionErrors() << "\n\t"
                 << "Edition w000 = "       << ner.getEditionErrors_w000() << "\n\t"
                 << "Edition w025 = "       << ner.getEditionErrors_w025() << "\n\t"
                 << "Edition w050 = "       << ner.getEditionErrors_w050() << "\n\t"
                 << "Edition w100 = "       << ner.getEditionErrors_w100() << "\n\t"
                 << "Recognition Error = "  << ner.getRecognitionErrors() << "\n\t"
                 << "Recognition w000 = "   << ner.getRecognitionErrors_w000() << "\n\t"
                 << "Recognition w025 = "   << ner.getRecognitionErrors_w025() << "\n\t"
                 << "Recognition w050 = "   << ner.getRecognitionErrors_w050() << "\n\t"
                 << "Recognition w100 = "   << ner.getRecognitionErrors_w100() << "\n\t"
                 << "Avg Delay ="           << ner.getAvgDelay() << "\n\t"
                 << "N = "                  << ner.getNCount() << "\n\t"
                 << "N_words = "            << ner.getN_words() << "\n\t"
                 << "N_ponct = "            << ner.getN_ponctuation() << "\n\t"
                 << "N_trans = "            << ner.getN_transitions();
}

void NERMainWindow::computeAllNERStatistics()
{
    QList<QMdiSubWindow*> subWindowList = mainMdiArea->subWindowList();

    for(int i=0; i<subWindowList.count(); i++)
    {
        QMdiSubWindow* subWindow = subWindowList.at(i);
        NERTableWidget* table = static_cast<NERTableWidget*>(subWindow->widget());
        table->computeNERStats_NerValue();
    }
}

LIC_ERROR_TYPE NERMainWindow::checkLicence()
{
    LIC_ERROR_TYPE isLicOK = licenceMng->checkLicence();

    if(isLicOK != LIC_NO_ERROR)
    {
        QMessageBox box;
        box.setInformativeText("The tool's licence is not installed or not longer valid!\nInstall a new licence file ?");
        box.setText("Licence check failed                                                        ");
        box.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        box.setIcon(QMessageBox::Question);
        box.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        int result = box.exec();
        bool exitApp = false;
        switch (result){
        case QMessageBox::No :
            exitApp = true;
        }

        if(exitApp){
            return LIC_UNDEF_ERROR;
        }

        QString licFilePath = QFileDialog::getOpenFileName(
                this,
                tr("NER licence file"),
                QDir::currentPath(),
                tr("NER Licence file (*.lic)"));

        if(licFilePath.isEmpty())
        {
             return LIC_UNDEF_ERROR;
        }

        licenceMng->installNewLicence(licFilePath);

        return licenceMng->checkLicence(); //recheck after install...
    }

    return LIC_NO_ERROR;
}

void NERMainWindow::displayErrorMessage(LIC_ERROR_TYPE errorType)
{
    QString msg;

    switch(errorType){
    case LIC_INVALID_TIME:
        msg = "The licence has expired";

        break;
    case LIC_INVALID_MAC_ADDRESS:
        msg = "The MAC address of this machine is inconsistent with the licence";
        break;
    case LIC_INVALID_FILE:
        msg = "The licence file is corrupted";
        break;
    case LIC_UNDEF_ERROR:
        msg = "The licence file could not be verified";
        break;
    default:
        break;
    }

    QMessageBox box;
    box.setText("Licence error                                                                ");
    box.setInformativeText(msg);
    box.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    box.setIcon(QMessageBox::Question);
    box.setStandardButtons(QMessageBox::Ok);
    box.exec();

}





















