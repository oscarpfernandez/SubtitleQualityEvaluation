#include <QtGui>
#include "draglabel.h"
#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent, QString &textBlock)  : QWidget(parent)
{
    //QFile dictionaryFile(":/dictionary/words.txt");
    //dictionaryFile.open(QFile::ReadOnly);
    //QTextStream inputStream(&dictionaryFile);
    int x = 2;
    int y = 2;

	QStringList wordsList = textBlock.split(" ");

	for(int i=0; i<wordsList.count(); i++) {
		QString word = wordsList.at(i);

        if (!word.isEmpty()) {
            DragLabel *wordLabel = new DragLabel(word, this);
            wordLabel->move(x, y);
            wordLabel->show();
            wordLabel->setAttribute(Qt::WA_DeleteOnClose);
            x += wordLabel->width() -1/*+ 2*/;

            if (x >= 245) {
                x = 5;
                y += wordLabel->height() + 2;
            }
        }
    }

    //White background...
    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);

    setMinimumSize(400, qMax(200, y));
    setWindowTitle(tr("Fridge Magnets"));

    setAcceptDrops(true);
}

//void DragWidget::dragEnterEvent(QDragEnterEvent *event)
//{
//    if (event->mimeData()->hasFormat("application/x-draglabel")) {
//        if (children().contains(event->source())) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else if (event->mimeData()->hasText()) {
//        event->acceptProposedAction();
//    } else {
//        event->ignore();
//    }
//}

//void DragWidget::dragMoveEvent(QDragMoveEvent *event)
//{
//    if (event->mimeData()->hasFormat("application/x-draglabel")) {
//        if (children().contains(event->source())) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else if (event->mimeData()->hasText()) {
//        event->acceptProposedAction();
//    } else {
//        event->ignore();
//    }
//}
//
//void DragWidget::dropEvent(QDropEvent *event)
//{
//    if (event->mimeData()->hasFormat("application/x-draglabel")) {
//        const QMimeData *mime = event->mimeData();
//
//        QByteArray itemData = mime->data("application/x-draglabel");
//        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
//
//        QString text;
//        QPoint offset;
//        dataStream >> text >> offset;
//
//        DragLabel *newLabel = new DragLabel(text, this);
//        newLabel->move(event->pos() - offset);
//        newLabel->show();
//        newLabel->setAttribute(Qt::WA_DeleteOnClose);
//
//        if (event->source() == this) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//
//    } else if (event->mimeData()->hasText()) {
//        QStringList pieces = event->mimeData()->text().split(QRegExp("\\s+"),
//                                                             QString::SkipEmptyParts);
//        QPoint position = event->pos();
//
//        foreach (QString piece, pieces) {
//            DragLabel *newLabel = new DragLabel(piece, this);
//            newLabel->move(position);
//            newLabel->show();
//            newLabel->setAttribute(Qt::WA_DeleteOnClose);
//
//            position += QPoint(newLabel->width(), 0);
//        }
//
//        event->acceptProposedAction();
//    } else {
//        event->ignore();
//    }
//}

void DragWidget::mousePressEvent(QMouseEvent *event)
{

    DragLabel *child = static_cast<DragLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPoint hotSpot = event->pos() - child->pos();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << child->labelText() << QPoint(hotSpot);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-draglabel", itemData);
    mimeData->setText(child->labelText());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(*child->pixmap());
    drag->setHotSpot(hotSpot);

    child->hide();

    if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
        child->close();
    else
        child->show();
}
