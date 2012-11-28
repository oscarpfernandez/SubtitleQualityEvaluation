#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

//! [0]
class DragWidget : public QWidget
{
public:
	DragWidget(QWidget *parent, QString &textBlock);

protected:
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
};
//! [0]

#endif
