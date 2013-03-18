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

    QGridLayout *genKeyLayout;
    QGroupBox *genKeyGroupBox;
    QLabel *userLabel;
    QLineEdit *userValueLabel;
    QLabel *orgLabel;
    QLineEdit *orgValueLabel;
    QLabel *macLabel;
    QLineEdit *macValueLabel;

    QCalendarWidget *calendarWidgetStart;
    QCalendarWidget *calendarWidgetFinish;
    QLabel *startTimeLabel;
    QDateEdit *startTimeValueLabel;
    QPushButton *startDateButton;
    QPushButton *finishDateButton;
    QLabel *finishTimeLabel;
    QDateEdit *finishTimeValueLabel;

    QPushButton *generateKey;

    QTabWidget *tabs;

    void createElements();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

private slots:
    void showCalendarStart();
    void showCalendarFinish();
    void setStartDateSlot(QDate d);
    void setFinishDateSlot(QDate d);
    void generateKeySlot();

};

#endif // MAINWINDOW_H
