#ifndef DIFFTABLEWIDGET_H
#define DIFFTABLEWIDGET_H

#include <qwidget.h>
#include <qtablewidget.h>
#include <qmdiarea.h>
#include <qmdisubwindow.h>
#include <QHBoxLayout>

class DiffTableWidget : public QTableWidget
{

Q_OBJECT

public:
	DiffTableWidget(QWidget *parent = 0);
	~DiffTableWidget();
	void insertNewTableLine();
	void insertTextBlockOnTableEntry(QString &text);


	
};

#endif