#ifndef NERTABLEWIDGET_H
#define NERTABLEWIDGET_H

#include <qwidget.h>
#include <qtablewidget.h>
#include <qmdiarea.h>
#include <qmdisubwindow.h>
#include <QHBoxLayout>
#include "nercommon.h"



const int SPEAKER_ID_COLUMN_WIDTH = 100;
const int SPEAKER_ID_COLUMN_INDEX = 0;
const int TIMESTAMP_COLUMN_WIDTH = 70;
const int TIMESTAMP_COLUMN_INDEX = 1;
const int TRANSCRIPTION_COLUMN_WIDTH = 500;
const int TRANSCRIPTION_COLUMN_INDEX = 2;

const int SUBTITLES_COLUMN_WIDTH = 400;

class NERTableWidget : public QTableWidget
{

Q_OBJECT

public:
    NERTableWidget(QWidget *parent = 0);
    ~NERTableWidget();
    void insertNewTableEntry(QString &speaker, QString &TimeStamp, QString &text);
    void loadXMLData(QList<BlockTRS> *trsBlocks);

private:
    QHeaderView *headerView;

public slots:
    void columnTableResized(int column, int oldWidth, int newWidth);
};

class NERSubTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    NERSubTableWidget(QWidget *parent=0);
    ~NERSubTableWidget();
    void insertNewTableEntry(QString &timeStamp, QString &text);
    void getXMLNode();

};

#endif