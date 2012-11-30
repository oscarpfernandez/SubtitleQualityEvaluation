#include "xmlhandler.h"

/******************************************************************************
 * XML Handler for NER tool.
 * Manages the loading of subtitles and transcriptions and the project's export
 * configuration.
 ******************************************************************************/

XMLHandler::XMLHandler()
{

}

XMLHandler::~XMLHandler()
{


}

bool XMLHandler::readTranscriptionXML(QString &xmlFilePath, DiffTableWidget *table)
{
	if(QFile::exists(xmlFilePath)){
        QFile *xmlFile = new QFile(xmlFilePath);
        if(xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return loadTranscriptionXML(xmlFile, table);
        }
	}

    return false;

}

bool XMLHandler::readSubtitleXML(QString &xmlFilePath, DiffTableWidget *table)
{
	if(QFile::exists(xmlFilePath)){
        QFile *xmlFile = new QFile(xmlFilePath);
        if(xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return loadSubtitleXML(xmlFile, table);
        }
	}

    return false;

}

/******************************************************************************
 * Loads the transcription XML format into the GUI's table...
 *
    <?xml version="1.0" encoding="UTF-8"?>
    <!DOCTYPE Trans SYSTEM "trans-14.dtd">
    <Trans scribe="Juan Martinez" audio_filename="ner_10vor10_2012-09-27_Audio" version="1" version_date="121026">
    <Speakers>
        <Speaker id="spk1" name="Journalist 1" check="no" type="female" dialect="native" accent="" scope="local"/>
        <Speaker id="spk2" name="Christine Maier" check="no" type="female" dialect="native" accent="" scope="local"/>
        <Speaker id="spk3" name="Stefan Reinhart" check="no" type="male" dialect="native" accent="" scope="local"/>
    </Speakers>
    <Episode>
        <Section type="report" startTime="0" endTime="85.6555102041">
            <Turn startTime="0" endTime="5.361" speaker="spk1" mode="planned" fidelity="high" channel="studio">
                <Sync time="0"/>
                zustandekommen, will die Bundeskanzlei n�chste Woche bekanntgeben.
            </Turn>
            <Turn speaker="spk2" mode="planned" fidelity="high" channel="studio" startTime="5.361" endTime="19.947">
                <Sync time="5.361"/>
                Falls das Referendum gegen das Abkommen mit Deutschland tats�chlich zustande kommt, w�rden die Schweizer Ende November dar�ber abstimmen.
                <Sync time="12.189"/>
                Stefan Reinhard in Berlin, was h�tte das dann f�r einen Einfluss auf die deutsche Politik, wo das Abkommen ebenfalls auf der Kippe steht?
            </Turn>
            <Turn mode="planned" fidelity="high" startTime="19.947" endTime="21.747" channel="studio">
                <Sync time="19.947"/>

            </Turn>
        </Section>
    </Episode>
    </Trans>
 *
 ******************************************************************************/
bool XMLHandler::loadTranscriptionXML(QFile *xmlFile, DiffTableWidget *table){

    bool isSyncBlock = false;
    QString syncTime;
    QString speaker;

    QList<BlockTRS> *trsBlocks = new QList<BlockTRS>();

    QXmlStreamReader *xmlReader = new QXmlStreamReader(xmlFile);
    QXmlStreamAttributes attrs;

	while(!xmlReader->atEnd() && !xmlReader->hasError()) {

		/* Read next element.*/
        xmlReader->readNext();


        /* If token is just StartDocument, we'll go to next.*/
        if(xmlReader->isStartDocument() ) {
            qDebug("\tisStartDocument...");
            continue;
        }

        if(xmlReader->isCharacters() ) {
            qDebug("\tisCharacters from Sync...");
            if(!xmlReader->text().toString().trimmed().isEmpty()){
                BlockTRS btr;
                btr.setSpeaker(speaker).setSyncTime(syncTime).setText(xmlReader->text().toString().trimmed());
                trsBlocks->append(btr);
                qDebug(btr.toString().toAscii());
            }
            continue;
        }

		/* If token is StartElement, we'll see if we can read it.*/
        if(xmlReader->isStartElement()) {
			if(xmlReader->name() == STR_SPEAKERS){
				qDebug("\tSpeakers block...");
				continue;
			}

			if(xmlReader->name() == STR_SPEAKER){
				qDebug("\tspeaker...");
				//Read Speaker attributes
				QXmlStreamAttributes attrs = xmlReader->attributes();
				const QString id = attrs.value(STR_SPEAKER_ID).toString();
				const QString name = attrs.value(STR_SPEAKER_NAME).toString();
				QString d("\tspeaker -> ");
				d.append(id).append(" :: ").append(name);
				d.toAscii();
				qDebug(d.toAscii());
				continue;
			}

			if(xmlReader->name() == STR_TRANS) {
				//Ignore it for the moment...
                qDebug("\tReading transcritption block...");
                continue;
            }
            else if(xmlReader->name() == STR_EPISODE) {
                qDebug("\tReading episode block...");

				
            }
			if(xmlReader->name() == STR_SECTION){
                attrs = xmlReader->attributes();

				continue;
			}
			if(xmlReader->name() == STR_TURN){
                attrs = xmlReader->attributes();
                speaker = attrs.value(STR_TURN_SPEAKER).toString();
				continue;
			}
            else if(xmlReader->name() == STR_SYNC){
                qDebug("\tReading Sync block...");
                attrs = xmlReader->attributes();
                syncTime = attrs.value(STR_SYNC_TIME).toString();
                isSyncBlock = true;
                continue;
            }
            
        }


		if(xmlReader->isEndElement()) {
            qDebug("\tClosing block...");
            continue;
        }
        if(xmlReader->isEndDocument()) {
            qDebug("\tEnd document block...");
            continue;
        }
	}

    //Fill the table with the entries...
    for(int i=0; i<trsBlocks->count(); i++){
        BlockTRS btr = trsBlocks->at(i);
        table->insertNewTableEntry(btr.getSpeaker(), btr.getSyncTime(), btr.getText());
    }


    return false;

}

bool XMLHandler::loadSubtitleXML(QFile *xmlFile, DiffTableWidget *table){


	return false;
}
