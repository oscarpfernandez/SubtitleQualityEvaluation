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


/*******************************************************************************
 * Handles the import of TRS XML files (generated by Transcriber application)
 * Args:
 *
 ******************************************************************************/
bool XMLHandler::readTranscriberXML(QString &xmlFilePath,
                                    QList<BlockTRS> *trsBlocks,
                                    QList<Speaker> *speakerList)
{
    if(QFile::exists(xmlFilePath)){
        QFile *xmlFile = new QFile(xmlFilePath);
        if(xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return loadTranscriberXML(xmlFile, trsBlocks, speakerList);
        }
    }

    return false;

}

bool XMLHandler::readSubtitleXML(QString &xmlFilePath,
                                 QList<BlockTRS> *trsBlocks)
{
    if(QFile::exists(xmlFilePath)){
        QFile *xmlFile = new QFile(xmlFilePath);
        if(xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return loadSubtitleXML(xmlFile, trsBlocks);
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
bool XMLHandler::loadTranscriberXML(QFile *xmlFile,
                                    QList<BlockTRS> *trsBlocks,
                                    QList<Speaker> *speakerList){

    QString syncTime;
    QString speaker;

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
                QString textFinal = xmlReader->text().toString().trimmed();
                textFinal.replace(",",", ");
                btr.setSpeaker(speaker).setSyncTime(syncTime).setText(textFinal);
                trsBlocks->append(btr);
                //qDebug(btr.toString().toAscii());
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
                const QString type = attrs.value(STR_SPEAKER_TYPE).toString();
                Speaker sp;
                sp.setId(id).setName(name).setType(type);
                speakerList->append(sp);
                continue;
            }

            if(xmlReader->name() == STR_TRANS) {
                //Ignore it for the moment...
                qDebug("\tReading transcritption block...");
                continue;
            }
            if(xmlReader->name() == STR_EPISODE) {
                qDebug("\tReading episode block...");
                continue;

            }
            if(xmlReader->name() == STR_SECTION){
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

    return true;
}

/*******************************************************************************
 * Loads the subtitles represented in the transcriber format.
 ******************************************************************************/
bool XMLHandler::loadSubtitleXML(QFile *xmlFile, QList<BlockTRS> *trsBlocks)
{
    QString syncTime;
    QString speaker;

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
                QString textFinal = xmlReader->text().toString().trimmed();
                textFinal.replace(",",", ");
                btr.setSpeaker(speaker).setSyncTime(syncTime).setText(textFinal);
                trsBlocks->append(btr);
                //qDebug(btr.toString().toAscii());
            }
            continue;
        }

        /* If token is StartElement, we'll see if we can read it.*/
        if(xmlReader->isStartElement()) {
            if(xmlReader->name() == STR_SPEAKERS){
                continue;
            }

            if(xmlReader->name() == STR_SPEAKER){
                continue;
            }

            if(xmlReader->name() == STR_TRANS) {
                continue;
            }
            else if(xmlReader->name() == STR_EPISODE) {
                continue;
            }
            if(xmlReader->name() == STR_SECTION){
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
                continue;
            }

        }

        //Closing tags.....
        if(xmlReader->isEndElement()) {
            qDebug("\tClosing block...");
            continue;
        }
        if(xmlReader->isEndDocument()) {
            qDebug("\tEnd document block...");
            continue;
        }
    }

    return true;
}


/*******************************************************************************
 * Writes the projects XML export content
 ******************************************************************************/
bool XMLHandler::writeProjectExportXML(QString &xmlFileName,
                                       QList<Speaker> *speakerList,
                                       QList<BlockTRS> *transcription,
                                       QList<NERTableWidget *> *nerTablesList)
{

    QFile *file = new QFile(xmlFileName);

    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }


    QXmlStreamWriter *xmlWriter = new QXmlStreamWriter();
    xmlWriter->setDevice(file);

    xmlWriter->setAutoFormatting(true);
    xmlWriter->writeStartDocument();

    xmlWriter->writeComment("************************************************");
    xmlWriter->writeComment("* NER Export File XML");
    xmlWriter->writeComment("************************************************");

    xmlWriter->writeStartElement(STR_NER_PROJECT);
    xmlWriter->writeAttribute(STR_NER_PROJECT_PROP_SAVEDATE,
                              QDateTime::currentDateTime().toString());

    xmlWriter->writeComment("NER Original Transcription and Speakers Block");

    xmlWriter->writeStartElement(STR_TRANSC_TAG);
    xmlWriter->writeStartElement(STR_SPEAKERS_TAG);

    for(int i=0; i<speakerList->count(); i++)
    {
        Speaker sp = speakerList->at(i);

        xmlWriter->writeStartElement(STR_SPEAKER_TAG);
        xmlWriter->writeAttribute(STR_SPEAKER_PROP_ID, sp.getId());
        xmlWriter->writeAttribute(STR_SPEAKER_PROP_NAME, sp.getName());
        xmlWriter->writeAttribute(STR_SPEAKER_PROP_TYPE, sp.getType());
        xmlWriter->writeEndElement();
    }
    xmlWriter->writeEndElement();//end Speaker tag

    for(int i=0; i<transcription->count(); i++)
    {
        BlockTRS btr = transcription->at(i);

        xmlWriter->writeStartElement(STR_TRANSC_LINE_TAG);
        xmlWriter->writeAttribute(STR_TRANSC_LINE_PROP_SPEAKER, btr.getSpeaker());
        xmlWriter->writeAttribute(STR_TRANSC_LINE_PROP_TIMESTAMP, btr.getSyncTime());
        xmlWriter->writeAttribute(STR_TRANSC_LINE_PROP_TEXT, btr.getText());
        xmlWriter->writeEndElement();//end TranscLine tag

    }
    xmlWriter->writeEndElement();//end Transcription block...


    /*********************************************
     * Export all the included subtitle tables...
     *********************************************/
    xmlWriter->writeComment("NER Comparison Tables Block");

    xmlWriter->writeStartElement(STR_TABLES_TAG);
    for(int t=0; t < nerTablesList->count(); t++)
    {
        xmlWriter->writeStartElement(STR_TABLE_TAG);
        NERTableWidget *tableWidget = nerTablesList->at(t);


        for(int row=0; row<tableWidget->rowCount(); row++)
        {
            xmlWriter->writeStartElement(STR_TABLELINE_TAG);

            QString speakerS = tableWidget->item(row, SPEAKER_ID_COLUMN_INDEX)->text();
            xmlWriter->writeAttribute(STR_TABLELINE_PROP_SID, speakerS);
            QString timeS = tableWidget->item(row, TIMESTAMP_COLUMN_INDEX)->text();
            xmlWriter->writeAttribute(STR_TABLELINE_PROP_TIMESTAMP, timeS);
            DragWidget* transWidget = static_cast<DragWidget*>(tableWidget->cellWidget(row, TRANSCRIPTION_COLUMN_INDEX));
            xmlWriter->writeAttribute(STR_TABLELINE_PROP_TRANSCRIP, transWidget->getText());


            NERSubTableWidget* subTable = static_cast<NERSubTableWidget*>(tableWidget->cellWidget(row, SUBTITLES_COLUMN_INDEX));
            if(subTable == 0){
                //no subtable was stored...
                //proceed to next line...
                continue;
            }

            for(int w=0; w < subTable->rowCount(); w++)
            {
                xmlWriter->writeStartElement(STR_SUBTABLELINE_TAG);

                DragWidget* dragWidget = static_cast<DragWidget*>(subTable->cellWidget(w,1));

                for(int z=0; z<dragWidget->countWords(); z++){

                    xmlWriter->writeStartElement(STR_WORD_TAG);
                    DragLabel* label = dragWidget->getWordAt(z);
                    xmlWriter->writeAttribute(STR_WORD_PROP_NAME, label->labelText());
                    xmlWriter->writeAttribute(STR_WORD_PROP_ERROR, QString::number(label->getError()));
                    xmlWriter->writeAttribute(STR_WORD_PROP_COMMENT, label->getComment());
                    xmlWriter->writeEndElement();//STR_WORD_TAG
                }
                xmlWriter->writeEndElement();//STR_SUBTABLELINE_TAG
            }
            xmlWriter->writeEndElement();//STR_TABLELINE_TAG
        }
        xmlWriter->writeEndElement();//STR_TABLE_TAG
    }
    xmlWriter->writeEndElement();//STR_TABLES_TAG

    xmlWriter->writeEndElement();//end NerProject
    xmlWriter->writeEndDocument();

    //Close file descriptor
    file->close();
    if (file->error()) {
        QMessageBox warningMessage;
        warningMessage.setText("There was an error closing the save file.");
        warningMessage.setWindowTitle("Warning");
        warningMessage.setIcon(QMessageBox::Warning);
        warningMessage.exec();
        return false;
    }

    delete xmlWriter;//free mem
    return true;
}














