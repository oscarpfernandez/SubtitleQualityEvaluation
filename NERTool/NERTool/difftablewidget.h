#ifndef DIFFTABLEWIDGET_H
#define DIFFTABLEWIDGET_H

#include <qwidget.h>
#include <qtablewidget.h>
#include <qmdiarea.h>
#include <qmdisubwindow.h>
#include <QHBoxLayout>

const int TIMESTAMP_COLUMN_WIDTH = 100;
const int TRANSCRIPTION_COLUMN_WIDTH = 400;
const int SUBTITLES_COLUMN_WIDTH = 400;

class DiffTableWidget : public QTableWidget
{

Q_OBJECT

public:
	DiffTableWidget(QWidget *parent = 0);
	~DiffTableWidget();
	void insertNewTableLine();
	void insertTextBlockOnTableEntry(QString &text, int &line, int &column);


	
};

#endif