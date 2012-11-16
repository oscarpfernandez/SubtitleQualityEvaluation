/********************************************************************************
** Form generated from reading UI file 'nermainwindow.ui'
**
** Created: Tue 23. Oct 16:09:28 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NERMAINWINDOW_H
#define UI_NERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NERMainWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NERMainWindow)
    {
        if (NERMainWindow->objectName().isEmpty())
            NERMainWindow->setObjectName(QString::fromUtf8("NERMainWindow"));
        NERMainWindow->resize(400, 300);
        menuBar = new QMenuBar(NERMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        NERMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NERMainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        NERMainWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(NERMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        NERMainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(NERMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        NERMainWindow->setStatusBar(statusBar);

        retranslateUi(NERMainWindow);

        QMetaObject::connectSlotsByName(NERMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *NERMainWindow)
    {
        NERMainWindow->setWindowTitle(QApplication::translate("NERMainWindow", "NERMainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NERMainWindow: public Ui_NERMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NERMAINWINDOW_H
