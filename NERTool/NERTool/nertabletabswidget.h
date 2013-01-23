#ifndef NERTABLETABSWIDGET_H
#define NERTABLETABSWIDGET_H

#include <QWidget>
#include "nertablewidget.h"

class NERTableTabsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NERTableTabsWidget(QWidget *parent = 0);
    void insertNewTable(QString &tabName, NERTableWidget *table);
    
signals:
    
public slots:
    
};

#endif // NERTABLETABSWIDGET_H
