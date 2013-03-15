#include "mainwindow.h"
#include "common.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    setWindowTitle(APP_NAME);
    resize(QSize(600,300));
    setWindowIcon(QIcon(":/pics/icon.png"));

    QWidget *centralWidget = new QWidget(parent);


    tabs = new QTabWidget(centralWidget);
    tabs->setMinimumSize(QSize(600,400));
    tabs->addTab(new QWidget(),"Generate Key");
    tabs->addTab(new QWidget(),"Read Key");

    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{

}

void MainWindow::createElements()
{

}

void MainWindow::createActions()
{

}

void MainWindow::createMenus()
{

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

