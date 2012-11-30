#include "difftablewidget.h"
#include <qwidget.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include "dragwidget.h"
#include "draglabel.h"

/******************************************************************************
 * DiffTableWidget manages the table difference betwwen the original transcribded
 * and the subtitle texts. Manages the several word items allowing the export 
 * of the data to an XML stream.
 ******************************************************************************/

DiffTableWidget::DiffTableWidget(QWidget *parent) : QTableWidget(parent)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    //setFont(QFont("Courier New", 10, QFont::Normal));
	setSortingEnabled(false);
    setColumnCount(3);
    setRowCount(0);

//    setColumnWidth(0,SPEAKER_ID_COLUMN_WIDTH);
//    setColumnWidth(1,TIMESTAMP_COLUMN_WIDTH);
//	setColumnWidth(2,SUBTITLES_COLUMN_WIDTH);

	QStringList headers;
    headers << "Speaker ID"
            << "Timestamp"
            << "Transcription";
    setHorizontalHeaderLabels(headers);


    headerView = new QHeaderView(Qt::Horizontal);
    headerView->setResizeMode(QHeaderView::Fixed);
    setHorizontalHeader(headerView);
    setColumnWidth(0,SPEAKER_ID_COLUMN_WIDTH);
    setColumnWidth(1,TIMESTAMP_COLUMN_WIDTH);
    setColumnWidth(2,TRANSCRIPTION_COLUMN_WIDTH);




    connect(headerView, SIGNAL(sectionResized(int,int,int)), this, SLOT(columnTableResized(int,int,int)));

}

/*
 * Intercepts the signal provided by table header resized event, to adjust the contents
 * of the dragwidget. This slot then passes the event to the table
 *
 */
void DiffTableWidget::columnTableResized(int column, int oldWidth, int newWidth){
    QString d = QString::number(column).append("-").append(QString::number(oldWidth)).append("-").append(QString::number(newWidth));
    qDebug("Column Resized!!!");
    qDebug(d.toAscii());

    columnResized(column, oldWidth, newWidth);
}

void DiffTableWidget::insertNewTableLine()
{
	QTableWidgetItem *newItem = new QTableWidgetItem();
	newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

}

void DiffTableWidget::insertNewTableEntry(QString &speaker, QString &timeStamp, QString &text)
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
    setCellWidget(line, TRANSCRIPTION_COLUMN_INDEX, wordBox);

}

DiffTableWidget::~DiffTableWidget()
{

}



