#include "difftablewidget.h"
#include <qwidget.h>
#include <qtablewidget.h>
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
    setRowCount(2);

	setColumnWidth(0,TIMESTAMP_COLUMN_WIDTH);
	setColumnWidth(1,TRANSCRIPTION_COLUMN_WIDTH);
	setColumnWidth(2,SUBTITLES_COLUMN_WIDTH);

	QStringList headers;
    headers << "Timestamp"
			<< "Original Transcription"
            << "Subtitles";
    setHorizontalHeaderLabels(headers);
	int l=1, c=1; 
	insertTextBlockOnTableEntry(QString("This is a test to test the lenght of the string!"), l, c);

}

void DiffTableWidget::insertNewTableLine()
{
	QTableWidgetItem *newItem = new QTableWidgetItem();
	newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

}

void DiffTableWidget::insertTextBlockOnTableEntry(QString &text, int &line, int &column)
{
	if(text == 0 || text.count() == 0 ){ return; }

	DragWidget *wordBox = new DragWidget(this, text);
	QTableWidgetItem *item = new QTableWidgetItem();
	
	setItem(1, 0, item);
	setCellWidget(1, 1, wordBox);
	setRowCount(rowCount()+1);



}

DiffTableWidget::~DiffTableWidget()
{

}



