#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <qfile.h>
#include <qtablewidget.h>

class XMLHandler {

public:
	XMLHandler();
	~XMLHandler();
	void checkFileAndLoad(QString &fileName, XMLHandler::XMLType type);
	void loadTranscriptionXML(QFile *xmlFile, QTableWidget *table);
	void loadSubtitleXML(QFile *xmlFile, QTableWidget *table);
	enum XMLType
	{
      XML_TRANSCRIPTION = 1,
	  XML_SUBTITLES = 2
    };
private:

};

#endif