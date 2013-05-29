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

//    horizontalHeader()->setResizeMode(QHeaderView::Interactive);
//    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

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
    setColumnWidth(3, SUBTITLES_COLUMN_WIDTH+250);

    //connect(headerView, SIGNAL(sectionResized(int,int,int)), this, SLOT(columnTableResized(int,int,int)));

    subtileDataHashedByTimestamp = new QHash<qlonglong,QString>();

    nerStatsDataValues.resetDataToZero();

}


NERTableWidget::~NERTableWidget()
{
    delete headerView;
    headerView = NULL;
}

void NERTableWidget::setMediaWidget(MediaMngWidget *mediaWid){
    mediaMngWidget = mediaWid;
}

/*******************************************************************************
 * Sets table main data.. used in project import
 ******************************************************************************/
void NERTableWidget::setMainDataList(QList<BlockTRS> *transList, QList<BlockTRS> subsList)
{
    transcriptionList = transList;
    subtitleTableData = new QList<BlockTRS>(subsList);;
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

    for(int i=0; i<subtitleTableData->count(); i++){
        BlockTRS btr = subtitleTableData->at(i);

        QString ts = btr.getSyncTime();
        QString text = btr.getText();

        ENGINE_DEBUG << "Time " << ts;
        ENGINE_DEBUG << "Text " << text;

        insertTimeStampsHashedMap(ts, text);

    }

    //Merge the translation with the subtitles...
    int i=0;
    int line=0;
    for(int j=0; j<transcription->count(); j++){
        NERSubTableWidget *subTable = new NERSubTableWidget(this);
        subTable->setMediaWidget(mediaMngWidget);
        subTable->setSelectionMode(QAbstractItemView::SingleSelection);
        subTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        if(j < transcription->count()-1){
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

                    if(i == subsTrsBlocks->count()-1){
                        //set the last subtile (for the case of #Trans >>> #subitles)
                        setCellWidget(line++, SUBTITLES_COLUMN_INDEX, subTable);

                        //Everything is loaded... os exit!
                        return;
                    }
                }

                else if(subBtr.getSyncTime().toDouble() >= transBtrNext.getSyncTime().toDouble()){
                    //skip to the new transcription line...

                    if(subTable->height() > rowHeight(line)){
                        //setRowHeight(line, subTable->height());
                        verticalHeader()->resizeSection(line, 200/*subTable->height()*/);
                    }

                    setCellWidget(line++, SUBTITLES_COLUMN_INDEX, subTable);
                    break;
                }

                ////setCellWidget(line++, SUBTITLES_COLUMN_INDEX, subTable);
            }
        }
        //Insert the rest of the subtitles in the last transcription line
        if(j == transcription->count()-1){

            for( ; i< subsTrsBlocks->count(); i++){
                BlockTRS subBtr = subsTrsBlocks->at(i);
                QString sync = subBtr.getSyncTime();
                QString text = subBtr.getText();

                ENGINE_DEBUG << "New entry -> Time = " << sync << "-- Text = " << text;

                subTable->insertNewTableEntry(sync, text);
            }

            setCellWidget(line++, SUBTITLES_COLUMN_INDEX, subTable);
        }
    }
}

void NERTableWidget::insertTimeStampsHashedMap(QString &timeStamp, QString &text)
{
    QStringList ls = timeStamp.split(".");
    QString secs;
    QString mils;

    qlonglong timeMilis;

    if(ls.count()==2){
        secs = ls[0];
        mils = ls[1];
        timeMilis = (secs.toLongLong())*1000
                + mils.toLongLong()
                - mils.toLongLong() % SUBTITLE_CHECK_INTERVAL;
    }
    else if(ls.count()==1){
        timeMilis = (secs.toLongLong())*1000;
    }

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
    DragWidget *wordBox = new DragWidget(this, text, TRANSCRIPTION_COLUMN_WIDTH, true);
    setRowHeight(line, wordBox->getBlockSize().height());
    setColumnWidth(2,wordBox->getBlockSize().width());
    setCellWidget(line, TRANSCRIPTION_COLUMN_INDEX, wordBox);

    return line;

}

int NERTableWidget::insertNewTableEntry(QString &speaker, QString &timeStamp)
{

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
//    DragWidget *wordBox = new DragWidget(this, text, TRANSCRIPTION_COLUMN_WIDTH, true);
//    setRowHeight(line, wordBox->getBlockSize().height());
//    setColumnWidth(2,wordBox->getBlockSize().width());
//    setCellWidget(line, TRANSCRIPTION_COLUMN_INDEX, wordBox);

    return line;
}

int NERTableWidget::insertTranscriptionLabelInLastEntry(DragWidget *wordBox)
{
    if(rowCount()==0 || wordBox==0)
    {
        return -1;
    }
    int line = rowCount()-1;

    setRowHeight(line, wordBox->getBlockSize().height());
    setColumnWidth(2,wordBox->getBlockSize().width());
    setCellWidget(line, TRANSCRIPTION_COLUMN_INDEX, wordBox);
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
    nerStatsDataValues.setN_ponctuation(numPontuation);
    nerStatsDataValues.setN_words(numWords);

    //speaker transitions...
    int transitions = 0;
    for(int i=0; i<rowCount()-1;i++){
        if(item(i,0)->text() != item(i+1,0)->text() ){
            transitions++;
        }
    }

    nerStatsDataValues.setN_transitions(transitions);

    return numWords + numPontuation + transitions;
}

NERStatsData NERTableWidget::computeNERStats_NerValue(){

    nerStatsDataValues.resetDataToZero();

    int N = computeNERStats_N();
    double re = computeNERStats_RecognitionErrors();
    double er = computeNERStats_EditionErrors();
    int ins = computeInsertions();
    int del = computeDeletions();
    int subs = computeSubstitutions();

    double ner = 1.0f - (double)(re+er)/N;

    double delay = computeNERStats_Delay() / 1000; //in seconds...

    double wordReduction = computeWordReduction();
    int transWords = getAllTranscriptionLabels().count();

    int subWords, subchars;
    getNumSubsWordsChars(subWords, subchars);

    //saveValues
    nerStatsDataValues.setNCount(N)
            .setEditionErrors(er)
            .setRecognitionErrors(re)
            .setAvgDelay(delay)
            .setNerValue(ner)
            .setReduction(wordReduction)
            .setTransWordCount(transWords);

    ENGINE_DEBUG << "NER -> " << "\n\tN = " << N
                 << "\n\tEdition Errors = " << er
                 << "\n\tRecog Errors = "   << re
                 << "\n\tNER = "            << ner
                 << "\n\tAvg Delay = "      << delay
                 << "\n\tInsertions = "     << ins
                 << "\n\tDeletions = "      << del
                 << "\n\tSubstitutions = "  << subs;


    return nerStatsDataValues;
}

NERStatsData NERTableWidget::getNERStatsValues()
{
    return nerStatsDataValues;
}

double NERTableWidget::computeNERStats_EditionErrors()
{
    double editionError = 0;
    for(int i=0; i<rowCount(); i++){

        //Get the Recog Errors from the subtable...
        NERSubTableWidget *subTable = static_cast<NERSubTableWidget*>(cellWidget(i, SUBTITLES_COLUMN_INDEX));
        if(subTable != 0){
            editionError += subTable->getEditionErrors(nerStatsDataValues);
        }

        //Get the recognition value from the transcription table line...
        DragWidget* drag = static_cast<DragWidget*>(cellWidget(i, TRANSCRIPTION_COLUMN_INDEX));
        if(drag !=0){
            editionError += drag->getEditionErrors(nerStatsDataValues);
        }
    }
    return editionError;
}

double NERTableWidget::computeNERStats_RecognitionErrors(){
    double recogError = 0;
    for(int i=0; i<rowCount(); i++){

        //Get the Recog Errors from the subtable...
        NERSubTableWidget *subTable = static_cast<NERSubTableWidget*>(cellWidget(i, SUBTITLES_COLUMN_INDEX));
        if(subTable != 0){
            recogError += subTable->getRecognitionErrors(nerStatsDataValues);
        }

        //Get the recognition value from the transcription table line...
        DragWidget* drag = static_cast<DragWidget*>(cellWidget(i, TRANSCRIPTION_COLUMN_INDEX));
        if(drag !=0){
            recogError += drag->getRecognitionErrors(nerStatsDataValues);
        }
    }
    return recogError;
}

double NERTableWidget::computeInsertions()
{
    double insertions = 0;
    for(int i=0; i<rowCount(); i++){

        NERSubTableWidget *subTable = static_cast<NERSubTableWidget*>(cellWidget(i, SUBTITLES_COLUMN_INDEX));
        if(subTable != 0){
            insertions += subTable->getInsertions(nerStatsDataValues);
        }

        //Get the recognition value from the transcription table line...
        DragWidget* drag = static_cast<DragWidget*>(cellWidget(i, TRANSCRIPTION_COLUMN_INDEX));
        if(drag !=0){
            insertions += drag->getInsertions(nerStatsDataValues);
        }
    }
    return insertions;
}

double NERTableWidget::computeDeletions()
{
    double deletions = 0;
    for(int i=0; i<rowCount(); i++){

        NERSubTableWidget *subTable = static_cast<NERSubTableWidget*>(cellWidget(i, SUBTITLES_COLUMN_INDEX));
        if(subTable != 0){
            deletions += subTable->getDeletions(nerStatsDataValues);
        }

        //Get the recognition value from the transcription table line...
        DragWidget* drag = static_cast<DragWidget*>(cellWidget(i, TRANSCRIPTION_COLUMN_INDEX));
        if(drag !=0){
            deletions += drag->getDeletions(nerStatsDataValues);
        }
    }
    return deletions;
}

double NERTableWidget::computeSubstitutions()
{
    double substitutions = 0;
    for(int i=0; i<rowCount(); i++){

        NERSubTableWidget *subTable = static_cast<NERSubTableWidget*>(cellWidget(i, SUBTITLES_COLUMN_INDEX));
        if(subTable != 0){
            substitutions += subTable->getSubstitutions(nerStatsDataValues);
        }

        //Get the recognition value from the transcription table line...
        DragWidget* drag = static_cast<DragWidget*>(cellWidget(i, TRANSCRIPTION_COLUMN_INDEX));
        if(drag !=0){
            substitutions += drag->getSubstitutions(nerStatsDataValues);
        }
    }
    return substitutions;
}

double NERTableWidget::computeNERStats_Delay(){
    double acumulatedDelay=0.0;
    int numDelayCounts = 0;

    int latestSubtitleIndex=0;

    for(int i=0; i<transcriptionList->count(); ++i)
    {
        BlockTRS btr = transcriptionList->at(i);
        QString transLine = btr.getText();

        if(!transLine.contains(" ") && !transLine.isEmpty()){
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

    if(numDelayCounts == 0){
        //No matching at all
        return 0;
    }

    return acumulatedDelay/ (double)numDelayCounts;
}

double NERTableWidget::computeWordReduction()
{
    double transWords = getAllTranscriptionLabels().count();
    double subtsWords = getAllSubtableLabels().count();

    if(transWords==0){
        return 0;
    }

    return 1.0 - subtsWords/transWords;
}

void NERTableWidget::getNumSubsWordsChars(int &numWords, int &numChars)
{
    QList<DragLabel*> subsLabels = getAllSubtableLabels();

    numChars = 0;
    numWords = subsLabels.count();

    for(int i=0; i<subsLabels.count(); i++)
    {
        DragLabel* lab = subsLabels.at(i);
        if(lab!=0){
            numChars += lab->labelText().count();
        }
    }
}

int NERTableWidget::getTotalSubsTimeInSeconds()
{

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

QList<Diff> NERTableWidget::computeDifferences(QString &transText, QString &subsText)
{
    QString dwDiffString = Utils::executeWordDiff(transText, subsText);
    dwDiffString = dwDiffString.simplified();

    QList<Diff> ret;

    if(dwDiffString.count()==0)
    {
        return ret;
    }

    QStringList modifications = dwDiffString.replace("[","@@@[")
            .replace("]","]@@@")
            .replace("{", "@@@{")
            .replace("}", "}@@@")
            .split("@@@");

    //split a set of strings with common operations...
    for(int i=0; i<modifications.count(); i++)
    {
        QString modif = modifications.at(i);

        modif.trimmed();

        if(modif.isEmpty()){
            continue;
        }

        if(modif.startsWith("{+")){// Insertion
            modif = modif.right(modif.count()-2);//remove "{+"
            modif.chop(2);//remove "+}"
            ret.append( buildDiffList(INSERT, modif) );
        }
        else if(modif.startsWith("[-")){// Insertion
            modif = modif.right(modif.count()-2);//remove "[-"
            modif.chop(2);//remove "-]"
            ret.append( buildDiffList(DELETE, modif) );
        }
        else{ //Equal
            ret.append( buildDiffList(EQUAL, modif) );
        }
    }
}

QList<Diff> NERTableWidget::buildDiffList(Operation op, QString &text)
{
    QList<Diff> ret;

    if(text.isEmpty()){
        return ret;
    }

    QStringList wordsList = text.split(" ");

    for(int i=0; i < wordsList.count(); i++){
        QString s = wordsList.at(i);
        if(!s.isEmpty()){
            ret.append(Diff(op, s));
        }
    }

    return ret;
}

QList<Diff> NERTableWidget::removeDeletions(QList<Diff> &list)
{
    QList<Diff> ret;

    for(int i=0; i<list.count(); i++){
        Diff d = list.at(i);
        if(d.operation == DELETE){
            continue;
        }
        ret.append(d);
    }

    return ret;
}

QList<Diff> NERTableWidget::removeInsertions(QList<Diff> &list)
{
    QList<Diff> ret;

    for(int i=0; i<list.count(); i++){
        Diff d = list.at(i);
        if(d.operation == INSERT){
            continue;
        }
        ret.append(d);
    }

    return ret;
}


QString NERTableWidget::getAllTranslationText()
{
    QString transText;
    for(int i=0; i < rowCount()-1; i++){
        transText.append(getTableTransRowText(i));
        transText.append(" ");
    }
    transText.append( getTableTransRowText( rowCount()-1 ) );

    return transText;
}

QString NERTableWidget::getAllSubtableText()
{
    QString subText;

    for(int i=0; i < rowCount(); i++){
        NERSubTableWidget* subTable = static_cast<NERSubTableWidget*>(cellWidget(i,SUBTITLES_COLUMN_INDEX));
        if(subTable!=0){
            subText.append(subTable->getJointSubTableText());
            subText.append(" ");
        }
    }
    return subText;
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

QList<DragLabel*> NERTableWidget::getAllSubtableLabels()
{
    QList<DragLabel*> ret;

    for(int i=0; i<rowCount(); i++){
        NERSubTableWidget* subTable = static_cast<NERSubTableWidget*>(cellWidget(i, SUBTITLES_COLUMN_INDEX));
        if(subTable!=0){
           ret.append(subTable->getSubTableLabels());
        }
    }

    return ret;
}

QList<DragLabel*> NERTableWidget::getAllTranscriptionLabels()
{
    QList<DragLabel*> ret;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(cellWidget(i, TRANSCRIPTION_COLUMN_INDEX));
        if(dw!=0){
           ret.append(dw->getLabels());
        }
    }

    return ret;
}


void NERTableWidget::applyEditionProperties(QList<Diff> &diffList)
{
    if(diffList.count()==0 ){
        return;
    }

    QList<DragLabel*> allLabels = getAllSubtableLabels();

    for(int i=0; i<allLabels.count(); i++){
        DragLabel* label = allLabels.at(i);
        Diff df = diffList.at(i);

        if(df.operation == EQUAL){
            label->setupLabelType(CorrectEdition);
            label->setErrorClass(NotDefined);
            label->setErrorWeight(ERROR_WEIGHT_0);
        }
        else{
            label->setupLabelType(EditionError);
            label->setErrorWeight(ERROR_WEIGHT_025);
            label->setErrorClass(NotDefined);
        }
        QString s("");
        label->setComment(s);
    }
}

void NERTableWidget::applyEditionPropertiesToTranscription(QList<Diff> &diffList)
{
    if(diffList.count()==0 ){
        return;
    }

    QList<DragLabel*> allLabels = getAllTranscriptionLabels();

    for(int i=0; i<allLabels.count(); i++){
        DragLabel* label = allLabels.at(i);
        Diff df = diffList.at(i);

        if(df.operation == EQUAL){
            label->setupLabelType(CorrectEdition);
            label->setErrorClass(NotDefined);
            label->setErrorWeight(ERROR_WEIGHT_0);
        }
        else{ //deletion
            label->setupLabelType(TrancriptionDeletion);
            label->setErrorClass(NotDefined);
            label->setErrorWeight(ERROR_WEIGHT_0);
        }
        QString s("");
        label->setComment(s);
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
    setSelectionMode(QAbstractItemView::NoSelection);
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

double NERSubTableWidget::getEditionErrors(NERStatsData &nerStats)
{
    double edError = 0;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(cellWidget(i, SUB_SUBTITLES_COLUMN_INDEX));
        if(dw!=0){
            edError += dw->getEditionErrors(nerStats);
        }
    }
    return edError;
}

double NERSubTableWidget::getRecognitionErrors(NERStatsData &nerStats)
{
    double rError = 0;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(cellWidget(i, SUB_SUBTITLES_COLUMN_INDEX));
        rError += dw->getRecognitionErrors(nerStats);
    }
    return rError;
}

double NERSubTableWidget::getInsertions(NERStatsData &nerStats)
{
    double insertions = 0;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(cellWidget(i, SUB_SUBTITLES_COLUMN_INDEX));
        insertions += dw->getInsertions(nerStats);
    }
    return insertions;
}

double NERSubTableWidget::getDeletions(NERStatsData &nerStats)
{
    double deletions = 0;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(cellWidget(i, SUB_SUBTITLES_COLUMN_INDEX));
        deletions += dw->getDeletions(nerStats);
    }
    return deletions;
}

double NERSubTableWidget::getSubstitutions(NERStatsData &nerStats)
{
    double substitutions = 0;

    for(int i=0; i<rowCount(); i++){
        DragWidget* dw = static_cast<DragWidget*>(cellWidget(i, SUB_SUBTITLES_COLUMN_INDEX));
        substitutions += dw->getSubstitutions(nerStats);
    }
    return substitutions;
}

NERSubTableWidget::~NERSubTableWidget()
{

}


