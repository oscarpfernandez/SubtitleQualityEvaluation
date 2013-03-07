#ifndef NERTABLEWIDGET_H
#define NERTABLEWIDGET_H

#include <qwidget.h>
#include <qtablewidget.h>
#include <qmdiarea.h>
#include <qmdisubwindow.h>
#include <QHBoxLayout>
#include "nercommon.h"
#include "draglabel.h"
#include "dragwidget.h"
#include "mediamngwidget.h"
#include "diff_match_patch.h"


const int SPEAKER_ID_COLUMN_WIDTH = 100;
const int SPEAKER_ID_COLUMN_INDEX = 0;
const int TIMESTAMP_COLUMN_WIDTH = 70;
const int TIMESTAMP_COLUMN_INDEX = 1;
const int TRANSCRIPTION_COLUMN_WIDTH = 500;
const int TRANSCRIPTION_COLUMN_INDEX = 2;
const int SUB_TIMESTAMP_COLUMN_WIDTH = 70;
const int SUB_SUBTITLES_COLUMN_WIDTH = 450;
const int SUBTITLES_COLUMN_WIDTH = SUB_TIMESTAMP_COLUMN_WIDTH + SUB_SUBTITLES_COLUMN_WIDTH;
const int SUBTITLES_COLUMN_INDEX = 3;

const int SUB_TIMESTAMP_COLUMN_INDEX = 0;
const int SUB_SUBTITLES_COLUMN_INDEX = 1;

class MediaMngWidget;
class NERSubTableWidget;

class NERTableWidget : public QTableWidget
{

Q_OBJECT

public:
    NERTableWidget(QWidget *parent);
    ~NERTableWidget();
    void setMediaWidget(MediaMngWidget *mediaWidget);
    void setTableName(QString &tableName);
    QString getTableName();
    void setResponsible(QString &responsible);
    QString getResponsible();
    void setDescription(QString &desc);
    QString getDescription();
    int insertNewTableEntry(QString &speaker,
                            QString &TimeStamp,
                            QString &text);
    void loadXMLData(QList<BlockTRS> *trsBlocks);
    void loadSubtitlesXMLData(QList<BlockTRS> *transcription,
                              QList<BlockTRS> *trsBlocks);
    void insertTimeStampsHashedMap(QString &timeStamp, QString &text);
    void insertNewSubtableInLastEntry(NERSubTableWidget* subtable);
    void deleteTablesContents();
    QHash<qlonglong,QString> getHashedSubtableData();
    int computeNERStats_N();
    double computeNERStats_NerValue();
    double computeNERStats_EditionErrors();
    double computeNERStats_RecognitionErrors();
    double computeNERStats_Delay();
    QString getTableTransRowText(int row);
    QList<DragLabel*> getTableTransRowLabels(int row);
    void makeTableRowDiff(int row);
    QList<Diff> reprocessdistanceOutput(QList<Diff> &diffList);
    void applyEditionProperties(int row, QList<Diff> &diffList);

private:
    MediaMngWidget *mediaMngWidget;
    QHeaderView *headerView;
    QList<BlockTRS> *subtitleTableData;
    QHash<qlonglong,QString> *subtileDataHashedByTimestamp;
    QList<BlockTRS> *transcriptionList;
    qlonglong getTimeInMilis(QString time);
    QString tableName;
    QString responsible;
    QString description;

public slots:
    void columnTableResized(int column, int oldWidth, int newWidth);
};

class NERSubTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    NERSubTableWidget(QWidget *parent=0);
    ~NERSubTableWidget();
    void setMediaWidget(MediaMngWidget *mediaWidget);
    int insertNewTableEntry(QString &timeStamp, QString &text);
    int insertNewTableEntry(QString &timeStamp, DragWidget *wordBox);
    BlockTRS getSubtableRowData(int row);
    QString getJointSubTableText();
    QList<DragLabel*> getSubTableLabels();

private:
    MediaMngWidget *mediaMngWidget;

private slots:
    void videoSeekFromStamp(int row, int column);

};

#endif
