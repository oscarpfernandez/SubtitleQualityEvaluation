#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include "draglabelcomment.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;
QT_END_NAMESPACE

class DragLabel : public QLabel
{
public:
    enum EditionTypeEnum {
        NotDefinedYet=0,
        CorrectEdition=1,
        EditionError=2,
        RecognitionError=3
    };
    DragLabel(const QString &text, QWidget *parent);
    QString labelText() const;
    void setupLabelType(DragLabel::EditionTypeEnum ete);
    void setComment(QString &newComment);
    QString getComment();
    void showCommentEditor();

private:
    QString m_labelText;
    QSize size;
    QString *editionComment;
    DragLabelComment *dwcomment;

public slots:
    void setEditCommentSlot(QString &comment);

};

#endif
