#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include <QMap>
#include "draglabel.h"
#include "dragwidgetcomment.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

const QString CORRECT_EDITION_STR = "Correct";
const QString RECOG_ERROR_STR = "RecognitionError";
const QString EDITION_ERROR = "EditionError";
const QString EDITION_COMMENT = "Edit Comnment";

//! [0]
class DragWidget : public QWidget
{
    Q_OBJECT
public:
    DragWidget(QWidget *parent, QString &textBlock, int maxWidth);
    ~DragWidget();
    QSize getBlockSize();
    void showCommentEditor();

protected:
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QList<DragLabel*> *m_labelsPointerList;
    int m_maxWidgetWidth;
    int m_numberOfLines;
    int m_labelSize;
    int m_counter;
    int m_numLines;
    QString *editionComment;
    DragWidgetComment *dwcomment;
    void setComment(QString &newComment);
    QString getComment();


public slots:
    void setEditCommentSlot(QString &comment);
};

#endif
