#include "mainwindow.h"
#include "common.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    setWindowTitle(APP_NAME);
    setFixedSize(QSize(700,400));
    setWindowIcon(QIcon(":/pics/icon.png"));

    centralWidget = new QWidget(parent);
    keyWidget = new QWidget(parent);

    createElements();
    initBannedMacAdresses();

    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{

}

void MainWindow::initBannedMacAdresses()
{
    macAddressofVM = QList<QString>();

    /*
        Company and Products                            MAC unique identifier (s)
        VMware ESX 3, Server, Workstation, Player       00-50-56, 00-0C-29, 00-05-69
        Microsoft Hyper-V, Virtual Server, Virtual PC 	00-03-FF
        Parallells Desktop, Workstation, Server         00-1C-42
        Virtual Iron 4                                  00-0F-4B
        Red Hat Xen                                     00-16-3E
        Oracle VM                                       00-16-3E
        XenSource                                       00-16-3E
        Novell Xen                                      00-16-3E
        Sun xVM VirtualBox                              08-00-27
      */

    macAddressofVM.append("00:50:56");
    macAddressofVM.append("00:0C:29");
    macAddressofVM.append("00:05:69");
    macAddressofVM.append("00:03:FF");
    macAddressofVM.append("00:1C:42");
    macAddressofVM.append("00:0F:4B");
    macAddressofVM.append("00:16:3E");
    macAddressofVM.append("08:00:27");
}

bool MainWindow::isBannedMac(QString mac)
{
    for(int i=0; i < macAddressofVM.count(); i++)
    {
        QString m = macAddressofVM.at(i);
        if(mac.startsWith(m.toLower())){
            return true;
        }
    }
    return false;
}

void MainWindow::createElements()
{

    mainKeyGenLayout = new QVBoxLayout;

    genKeyLayout = new QGridLayout;
    genKeyGroupBox = new QGroupBox(QString("Key Properties"), centralWidget);
    userLabel = new QLabel(QString("User: "));
    userLabel->setMaximumWidth(100);
    userValueLabel = new QLineEdit();
    userValueLabel->setToolTip(QString("User's name associated to the licence."));
    orgLabel = new QLabel(QString("Organization: "));
    orgValueLabel = new QLineEdit();
    orgValueLabel->setToolTip(QString("The organization attached to the licence."));
    macLabel = new QLabel(QString("MAC Address: "));
    macValueLabel = new QLineEdit();
    macValueLabel->setToolTip(QString("MAC address where NER Tool is going to be installed."));


    startTimeLabel = new QLabel(QString("Start Date: "));
    calendarWidgetStart = new QCalendarWidget();
    connect(calendarWidgetStart, SIGNAL(clicked(QDate)), this, SLOT(setStartDateSlot(QDate)));
    calendarWidgetFinish = new QCalendarWidget();
    connect(calendarWidgetFinish, SIGNAL(clicked(QDate)), this, SLOT(setFinishDateSlot(QDate)));

    QDate currentDate = QDate::currentDate();
    startTimeValueLabel = new QDateEdit();
    startTimeValueLabel->setMaximumWidth(100);
    startTimeValueLabel->setDate(QDate::fromString( currentDate.toString(Qt::ISODate), Qt::ISODate  ));

    startDateButton = new QPushButton("...");
    connect(startDateButton, SIGNAL(clicked()), this, SLOT(showCalendarStart()));
    finishDateButton = new QPushButton("...");
    connect(finishDateButton, SIGNAL(clicked()), this, SLOT(showCalendarFinish()));

    finishTimeLabel = new QLabel(QString("Finish Date:"));
    finishTimeValueLabel = new QDateEdit();
    finishTimeValueLabel->setDate(QDate::fromString( currentDate.toString(Qt::ISODate), Qt::ISODate  ));
    finishTimeValueLabel->setDate(QDate(currentDate.year()+1, currentDate.month(), currentDate.day()));
    finishTimeValueLabel->setMaximumWidth(100);

    allowVMLabel = new QLabel("Allow VM MAC: ");
    allowVMCombo = new QComboBox();
    allowVMCombo->setMaximumWidth(100);
    allowVMCombo->addItem(QString("No"));
    allowVMCombo->addItem(QString("Yes"));
    allowVMCombo->setToolTip("Allow that the MAC address provided is from a Virtual Machine.");

    genKeyLayout->addWidget(userLabel, 0,0);
    genKeyLayout->addWidget(userValueLabel, 0,1);
    genKeyLayout->addWidget(orgLabel, 1,0);
    genKeyLayout->addWidget(orgValueLabel, 1,1);
    genKeyLayout->addWidget(macLabel, 2,0);
    genKeyLayout->addWidget(macValueLabel, 2,1);
    genKeyLayout->addWidget(allowVMLabel, 3,0);
    genKeyLayout->addWidget(allowVMCombo, 3,1);
    genKeyLayout->addWidget(startTimeLabel, 4,0);
    genKeyLayout->addWidget(startTimeValueLabel, 4,1);
    genKeyLayout->addWidget(startDateButton, 4,2);
    genKeyLayout->addWidget(finishTimeLabel, 5,0);
    genKeyLayout->addWidget(finishTimeValueLabel, 5,1);
    genKeyLayout->addWidget(finishDateButton, 5,2);
    genKeyGroupBox->setLayout(genKeyLayout);
    genKeyGroupBox->setMaximumHeight(genKeyGroupBox->sizeHint().height());

    generateKey = new QPushButton(QIcon(":/pics/icon.png"),"Generate Key File");
    connect(generateKey, SIGNAL(clicked()), this, SLOT(generateKeySlot()));
    generateKey->setFixedHeight(60);
    generateKey->setFixedWidth(200);

    readerKeyGroupBox = new QGroupBox("Loaded Key Properties");
    keyReaderLayout = new QVBoxLayout;
    keyTextEdit = new QTextEdit();
    keyTextEdit->setEnabled(false);
    keyTextEdit->setTextBackgroundColor(QColor(Qt::black));
    keyTextEdit->setPalette(QPalette(QColor(0,0,0)));
    keyTextEdit->setTextColor(QColor(Qt::white));

    readKey = new QPushButton(QIcon(":/pics/icon.png"),"Read Key File");
    readKey->setFixedHeight(60);
    readKey->setFixedWidth(200);
    connect(readKey, SIGNAL(clicked()), this, SLOT(loadKeySlot()));

    keyReaderLayout->addWidget(keyTextEdit, Qt::AlignCenter);
    keyReaderLayout->addWidget(readKey, Qt::AlignLeft);
    readerKeyGroupBox->setLayout(keyReaderLayout);

    mainKeyGenLayout->addWidget(genKeyGroupBox);
    mainKeyGenLayout->addWidget(generateKey, Qt::AlignCenter);

    keyWidget->setLayout(mainKeyGenLayout);

    tabs = new QTabWidget(centralWidget);
    tabs->setMinimumSize(QSize(700,400));
    tabs->addTab(keyWidget,"Generate Key");
    tabs->addTab(readerKeyGroupBox,"Read Key");
}

void MainWindow::generateKeySlot()
{
    QString user = userValueLabel->text().simplified();
    QString org = orgValueLabel->text().simplified();
    QString mac = macValueLabel->text().simplified().toLower().replace("-",":");
    QDate startDate = startTimeValueLabel->date();
    QDate finishDate = finishTimeValueLabel->date();

    if(user.isEmpty() || org.isEmpty() || mac.isEmpty()){
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setText("Input data is not valid!                                ");
        box.setInformativeText("Some of the required values are empty.       ");
        box.exec();

        return;
    }

    //Check Mac Address format...
    //00:1B:11:50:B5:FB
    QRegExp exp("^([0-9a-fA-F][0-9a-fA-F]:){5}([0-9a-fA-F][0-9a-fA-F])$");
    bool macMatch = exp.exactMatch(mac);
    if(!macMatch){
        QMessageBox box;
        box.setWindowTitle(QString("Error"));
        box.setIcon(QMessageBox::Warning);
        box.setText("Invalid MAC Address information!                                 ");
        box.setInformativeText("The MAC address provided has invalid format. ");
        box.exec();

        return;
    }
    else if(isBannedMac(mac) && allowVMCombo->currentText()=="No"){
        QMessageBox box;
        box.setWindowTitle(QString("Error"));
        box.setIcon(QMessageBox::Warning);
        box.setText("Invalid MAC Address information!                                 ");
        box.setInformativeText("The MAC address provided belongs to a virtual machine! ");
        box.exec();

        return;
    }

    if(startDate.daysTo(finishDate) <=0 ){
        QMessageBox box;
        box.setWindowTitle(QString("Error"));
        box.setIcon(QMessageBox::Warning);
        box.setText("Invalid date information!                                 ");
        box.setInformativeText("The date information provided is inconsistent. ");
        box.exec();

        return;
    }

    QString path = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);

    QString licenceFile = QFileDialog::getSaveFileName(
                this,
                tr("Save Licence File"),
                path,
                tr("NER Files (*.lic)"));

    if(licenceFile.isEmpty()){
        return; //Nothing to do!
    }

    if(!licenceFile.endsWith(".lic")){
        licenceFile.append(".lic");
    }

    Utils::generateLicenceFile(licenceFile, user, org, mac, startDate, finishDate);

}


void MainWindow::loadKeySlot()
{
    QString licenceFile = QFileDialog::getOpenFileName(
                this,
                tr("Save Licence File"),
                QDir::currentPath(),
                tr("NER Files (*.lic)"));

    QString xml = Utils::readLicenceFile(licenceFile);

    QString data = Utils::fromXML(xml);

    QString ret;
    ret.append("************************************************\n")
       .append("                            NER Licence File\n")
       .append("************************************************\n")
            .append(data);

    keyTextEdit->setText(ret);

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

}

