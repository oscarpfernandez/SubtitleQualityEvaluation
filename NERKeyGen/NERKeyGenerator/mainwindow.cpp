#include "mainwindow.h"
#include "common.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    setWindowTitle(APP_NAME);
    resize(QSize(700,400));
    setWindowIcon(QIcon(":/pics/icon.png"));

    centralWidget = new QWidget(parent);
    keyWidget = new QWidget(parent);

    createElements();

    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{

}

void MainWindow::createElements()
{

    mainKeyGenLayout = new QVBoxLayout;

    genKeyLayout = new QGridLayout;
    genKeyGroupBox = new QGroupBox(QString("Key Properties"), centralWidget);
    userLabel = new QLabel(QString("User: "));
    userLabel->setMaximumWidth(100);
    userValueLabel = new QLineEdit();
    orgLabel = new QLabel(QString("Organization: "));
    orgValueLabel = new QLineEdit();
    macLabel = new QLabel(QString("MAC Address: "));
    macValueLabel = new QLineEdit();


    startTimeLabel = new QLabel(QString("Start Date: "));
    calendarWidgetStart = new QCalendarWidget();
    connect(calendarWidgetStart, SIGNAL(clicked(QDate)), this, SLOT(setStartDateSlot(QDate)));
    calendarWidgetFinish = new QCalendarWidget();
    connect(calendarWidgetFinish, SIGNAL(clicked(QDate)), this, SLOT(setFinishDateSlot(QDate)));

    QDate currentDate = QDate::currentDate();
    startTimeValueLabel = new QDateEdit();
    startTimeValueLabel->setMaximumWidth(100);
    startTimeValueLabel->setDate(QDate::fromString( currentDate.toString("dd/MM/yyyy"), "dd/MM/yyyy"  ));

    startDateButton = new QPushButton("...");
    connect(startDateButton, SIGNAL(clicked()), this, SLOT(showCalendarStart()));
    finishDateButton = new QPushButton("...");
    connect(finishDateButton, SIGNAL(clicked()), this, SLOT(showCalendarFinish()));

    finishTimeLabel = new QLabel(QString("Finish Date:"));
    finishTimeValueLabel = new QDateEdit();
    finishTimeValueLabel->setDate(QDate::fromString( currentDate.toString("dd/MM/yyyy"), "dd/MM/yyyy"  ));
    finishTimeValueLabel->setDate(QDate(currentDate.year()+1, currentDate.month(), currentDate.day()));
    finishTimeValueLabel->setMaximumWidth(100);

    genKeyLayout->addWidget(userLabel, 0,0);
    genKeyLayout->addWidget(userValueLabel, 0,1);
    genKeyLayout->addWidget(orgLabel, 1,0);
    genKeyLayout->addWidget(orgValueLabel, 1,1);
    genKeyLayout->addWidget(macLabel, 2,0);
    genKeyLayout->addWidget(macValueLabel, 2,1);
    genKeyLayout->addWidget(startTimeLabel, 3,0);
    genKeyLayout->addWidget(startTimeValueLabel, 3,1);
    genKeyLayout->addWidget(startDateButton, 3,2);
    genKeyLayout->addWidget(finishTimeLabel, 4,0);
    genKeyLayout->addWidget(finishTimeValueLabel, 4,1);
    genKeyLayout->addWidget(finishDateButton, 4,2);
    genKeyGroupBox->setLayout(genKeyLayout);
    genKeyGroupBox->setMaximumHeight(genKeyGroupBox->sizeHint().height());

    generateKey = new QPushButton(QIcon(":/pics/icon.png"),"Generate Key File");
    connect(generateKey, SIGNAL(clicked()), this, SLOT(generateKeySlot()));
    generateKey->setFixedHeight(60);
    generateKey->setFixedWidth(200);

    mainKeyGenLayout->addWidget(genKeyGroupBox);
    mainKeyGenLayout->addWidget(generateKey);

    keyWidget->setLayout(mainKeyGenLayout);

    tabs = new QTabWidget(centralWidget);
    tabs->setMinimumSize(QSize(700,400));
    tabs->addTab(keyWidget,"Generate Key");
    tabs->addTab(new QWidget(),"Read Key");
}

void MainWindow::createActions()
{

}

void MainWindow::createMenus()
{

}

void MainWindow::generateKeySlot()
{
    QString user = userValueLabel->text().simplified();
    QString org = orgValueLabel->text().simplified();
    QString mac = macValueLabel->text().simplified();
    QDate startDate = startTimeValueLabel->date();
    QDate finishDate = finishTimeValueLabel->date();

    QString licenceFile = QFileDialog::getSaveFileName(
                this,
                tr("Save Licence File"),
                QDir::currentPath(),
                tr("NER Files (*.lic)"));

    if(licenceFile.isEmpty()){
        return; //Nothing to do!
    }

    if(!licenceFile.endsWith(".lic")){
        licenceFile.append(".lic");
    }

    Utils::generateLicenceFile(licenceFile, user, org, mac, startDate, finishDate);

}

void MainWindow::showCalendarStart()
{
    calendarWidgetStart->show();
}

void MainWindow::showCalendarFinish()
{
    calendarWidgetFinish->show();
}

void MainWindow::setStartDateSlot(QDate d)
{
    startTimeValueLabel->setDate(d);
}

void MainWindow::setFinishDateSlot(QDate d)
{
    finishTimeValueLabel->setDate(d);
}

void MainWindow::createToolBars()
{

}

void MainWindow::createStatusBar(){
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

