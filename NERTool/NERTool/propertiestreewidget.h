#ifndef PROPERTIESTREEWIDGET_H
#define PROPERTIESTREEWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QTreeWidget>

class PropertiesTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesTreeWidget(QWidget *parent = 0);
    void insertNewNerTable(QString &name);
    void insertNewSpeaker(QString &speaker);
    
private:
    QVBoxLayout *mainVLayout;
    QTreeWidget *mainTreeWidget;

    
public slots:
    
};

#endif // PROPERTIESTREEWIDGET_H
