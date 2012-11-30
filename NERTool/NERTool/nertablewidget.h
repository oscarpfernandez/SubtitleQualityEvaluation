#ifndef DIFFTABLEWIDGET_H
#define DIFFTABLEWIDGET_H

#include <qwidget.h>
#include <qtablewidget.h>
#include <qmdiarea.h>
#include <qmdisubwindow.h>
#include <QHBoxLayout>

const int SPEAKER_ID_COLUMN_WIDTH = 100;
const int SPEAKER_ID_COLUMN_INDEX = 0;
const int TIMESTAMP_COLUMN_WIDTH = 70;
const int TIMESTAMP_COLUMN_INDEX = 1;
const int TRANSCRIPTION_COLUMN_WIDTH = 500;
const int TRANSCRIPTION_COLUMN_INDEX = 2;

const int SUBTITLES_COLUMN_WIDTH = 400;

class DiffTableWidget : public QTableWidget
{

Q_OBJECT

public:
	DiffTableWidget(QWidget *parent = 0);
	~DiffTableWidget();
	void insertNewTableLine();
    void insertNewTableEntry(QString &speaker, QString &TimeStamp, QString &text);

private:
    QHeaderView *headerView;

public slots:
    void columnTableResized(int column, int oldWidth, int newWidth);
};

#endif
