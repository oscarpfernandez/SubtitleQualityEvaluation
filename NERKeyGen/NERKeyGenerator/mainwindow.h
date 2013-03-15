#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTabWidget>

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
    QTabWidget *tabs;

    void createElements();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();


};

#endif // MAINWINDOW_H
