#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <qfile.h>
#include <qtablewidget.h>
#include <qxmlstream.h>

#include "nercommon.h"

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


class XMLHandler {

public:
    XMLHandler();
	~XMLHandler();
    bool readTranscriberXML(QString &xmlFileName, QList<BlockTRS> *trsBlocks);
    //bool writeProjectExportXML(QString &xmlFileName, )


private:
    bool loadTranscriberXML(QFile *xmlFile, QList<BlockTRS> *trsBlocks);
};

#endif
