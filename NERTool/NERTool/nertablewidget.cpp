#include "nertablewidget.h"
#include <qwidget.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include "dragwidget.h"
#include "draglabel.h"
#include "xmlhandler.h"

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
    setRowCount(0);

	QStringList headers;
    headers << "Speaker ID"
            << "Timestamp"
            << "Transcription"
            << "Subtitles";
    setHorizontalHeaderLabels(headers);


    headerView = new QHeaderView(Qt::Horizontal);
    //headerView->setResizeMode(QHeaderView::Fixed);
    setHorizontalHeader(headerView);
    setColumnWidth(0,SPEAKER_ID_COLUMN_WIDTH);
    setColumnWidth(1,TIMESTAMP_COLUMN_WIDTH);
    setColumnWidth(2,TRANSCRIPTION_COLUMN_WIDTH);
    setColumnWidth(3, SUBTITLES_COLUMN_WIDTH);

    connect(headerView, SIGNAL(sectionResized(int,int,int)), this, SLOT(columnTableResized(int,int,int)));

}

void NERTableWidget::loadXMLData(QList<BlockTRS> *trsBlocks){
    if(trsBlocks==0 || trsBlocks->count()==0){
        //Nothing to do...
        return;
    }

    //Fill the table with the entries...
    for(int i=0; i<trsBlocks->count(); i++){
        BlockTRS btr = trsBlocks->at(i);
        insertNewTableEntry(btr.getSpeaker(), btr.getSyncTime(), btr.getText());
    }
}

void NERTableWidget::loadSubtitlesXMLData(QList<BlockTRS> *trsBlocks){
    if(trsBlocks==0 || trsBlocks->count()==0){
        //Nothing to do...
        return;
    }

    NERSubTableWidget *subTable = new NERSubTableWidget(this);
    BlockTRS btr = trsBlocks->at(0);
    subTable->insertNewTableEntry(btr.getSyncTime(),btr.getText());
    BlockTRS btr2 = trsBlocks->at(1);
    subTable->insertNewTableEntry(btr2.getSyncTime(),btr2.getText());
    setCellWidget(0, SUBTITLES_COLUMN_INDEX, subTable);

}

/*
 * Intercepts the signal provided by table header resized event, to adjust the contents
 * of the dragwidget. This slot then passes the event to the table
 *
 */
void NERTableWidget::columnTableResized(int column, int oldWidth, int newWidth){
    QString d = QString::number(column).append("-").append(QString::number(oldWidth)).append("-").append(QString::number(newWidth));
    qDebug("Column Resized!!!");
    qDebug(d.toAscii());

    columnResized(column, oldWidth, newWidth);
}

void NERTableWidget::insertNewTableEntry(QString &speaker, QString &timeStamp, QString &text)
{
    if(text == 0 || text.count() == 0 ){ return; }

    int line = rowCount();
    insertRow(line);
    //Set Speaker
    QTableWidgetItem *speakerItem = new QTableWidgetItem();
    speakerItem->setText(speaker);
    setItem(line, SPEAKER_ID_COLUMN_INDEX, speakerItem);

    //Set timestamp
    QTableWidgetItem *tsItem = new QTableWidgetItem();
    tsItem->setText(timeStamp);
    setItem(line, TIMESTAMP_COLUMN_INDEX, tsItem);

    //Insert the chopped text block with the widget...
    DragWidget *wordBox = new DragWidget(this, text, TRANSCRIPTION_COLUMN_WIDTH);
    setRowHeight(line, wordBox->getBlockSize().height());
    setColumnWidth(2,wordBox->getBlockSize().width());
    setCellWidget(line, TRANSCRIPTION_COLUMN_INDEX, wordBox);

}

void NERTableWidget::deleteTablesContents(){
    clearContents();
    for(int i=0; i< rowCount(); i++){
        removeRow(i);
    }
    setRowCount(0);
}

NERTableWidget::~NERTableWidget()
{
    delete headerView;
    headerView = NULL;
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
    setColumnWidth(SUB_TIMESTAMP_COLUMN_INDEX, SUB_TIMESTAMP_COLUMN_WIDTH);
    setColumnWidth(SUB_SUBTITLES_COLUMN_INDEX, SUB_SUBTITLES_COLUMN_WIDTH);
    setRowCount(0);
    //note: we don't want to display the line and column headers of each subtable
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(false);
}

void NERSubTableWidget::insertNewTableEntry(QString &timeStamp, QString &text)
{
    int line = rowCount();
    insertRow(line);

    //Set timestamp
    QTableWidgetItem *tsItem = new QTableWidgetItem();
    tsItem->setText(timeStamp);
    setItem(line, SUB_TIMESTAMP_COLUMN_INDEX, tsItem);

    //Insert the chopped text block with the widget...
    DragWidget *wordBox = new DragWidget(this, text, SUBTITLES_COLUMN_WIDTH);
    setRowHeight(line, wordBox->getBlockSize().height());
    setColumnWidth(1,wordBox->getBlockSize().width());
    setCellWidget(line, SUB_SUBTITLES_COLUMN_INDEX, wordBox);

}

void NERSubTableWidget::getXMLNode()
{

}

NERSubTableWidget::~NERSubTableWidget()
{

}


