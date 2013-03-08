#include "nertablewidget.h"
#include <qwidget.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include "dragwidget.h"
#include "draglabel.h"
#include "xmlhandler.h"
#include <QDebug>

QT_FORWARD_DECLARE_CLASS(NERSubTableWidget)


/******************************************************************************
 * DiffTableWidget manages the table difference betwwen the original transcribded
 * and the subtitle texts. Manages the several word items allowing the export
 * of the data to an XML stream.
 ******************************************************************************/

NERTableWidget::NERTableWidget(QWidget *parent) : QTableWidget(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    //setFont(QFont("Courier New", 10, QFont::Normal));
    setSortingEnabled(false);
    setColumnCount(4);

    setAttribute(Qt::WA_DeleteOnClose);

    setRowCount(0);

    horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    QStringList headers;
    headers << "Speaker ID"
            << "Timestamp"
            << "Transcription"
            << "Subtitles";
    setHorizontalHeaderLabels(headers);


    headerView = new QHeaderView(Qt::Horizontal);
    setHorizontalHeader(headerView);
    setColumnWidth(0,SPEAKER_ID_COLUMN_WIDTH);
    setColumnWidth(1,TIMESTAMP_COLUMN_WIDTH);
    setColumnWidth(2,TRANSCRIPTION_COLUMN_WIDTH);
    setColumnWidth(3, SUBTITLES_COLUMN_WIDTH);

    //connect(headerView, SIGNAL(sectionResized(int,int,int)), this, SLOT(columnTableResized(int,int,int)));

    subtileDataHashedByTimestamp = new QHash<qlonglong,QString>();

}


NERTableWidget::~NERTableWidget()
{
    delete headerView;
    headerView = NULL;
}

void NERTableWidget::setMediaWidget(MediaMngWidget *mediaWid){
    mediaMngWidget = mediaWid;
}

void NERTableWidget::loadXMLData(QList<BlockTRS> *trsBlocks){
    if(trsBlocks==0 || trsBlocks->count()==0){
        //Nothing to do...
        return;
    }

    transcriptionList = trsBlocks;

    //Fill the table with the entries...
    for(int i=0; i<trsBlocks->count(); i++){
        BlockTRS btr = trsBlocks->at(i);
        QString speaker = btr.getSpeaker();
        QString sync = btr.getSyncTime();
        QString text = btr.getText();
        insertNewTableEntry(speaker, sync, text);
    }
}

void NERTableWidget::loadSubtitlesXMLData(QList<BlockTRS> *transcription, QList<BlockTRS> *subsTrsBlocks){
    if(subsTrsBlocks==0 || subsTrsBlocks->count()==0 || transcription==0 || transcription->count()==0){
        //Nothing to do...
        return;
    }

    //Save the subtitles list...
    subtitleTableData = new QList<BlockTRS>(*subsTrsBlocks);
//    subtileDataHashedByTimestamp = new QHash<qlonglong,QString>();
    for(int i=0; i<subtitleTableData->count(); i++){
        BlockTRS btr = subtitleTableData->at(i);

        QString ts = btr.getSyncTime();
        QString text = btr.getText();

        ENGINE_DEBUG << "Time " << ts;
        ENGINE_DEBUG << "Text " << text;

        insertTimeStampsHashedMap(ts, text);
//        QStringList ls = btr.getSyncTime().split(".");
//        QString secs = ls[0];
//        QString mils = ls[1];
//        qlonglong timeMilis = (secs.toLongLong())*1000
//                + mils.toLongLong()
//                - mils.toLongLong() % SUBTITLE_CHECK_INTERVAL;
//        QString t = btr.getText();
//        subtileDataHashedByTimestamp->insert(timeMilis, t);

    }

    //Merge the translation with the subtitles...
    int i=0;
    int line=0;
    for(int j=0; j<transcription->count()-1; j++){
        NERSubTableWidget *subTable = new NERSubTableWidget(this);
        subTable->setMediaWidget(mediaMngWidget);
        subTable->setSelectionMode(QAbstractItemView::SingleSelection);
        subTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        subTable->setDragEnabled(true);
        subTable->viewport()->setAcceptDrops(true);
        subTable->setDropIndicatorShown(true);
        subTable->setDragDropMode(QAbstractItemView::DragDrop);

        for( ; i< subsTrsBlocks->count(); i++){
            BlockTRS subBtr = subsTrsBlocks->at(i);
            BlockTRS transBtr = transcription->at(j);
            BlockTRS transBtrNext = transcription->at(j+1);

            ENGINE_DEBUG << "TRS";
            ENGINE_DEBUG << subBtr.toString();
            ENGINE_DEBUG << transBtr.toString();
            ENGINE_DEBUG << transBtrNext.toString();


            if(transBtr.getSyncTime().toDouble() <= subBtr.getSyncTime().toDouble()
                    && subBtr.getSyncTime().toDouble() < transBtrNext.getSyncTime().toDouble() )
            {
                QString sync = subBtr.getSyncTime();
                QString text = subBtr.getText();

                ENGINE_DEBUG << "New entry -> Time = " << sync << "-- Text = " << text;

                subTable->insertNewTableEntry(sync, text);
            }

            if(subBtr.getSyncTime().toDouble() > transBtrNext.getSyncTime().toDouble()){
                //skip to the new transcription line...
                qDebug("Set cell widget...");
                if(subTable->height() > rowHeight(line)){
                    //setRowHeight(line, subTable->height());
                    verticalHeader()->resizeSection(line, 200/*subTable->height()*/);

                }

                setCellWidget(line++, SUBTITLES_COLUMN_INDEX, subTable);

                break;
            }
        }
    }
}

void NERTableWidget::insertTimeStampsHashedMap(QString &timeStamp, QString &text)
{
    QStringList ls = timeStamp.split(".");
    QString secs = ls[0];
    QString mils = ls[1];
    qlonglong timeMilis = (secs.toLongLong())*1000
            + mils.toLongLong()
            - mils.toLongLong() % SUBTITLE_CHECK_INTERVAL;

    subtileDataHashedByTimestamp->insert(timeMilis, text);
}

/*
 * Intercepts the signal provided by table header resized event, to adjust the contents
 * of the dragwidget. This slot then passes the event to the table
 *
 */
void NERTableWidget::columnTableResized(int column, int oldWidth, int newWidth){
    QString d = QString::number(column).append("-").append(QString::number(oldWidth)).append("-").append(QString::number(newWidth));

    //TODO prpagate this resize to the subtables...

    columnResized(column, oldWidth, newWidth);
}

int NERTableWidget::insertNewTableEntry(QString &speaker, QString &timeStamp, QString &text)
{
    if(text == 0 || text.count() == 0 ){ return -1; }

    int line = rowCount();
    insertRow(line);
    //Set Speaker
    QTableWidgetItem *speakerItem = new QTableWidgetItem();
    speakerItem->setText(speaker);
    speakerItem->setFlags(speakerItem->flags() ^ Qt::ItemIsEditable);
    setItem(line, SPEAKER_ID_COLUMN_INDEX, speakerItem);

    //Set timestamp
    QTableWidgetItem *tsItem = new QTableWidgetItem();
    tsItem->setText(timeStamp);
    tsItem->setFlags(tsItem->flags() ^ Qt::ItemIsEditable);
    setItem(line, TIMESTAMP_COLUMN_INDEX, tsItem);

    //Insert the chopped text block with the widget...
    DragWidget *wordBox = new DragWidget(this, text, TRANSCRIPTION_COLUMN_WIDTH, false);
    setRowHeight(line, wordBox->getBlockSize().height());
    setColumnWidth(2,wordBox->getBlockSize().width());
    setCellWidget(line, TRANSCRIPTION_COLUMN_INDEX, wordBox);

    return line;

}

void NERTableWidget::insertNewSubtableInLastEntry(NERSubTableWidget *subtable)
{
    ENGINE_DEBUG << "----- Row count: " << rowCount();

    if(rowCount()==0 || subtable==0){
        return;
    }
    setCellWidget(rowCount()-1, SUBTITLES_COLUMN_INDEX, subtable);
}

void NERTableWidget::deleteTablesContents(){
    clearContents();
    for(int i=0; i< rowCount(); i++){
        removeRow(i);
    }
    setRowCount(0);
}

QHash<qlonglong,QString> NERTableWidget::getHashedSubtableData()
{
    return *subtileDataHashedByTimestamp;
}

/*******************************************************************************
 * NER Stats Computation.
 ******************************************************************************/
int NERTableWidget::computeNERStats_N()
{
    int numWords=0;
    int numPontuation=0;

    if(subtileDataHashedByTimestamp!=0){

        QList<QString> subtitles = subtileDataHashedByTimestamp->values();

        for(int i=0; i<subtitles.count();++i){
            QString str = subtitles.at(i);
            numWords += str.trimmed().split(" ").count();

            numPontuation += str.count(".");
            numPontuation += str.count("!");
            numPontuation += str.count("?");
            numPontuation += str.count(";");
            numPontuation += str.count(",");
        }
    }

    //speaker transitions...
    int transitions = 0;
    for(int i=0; i<rowCount()-1;i++){
        if(item(i,0)->text() != item(i+1,0)->text() ){
            transitions++;
        }
    }

    return numWords + numPontuation + transitions;
}

double NERTableWidget::computeNERStats_NerValue(){

    int N = computeNERStats_N();
    double re = computeNERStats_RecognitionErrors();
    double er = computeNERStats_EditionErrors();

    double ner = 1.0f - (double)(re+er)/N;

    double delay = computeNERStats_Delay() / 1000; //in seconds...

    //saveValues
    nerStatsDataValues.setNCount(N)
            .setEditionErrors(er)
            .setRecognitionErrors(re)
            .setAvgDelay(delay)
            .setNerValue(ner);

    ENGINE_DEBUG << "NER -> " << "\n\tN = " << N
                 << "\n\tEdition Errors = "<< er
                 << "\n\tRecog Errors = " << re
                 << "\n\tNER = " << ner
                 << "\n\tAvg Delay = " << delay;

    return ner;
}

NERStatsData NERTableWidget::getNERStatsValues()
{
    return nerStatsDataValues;
}

double NERTableWidget::computeNERStats_EditionErrors()
{
    double editionError = 0;
    for(int i=0; i<rowCount(); i++){

        NERSubTableWidget *subTable = static_cast<NERSubTableWidget*>(cellWidget(i, SUBTITLES_COLUMN_INDEX));
        if(subTable != 0){
            editionError += subTable->getEditionErrors();
        }
    }
    return editionError;
}

double NERTableWidget::computeNERStats_RecognitionErrors(){
    double editionError = 0;
    for(int i=0; i<rowCount(); i++){

        NERSubTableWidget *subTable = static_cast<NERSubTableWidget*>(cellWidget(i, SUBTITLES_COLUMN_INDEX));
        if(subTable != 0){
            editionError += subTable->getRecognitionErrors();
        }
    }
    return editionError;
}

double NERTableWidget::computeNERStats_Delay(){
    double acumulatedDelay=0.0;
    int numDelayCounts = 0;

    int latestSubtitleIndex=0;

    for(int i=0; i<transcriptionList->count(); ++i)
    {
        BlockTRS btr = transcriptionList->at(i);

        if(!btr.getText().contains(" ") && !btr.getText().isEmpty()){
            //single words.
            for(int k = latestSubtitleIndex; k<subtitleTableData->count(); ++k)
            {
                BlockTRS subBtr = subtitleTableData->at(k);

                if(btr.getText().compare(subBtr.getText())==0){
                    qlonglong subTime = getTimeInMilis(subBtr.getSyncTime());
                    qlonglong transTime = getTimeInMilis(btr.getSyncTime());

                    if(subTime >= transTime){
                        latestSubtitleIndex = k;

                        acumulatedDelay += (subTime - transTime);
                        numDelayCounts++;
                    }
                }
            }
        }
    }

    return acumulatedDelay/ (double)numDelayCounts;

}

qlonglong NERTableWidget::getTimeInMilis(QString time)
{
    if(time==0 || time.isEmpty()){
        return 0;
    }

    QStringList ls = time.split(".");
    QString secs = ls[0];
    QString mils = ls[1];
    qlonglong timeMilis = (secs.toLongLong())*1000 + mils.toLongLong();

    return timeMilis;
}

QString NERTableWidget::getTableTransRowText(int row)
{
    QString ret;

    if(row<0 || row >= rowCount()){
        return ret;
    }

    DragWidget* dw = static_cast<DragWidget*>(cellWidget(row,TRANSCRIPTION_COLUMN_INDEX));
    if(dw!=0){
        ret.append(dw->getText());
    }

    return ret;
}

QList<DragLabel*> NERTableWidget::getTableTransRowLabels(int row)
{
    QList<DragLabel*> labels;

    if(row<0 || row >= rowCount()){
        return labels;
    }

    DragWidget* dw = static_cast<DragWidget*>(this->cellWidget(row,TRANSCRIPTION_COLUMN_INDEX));
    if(dw!=0){
        QList<DragLabel*> lab = dw->getLabels();
        labels.append(lab);
    }

    return labels;
}

void NERTableWidget::makeTableRowDiff(int row)
{
    if(row<0 || row >= rowCount()){
        return;
    }

    ENGINE_DEBUG << "-- Diff of line = " << row;


    QString textTrans = getTableTransRowText(row);
    ENGINE_DEBUG << "Raw text = " << textTrans;

    NERSubTableWidget* subTable = static_cast<NERSubTableWidget*>(cellWidget(row,SUBTITLES_COLUMN_INDEX));
    QString subText;
    if(subTable!=0){
        subText = subTable->getJointSubTableText();
    }
    ENGINE_DEBUG << "Subtable text = " << subText;

    QList<Diff> newList;

    if(textTrans.count()!=0 && subText.count()!=0){
        diff_match_patch diff;
        QList<Diff> list = diff.diff_main(textTrans, subText, true);

        ENGINE_DEBUG << "Preprocessing...";
        for(int i=0;i<list.count(); i++){
            Diff d = list.at(i);
            ENGINE_DEBUG << i << d.toString();
        }

        newList = reprocessdistanceOutput(list);

        for(int i=0;i<newList.count(); i++){
            Diff d = newList.at(i);
            ENGINE_DEBUG << i << d.toString();
        }
    }

    applyEditionProperties(row, newList);
}

QList<Diff> NERTableWidget::reprocessdistanceOutput(QList<Diff> &diffList)
{
    QList<Diff> preRet;

    Operation lastOp;
    QString lastString;
    bool isNewString = true;

    for(int i=0; i<diffList.count(); i++){
        Diff d = diffList.at(i);
        if(d.operation == DELETE){
            //ignore.
            continue;
            //preRet.append(d);
        }
        else{
            preRet.append(d);
        }
//        else if(d.text == " "){
//            //delimiter
//            Diff val(lastOp, lastString);
//            preRet.append(val);

//            isNewString = true;
//            lastString.clear();
//        }
//        else if(d.operation == INSERT){
//            if(isNewString){
//                lastOp = INSERT;
//            }
//            lastString.append(d.text);
//        }
//        else if(d.operation == EQUAL){
//            if(isNewString){
//                lastOp = EQUAL;
//            }
//            lastString.append(d.text);
//        }
    }

    QList<Diff> ret;

    for(int k=0; k<preRet.count();k++){
        Diff d = preRet.at(k);

        QStringList texList = d.text.trimmed().split(" ");
        if(texList.count()>1){
            for(int i=0; i<texList.count(); i++){
                Diff s(d.operation, texList.at(i));
                ret.append(s);
            }
        }
        else{
            ret.append(d);
        }
    }

    return ret;
}

void NERTableWidget::applyEditionProperties(int row, QList<Diff> &diffList)
{
    if(diffList.count()==0 || row < 0 || row >= rowCount()){
        return;
    }

    NERSubTableWidget* subTable = static_cast<NERSubTableWidget*>(cellWidget(row, SUBTITLES_COLUMN_INDEX));

    if(subTable!=0){
        QList<DragLabel*> dragLabs = subTable->getSubTableLabels();

        ENGINE_DEBUG << "Labels size = " << dragLabs.count();
        ENGINE_DEBUG << "Diff list = " << diffList.count();

        for(int i=0; i<dragLabs.count(); i++){
            DragLabel* label = dragLabs.at(i);
            Diff df = diffList.at(i);

            if(df.operation == EQUAL){
                label->setupLabelType(CorrectEdition);
                label->setErrorWeight(ERROR_WEIGHT_0);
            }
            else{
                label->setupLabelType(EditionError);
                label->setErrorWeight(ERROR_WEIGHT_025);
            }
        }
    }

}

/*******************************************************************************
 *******************************************************************************
 * NERSubTableWidget class defines the structure if each subtable entry that
 * will hold the subtitle information data. This nested structure is required
 * since the relation between transcription and subtitles is 1 to N.
 ******************************************************************************/
NERSubTableWidget::NERSubTableWidget(QWidget *parent): QTableWidget(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSortingEnabled(false);
    setColumnCount(2);
    //setColumnWidth(SUB_TIMESTAMP_COLUMN_INDEX, SUB_TIMESTAMP_COLUMN_WIDTH);
    setColumnWidth(SUB_SUBTITLES_COLUMN_INDEX, SUB_SUBTITLES_COLUMN_WIDTH+150);
    setRowCount(0);
    //note: we don't want to display the line and column headers of each subtable
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);

    connect(this, SIGNAL(cellClicked(int,int)), this, SLOT(videoSeekFromStamp(int,int)));

}

void NERSubTableWidget::setMediaWidget(MediaMngWidget *mediaWidget)
{
    mediaMngWidget = mediaWidget;
}

int NERSubTableWidget::insertNewTableEntry(QString &timeStamp, QString &text)
{
    int line = rowCount();
    insertRow(line);

    //Set timestamp
    QTableWidgetItem *tsItem = new QTableWidgetItem();
    tsItem->setText(timeStamp);
    tsItem->setFlags(tsItem->flags() ^ Qt::ItemIsEditable);
    setItem(line, SUB_TIMESTAMP_COLUMN_INDEX, tsItem);

    //Insert the chopped text block with the widget...
    DragWidget *wordBox = new DragWidget(this, text, SUBTITLES_COLUMN_WIDTH-30, true);
    setRowHeight(line, wordBox->getBlockSize().height());
    setColumnWidth(SUBTITLES_COLUMN_INDEX,SUBTITLES_COLUMN_WIDTH);
    setCellWidget(line, SUB_SUBTITLES_COLUMN_INDEX, wordBox);

    return line;
}

int NERSubTableWidget::insertNewTableEntry(QString &timeStamp, DragWidget *wordBox)
{
    int line = rowCount();
    insertRow(line);

    //Set timestamp
    QTableWidgetItem *tsItem = new QTableWidgetItem();
    tsItem->setText(timeStamp);
    tsItem->setFlags(tsItem->flags() ^ Qt::ItemIsEditable);
    setItem(line, SUB_TIMESTAMP_COLUMN_INDEX, tsItem);

    //Insert the chopped text block with the widget...
//    DragWidget *wordBox = new DragWidget(this, listItemLabels, SUBTITLES_COLUMN_WIDTH-30, true);
    setRowHeight(line, wordBox->getBlockSize().height());
    setColumnWidth(SUBTITLES_COLUMN_INDEX,SUBTITLES_COLUMN_WIDTH);
    setCellWidget(line, SUB_SUBTITLES_COLUMN_INDEX, wordBox);

    return line;
}

BlockTRS NERSubTableWidget::getSubtableRowData(int row)
{
    BlockTRS ret;
    if(row>=rowCount() || row < 0)
    {
        return ret;
    }

    QString timeStamp = item(row, SUB_TIMESTAMP_COLUMN_INDEX)->text();
    QString subtitleText = item(row, SUB_SUBTITLES_COLUMN_INDEX)->text();

    ret.setSyncTime(timeStamp).setText(subtitleText);

    return ret;
}


void NERSubTableWidget::videoSeekFromStamp(int row, int column)
{
    ENGINE_DEBUG << "Row = " << row << "Column = " << column;

    QString timeStamp = item(row, SUB_TIMESTAMP_COLUMN_INDEX)->text();

    QStringList ls = timeStamp.split(".");
    QString secs = ls[0];
    QString mils = ls[1];
    qlonglong timeMilis = (secs.toLongLong())*1000
            + mils.toLongLong()
            -mils.toLongLong() % SUBTITLE_CHECK_INTERVAL;

    ENGINE_DEBUG << "Row = " << row << "Column = " << column;
    ENGINE_DEBUG << "\nTimeMilis =" << timeMilis << "\nTimeOrig =" << timeStamp;

    mediaMngWidget->seekVideo(timeMilis);
}

void NERTableWidget::setTableName(QString &tableNam)
{
    tableName = tableNam;
}

QString NERTableWidget::getTableName()
{
    return tableName;
}

void NERTableWidget::setResponsible(QString &resp)
{
    responsible = resp;
}

QString NERTableWidget::getResponsible()
{
    return responsible;
}

void NERTableWidget::setDescription(QString &desc)
{
    description = desc;
}

QString NERTableWidget::getDescription()
{
    return description;
}

QString NERSubTableWidget::getJointSubTableText()
{
    QString ret;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(this->cellWidget(i,1));
        if(dw!=0){
            ret.append(dw->getText());
        }
    }

    return ret;
}

QList<DragLabel*> NERSubTableWidget::getSubTableLabels()
{
    QList<DragLabel*> labels;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(this->cellWidget(i,1));
        if(dw!=0){
            QList<DragLabel*> lab = dw->getLabels();
            labels.append(lab);
        }
    }

    return labels;
}

double NERSubTableWidget::getEditionErrors()
{
    double edError = 0;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(cellWidget(i, SUB_SUBTITLES_COLUMN_INDEX));
        if(dw!=0){
            edError += dw->getEditionErrors();
        }
    }
    return edError;
}

double NERSubTableWidget::getRecognitionErrors()
{
    double rError = 0;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(cellWidget(i, SUB_SUBTITLES_COLUMN_INDEX));
        rError += dw->getEditionErrors();
    }
    return rError;
}

NERSubTableWidget::~NERSubTableWidget()
{

}


