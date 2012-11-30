#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>

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

private:
    QString m_labelText;
    QSize size;

};

#endif
