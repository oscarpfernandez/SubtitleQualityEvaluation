#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include "draglabelcomment.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;
QT_END_NAMESPACE

enum EditionTypeEnum {
    NotDefinedYet=0,
    CorrectEdition=1,
    EditionError=2,
    RecognitionError=3
};

enum ModificationType {
    NotDefined=0,
    Insertion=1,
    Deletion=2,
    Substitution=3
};

class DragLabel : public QLabel
{
public:
    DragLabel(const QString &text, QWidget *parent);
    QString labelText() const;
    void setupLabelType(EditionTypeEnum ete);
    void setComment(QString &newComment);
    QString getComment();
    void showCommentEditor();
    EditionTypeEnum getErrorType();
    double getErrorWeight();
    void setErrorWeight(double w);
    void setErrorClass(ModificationType modType);
    ModificationType getErrorClass();
    EditionTypeEnum editionEnumFromOrdinal(int value);
    ModificationType modificationTypeFromOrdinal(int value);
    void markAsDeleted();

private:
    QString m_labelText;
    QSize size;
    QString *editionComment;
    DragLabelComment *dwcomment;
    EditionTypeEnum errorType;
    double errorWeight; //0.25, 0.5 or 1
    ModificationType errorClass;

public slots:
    void setEditCommentSlot(QString &comment);

};

#endif
