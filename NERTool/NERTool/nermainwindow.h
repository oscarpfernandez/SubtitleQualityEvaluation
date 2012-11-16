#ifndef NERMAINWINDOW_H
#define NERMAINWINDOW_H

#include <QMainWindow>

class NERMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NERMainWindow(QWidget *parent = 0);
    ~NERMainWindow();

private:
    void createGuiElements();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
};

#endif // NERMAINWINDOW_H
