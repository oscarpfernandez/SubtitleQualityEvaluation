#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <qfile.h>
#include <qtablewidget.h>
#include <qxmlstream.h>
#include "difftablewidget.h"

const QString STR_SPEAKERS = "Speakers";
const QString STR_SPEAKER = "Speaker";
const QString STR_SPEAKER_ID = "id";
const QString STR_SPEAKER_NAME = "name";
const QString STR_TURN_SPEAKER = "speaker";

const QString STR_TRANS = "Trans";
const QString STR_EPISODE = "Episode";
const QString STR_SECTION = "Section";
const QString STR_TURN = "Turn";
const QString STR_SYNC = "Sync";
const QString STR_SYNC_TIME = "time";

/*
 * Struct to hold each line contained on the TRS XML file.
 */
struct BlockTRS
{
private:
    QString speaker;
    QString syncTime;
    QString text;
public:
    BlockTRS& setSpeaker(QString s){speaker=s; return *this;}
    BlockTRS& setSyncTime(QString t){syncTime=t; return *this;}
    BlockTRS& setText(QString txt){text=txt; return *this;}
    QString getSpeaker(){return speaker;}
    QString getSyncTime(){return syncTime;}
    QString getText(){return text;}
    QString toString(){
        return QString("\tBlock -> ")
                .append(speaker).append("\n")
                .append(syncTime).append("\n")
                .append(text.trimmed());
    }
};

class XMLHandler {

public:
    XMLHandler();
	~XMLHandler();
    bool readTranscriptionXML(QString &xmlFileName, DiffTableWidget *table);
    bool readSubtitleXML(QString &xmlFileName, DiffTableWidget *table);
    //bool writeExportXML(QString &xmlFileName, )


private:
    bool loadTranscriptionXML(QFile *xmlFile, DiffTableWidget *table);
    bool loadSubtitleXML(QFile *xmlFile, DiffTableWidget *table);
};

#endif
