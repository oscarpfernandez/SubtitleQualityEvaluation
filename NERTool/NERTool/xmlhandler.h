#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <qfile.h>
#include <qtablewidget.h>
#include <qxmlstream.h>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDateTime>
#include <QTreeWidgetItem>
#include "nercommon.h"
#include "nertablewidget.h"
#include "dragwidget.h"
#include "propertiestreewidget.h"

/*******************************************************************************
 * Transcriber XML tags (for import)
 ******************************************************************************/
const QString STR_SPEAKERS = "Speakers";
const QString STR_SPEAKER = "Speaker";
const QString STR_SPEAKER_ID = "id";
const QString STR_SPEAKER_NAME = "name";
const QString STR_SPEAKER_TYPE = "type";
const QString STR_TURN_SPEAKER = "speaker";

const QString STR_TRANS = "Trans";
const QString STR_EPISODE = "Episode";
const QString STR_SECTION = "Section";
const QString STR_TURN = "Turn";
const QString STR_SYNC = "Sync";
const QString STR_SYNC_TIME = "time";


/*******************************************************************************
 * NER export tags.
 ******************************************************************************/
const QString STR_NER_PROJECT = "NERProject";
const QString STR_NER_PROJECT_PROP_SAVEDATE = "saveTime";

const QString STR_TRANSC_TAG = "Transcription";
const QString STR_TRANSC_PROP_NAME = "tableName";
const QString STR_TRANSC_RESPONSIBLE = "responsible";
const QString STR_TRANSC_DESCRIPTION = "description";
const QString STR_TRANSC_LINE_TAG = "TranscLine";
const QString STR_TRANSC_LINE_PROP_TIMESTAMP = "timestamp";
const QString STR_TRANSC_LINE_PROP_SPEAKER = "speakerid";
const QString STR_TRANSC_LINE_PROP_TEXT = "text";
const QString STR_TRANSC_LINE_WORDS = "TranscWords";
const QString STR_TRANSC_LINE_WORD = "TranscWord";

const QString STR_SPEAKERS_TAG = "Speakers";
const QString STR_SPEAKER_TAG = "Speaker";
const QString STR_SPEAKER_PROP_ID = "sID";
const QString STR_SPEAKER_PROP_NAME = "sName";
const QString STR_SPEAKER_PROP_TYPE = "sType";

const QString STR_TABLES_TAG = "Tables";
const QString STR_TABLE_TAG = "Table";
const QString STR_TABLE_PROP_NAME = "tableName";
const QString STR_TABLE_PROP_RESPONSIBLE = "responsible";
const QString STR_TABLE_PROP_DESCRIPTION = "description";
const QString STR_TABLE_PROP_ASSESSMENT = "assessment";
const QString STR_TABLELINE_TAG = "TableLine";
const QString STR_TABLELINE_PROP_SID = "sID";
const QString STR_TABLELINE_PROP_TIMESTAMP = "timestamp";
const QString STR_TABLELINE_PROP_TRANSCRIP = "transcription";
const QString STR_SUBTABLELINE_TAG = "SubTableLine";
const QString STR_SUBTABLELINE_PROP_TIMESTAMP = "timestamp";
const QString STR_WORD_TAG = "SubtWord";
const QString STR_WORD_PROP_NAME = "name";
const QString STR_WORD_PROP_ERROR = "error";
const QString STR_WORD_PROP_WEIGHT = "weight";
const QString STR_WORD_PROP_CLASS = "class";
const QString STR_WORD_PROP_COMMENT = "comment";

class XMLHandler {

public:
    XMLHandler(QWidget *parent);
    ~XMLHandler();
    bool readTranscriberXML(QString &xmlFileName,
                            QList<BlockTRS> *trsBlocks,
                            QList<Speaker> *speakerList);
    bool readSRTTranscription(QString &xmlFileName,
                              QList<BlockTRS> *trsBlocks);
    bool readSubtitleXML(QString &xmlFileName,
                         QList<BlockTRS> *trsBlocks);
    bool readSubtitleSRT(QString &srtFile,
                         QList<BlockTRS> *trsBlocks);
    bool writeProjectExportXML(QString &xmlFileName,
                               QList<Speaker> *speakerList,
                               QList<BlockTRS> *transcription,
                               QTreeWidgetItem *transcTreeNode,
                               QMap<QTreeWidgetItem *, QMdiSubWindow *> *subWindowsMap);
    bool readProjectExportXML(QString &xmlFileName,
                              QList<Speaker> *speakerList,
                              QList<BlockTRS> *transcription,
                              QList<NERTableWidget*> *nerTablesList,
                              MediaMngWidget *mediaWid,
                              PropertiesTreeWidget *treeWidget);
    bool writeProjectReport(QString &xmlFileName,
                            QList<NERTableWidget*> *nerTablesList,
                            PropertiesTreeWidget *treeWidget);


private:
    QWidget *_parent;
    bool loadTranscriberXML(QFile *xmlFile,
                            QList<BlockTRS> *trsBlocks,
                            QList<Speaker> *speakerList);
    bool loadSRTTranscription(QFile *srtFile,
                              QList<BlockTRS> *trsBlocks);
    bool loadSubtitleXML(QFile *xmlFile,
                         QList<BlockTRS> *trsBlocks);
    QString getFormatedTime(QString &time, bool &isTimeSRTOk);
};

#endif
