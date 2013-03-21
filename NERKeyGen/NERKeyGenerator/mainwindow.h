#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QTabWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QComboBox>
#include <QDesktopServices>
#include "utils.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QLabel  *statusBarLeftLabel;
    QLabel  *statusBarMiddleLabel;
    QLabel  *statusBarRightLabel;

    QWidget *centralWidget;
    QWidget *keyWidget;
    QVBoxLayout *mainKeyGenLayout;

    QList<QString> macAddressofVM;

    QGridLayout *genKeyLayout;
    QGroupBox *genKeyGroupBox;
    QLabel *userLabel;
    QLineEdit *userValueLabel;
    QLabel *orgLabel;
    QLineEdit *orgValueLabel;
    QLabel *macLabel;
    QLineEdit *macValueLabel;

    QLabel *allowVMLabel;
    QComboBox *allowVMCombo;

    QVBoxLayout *keyReaderLayout;
    QGroupBox *readerKeyGroupBox;

    QCalendarWidget *calendarWidgetStart;
    QCalendarWidget *calendarWidgetFinish;
    QLabel *startTimeLabel;
    QDateEdit *startTimeValueLabel;
    QPushButton *startDateButton;
    QPushButton *finishDateButton;
    QLabel *finishTimeLabel;
    QDateEdit *finishTimeValueLabel;

    QPushButton *generateKey;
    QPushButton *readKey;

    QTextEdit *keyTextEdit;

    QTabWidget *tabs;

    void createElements();
    void createToolBars();
    void createStatusBar();
    void initBannedMacAdresses();
    bool isBannedMac(QString mac);

private slots:
    void showCalendarStart();
    void showCalendarFinish();
    void setStartDateSlot(QDate d);
    void setFinishDateSlot(QDate d);
    void generateKeySlot();
    void loadKeySlot();

};

#endif // MAINWINDOW_H
