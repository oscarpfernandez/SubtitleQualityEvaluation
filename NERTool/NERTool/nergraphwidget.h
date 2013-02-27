#ifndef NERGRAPHWIDGET_H
#define NERGRAPHWIDGET_H

#include <QWidget>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "nercommon.h"
#include "qcustomplot.h"

class NERGraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NERGraphWidget(QWidget *parent = 0);
    void setupBarPlot(QVector<QString> &tickNerTableNames,
                      QList<NERStatsData> &data);

private:
    QCustomPlot* customPlot;
    QCPBars *correctEditions;
    QCPBars *editionErrors;
    QCPBars *recogErrors;

public slots:
    
};

#endif // NERGRAPHWIDGET_H
