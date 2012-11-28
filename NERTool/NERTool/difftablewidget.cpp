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
    setColumnCount(2);
    setRowCount(2);

	setColumnWidth(0,200);
    setColumnWidth(1,200);

	QStringList headers;
    headers << "Original Transcription"
            << "Subtitles";
    setHorizontalHeaderLabels(headers);

	insertTextBlockOnTableEntry(QString("This is a test!"));

}

void DiffTableWidget::insertNewTableLine()
{
	QTableWidgetItem *newItem = new QTableWidgetItem();
	newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

}

void DiffTableWidget::insertTextBlockOnTableEntry(QString &text)
{
	if(text == 0 || text.count() == 0 ){ return; }

	DragWidget *wordBox = new DragWidget(this, text);
	QTableWidgetItem *item = new QTableWidgetItem();
	
	setItem(1, 0, item);
	setCellWidget(1, 0, wordBox);
	setRowCount(rowCount()+1);



}

DiffTableWidget::~DiffTableWidget()
{

}



