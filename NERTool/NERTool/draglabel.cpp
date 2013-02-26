#include <QtGui>
#include "draglabel.h"

/*******************************************************************************
 * This class defines each word block contained in the dragwidget, assigning
 * diferenciated properties to each element. With this it is possible to assign
 * a diferent "error" type to each block and the associated comment.
 ******************************************************************************/
DragLabel::DragLabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    m_labelText = text;
    editionComment = new QString();
    dwcomment = new DragLabelComment(parent);
    errorType = NotDefinedYet;
}

/*******************************************************************************
 * Getter for the drag label widget text.
 * Return:
 * - String with the associated text.
 ******************************************************************************/
QString DragLabel::labelText() const
{
    return m_labelText;
}

/*******************************************************************************
 * This function allows to define the base error type properties of the widget
 * Args:
 * - EditionTypeEnum: the error type assigned to the widget.
 ******************************************************************************/
void DragLabel::setupLabelType(EditionTypeEnum ete)
{
    errorType = ete;

    QFontMetrics metric(font());
    size = metric.size(Qt::TextSingleLine, m_labelText);

    QImage image(size.width() + 5, size.height() + 5, QImage::Format_ARGB32_Premultiplied);
    image.fill(qRgba(255, 255, 255, 0));

    QFont font;
    font.setStyleStrategy(QFont::ForceOutline);

    QLinearGradient gradient(0, 0, 0, image.height()-1);
    QPainter painter;

    if(ete == NotDefinedYet){
        QString s = QString::number(size.width());
        gradient.setColorAt(0.0, Qt::white);
        gradient.setColorAt(0.2, QColor(240, 240, 240));
        gradient.setColorAt(0.8, QColor(250, 250, 250));
        gradient.setColorAt(1.0, QColor(255, 255, 255));

        painter.begin(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(gradient);
        painter.drawRect(QRectF(0.1, 0.1, image.width()-1, image.height()-1));
        painter.setFont(font);
        painter.setBrush(Qt::white);
        painter.drawText(QRect(QPoint(3, 3), size), Qt::AlignCenter, m_labelText);
        painter.end();
    }

    else if(ete == CorrectEdition){
        QString s = QString::number(size.width());
        qDebug(s.toAscii());
        gradient.setColorAt(0.0, Qt::white);
        gradient.setColorAt(0.2, QColor(169, 250, 40));
        gradient.setColorAt(0.8, QColor(170, 252, 45));
        gradient.setColorAt(1.0, QColor(173, 255, 47));

        painter.begin(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(gradient);
        painter.drawRect(QRectF(0.1, 0.1, image.width()-1, image.height()-1));
        painter.setFont(font);
        painter.setBrush(Qt::black);
        painter.drawText(QRect(QPoint(3, 3), size), Qt::AlignCenter, m_labelText);
        painter.end();
    }
    else if(ete == EditionError){
        gradient.setColorAt(0.0, Qt::white);
        gradient.setColorAt(0.2, QColor(245, 120, 10));
        gradient.setColorAt(0.8, QColor(250, 125, 5));
        gradient.setColorAt(1.0, QColor(255, 127, 0));

        painter.begin(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(gradient);
        painter.drawRect(QRectF(0.1, 0.1, image.width()-1, image.height()-1));
        painter.setFont(font);
        painter.setBrush(Qt::black);
        painter.drawText(QRect(QPoint(3, 3), size), Qt::AlignCenter, m_labelText);
        painter.end();
    }
    else if(ete == RecognitionError){
        gradient.setColorAt(0.0, Qt::white);
        gradient.setColorAt(0.2, QColor(245, 240, 5));
        gradient.setColorAt(0.8, QColor(250, 245, 5));
        gradient.setColorAt(1.0, QColor(255, 255, 0));

        painter.begin(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(gradient);
        painter.drawRect(QRectF(0.1, 0.1, image.width()-1, image.height()-1));
        painter.setFont(font);
        painter.setBrush(Qt::black);
        painter.drawText(QRect(QPoint(3, 3), size), Qt::AlignCenter, m_labelText);
        painter.end();

    }
    setPixmap(QPixmap::fromImage(image));
}

EditionTypeEnum DragLabel::getErrorType()
{
    return errorType;
}

void DragLabel::setComment(QString &newComment)
{
    dwcomment->setEditComment(newComment);
}

QString DragLabel::getComment()
{
    return dwcomment->getEditComment();
}

void DragLabel::showCommentEditor()
{
    dwcomment->show();
}

double DragLabel::getErrorWeight()
{
    return errorWeight;
}

void DragLabel::setErrorWeight(double w){
    errorWeight = w;
}


