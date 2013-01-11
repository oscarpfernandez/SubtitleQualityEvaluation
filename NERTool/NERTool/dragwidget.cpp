#include <QtGui>
#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent, QString &textBlock, int maxWidth)  : QWidget(parent)
{
    m_labelsPointerList = new QList<DragLabel *>();
    int x = 5;
    int y = 2;
    m_maxWidgetWidth = maxWidth-70;
    m_counter = 0;
    m_numLines = 0;

	QStringList wordsList = textBlock.split(" ");

	for(int i=0; i<wordsList.count(); i++) {
		QString word = wordsList.at(i);

        if (!word.isEmpty()) {
            DragLabel *wordLabel = new DragLabel(word, this);
            wordLabel->setupLabelType(DragLabel::NotDefinedYet);
            wordLabel->move(x, y);
            wordLabel->show();
            wordLabel->setAttribute(Qt::WA_DeleteOnClose);
            m_labelsPointerList->insert(m_counter++, wordLabel);

            x += wordLabel->width();

            if (x >= m_maxWidgetWidth && i-1<wordsList.count()) {
                x = 5;
                y += wordLabel->height() + 2;
                m_numLines++;
            }
        }
    }

    //White background...
    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);

    //setMinimumSize(400, qMax(200, y));

    //setAcceptDrops(true);
}

void redrawWidgetSizeChangedSlot(int &cellWidth){

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
    if (!child){
        return;
    }

    QPoint hotSpot = event->pos() - child->pos();
    //QPoint hotSpot = event->pos();

    // for most widgets
    QPoint globalPos = child->mapToGlobal(hotSpot);
    // for QAbstractScrollArea and derived classes you would use:
    //QPoint globalPos = this->viewport()->mapToGlobal(hotSpot);

    QMenu myMenu(this);
    myMenu.addAction(CORRECT_EDITION_STR);
    myMenu.addAction(EDITION_ERROR);
    myMenu.addAction(RECOG_ERROR_STR);
    // ...

    QAction* selectedItem = myMenu.exec(globalPos);
    if(selectedItem){
        if (selectedItem->text() == CORRECT_EDITION_STR)
        {
            child->setupLabelType(DragLabel::CorrectEdition);
        }
        else if(selectedItem->text() == EDITION_ERROR)
        {
            child->setupLabelType(DragLabel::EditionError);
        }
        else if(selectedItem->text() == RECOG_ERROR_STR)
        {
            child->setupLabelType(DragLabel::RecognitionError);
        }
    }


//    QByteArray itemData;
//    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//    dataStream << child->labelText() << QPoint(hotSpot);

//    QMimeData *mimeData = new QMimeData;
//    mimeData->setData("application/x-draglabel", itemData);
//    mimeData->setText(child->labelText());

//    QDrag *drag = new QDrag(this);
//    drag->setMimeData(mimeData);
//    drag->setPixmap(*child->pixmap());
//    drag->setHotSpot(hotSpot);

//    child->hide();

//    if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
//        child->close();
//    else
//        child->show();
}

QSize DragWidget::getBlockSize()
{
    int height = 0;
    if(m_labelsPointerList->count()>0){
        DragLabel *labelW;
        labelW = m_labelsPointerList->at(0);
        height = labelW->height();
    }

    return QSize(m_maxWidgetWidth, (m_numLines+1)*height + 10);
}
