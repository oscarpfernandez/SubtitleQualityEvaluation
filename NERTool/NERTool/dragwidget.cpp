#include <QtGui>
#include "dragwidget.h"


/*******************************************************************************
 * This class manages the several words of a sentence, allowing to mark and
 * individual text token with a specific error type, and associate with it with
 * a comment.
 ******************************************************************************/
DragWidget::DragWidget(QWidget *parent,
                       QString &textBlock,
                       int maxWidth,
                       bool isModifiable)  : QWidget(parent)
{
    m_isModifiable = isModifiable;
    m_labelsPointerList = new QList<DragLabel *>();
    int x = 5;
    int y = 2;
    m_maxWidgetWidth = maxWidth;
    m_numLines = 0;

	QStringList wordsList = textBlock.split(" ");

	for(int i=0; i<wordsList.count(); i++) {
		QString word = wordsList.at(i);

        if (!word.isEmpty()) {
            DragLabel *wordLabel = new DragLabel(word, this);
            wordLabel->setupLabelType(NotDefinedYet);
            wordLabel->move(x, y);
            wordLabel->show();
            wordLabel->setAttribute(Qt::WA_DeleteOnClose);
            m_labelsPointerList->append(wordLabel);

            x += wordLabel->width()+1;

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

    setContextMenuPolicy(Qt::DefaultContextMenu);
    installEventFilter(this);
}

DragWidget::~DragWidget()
{

}

/*******************************************************************************
 * Provides the number of words contained in the text block.
 ******************************************************************************/
int DragWidget::countWords()
{
    if(m_labelsPointerList->isEmpty()){
        return 0;
    }

//    int c =  m_labelsPointerList->count();
//    qDebug() << "Number of words -> "<< c;

    return m_labelsPointerList->count();
}

/*******************************************************************************
 * Provides a word at a specific position from the word set.
 * If the index it out of bounds, NULL pointer is returned.
 ******************************************************************************/
DragLabel* DragWidget::getWordAt(int pos)
{
    if(pos >= countWords()){
        return 0;
    }

    return m_labelsPointerList->at(pos);
}

/*******************************************************************************
 * Provides the full text contained in the widget.
 ******************************************************************************/
QString DragWidget::getText()
{
    QString ret;
    for(int i=0; i<m_labelsPointerList->count(); i++){
        DragLabel *w = m_labelsPointerList->at(i);
        ret.append(w->labelText()).append(" ");
    }

    return ret;

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

/*******************************************************************************
 * QEvent filter for managing context menu call over the drag widget to change
 * the error status.
 ******************************************************************************/
bool DragWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(!m_isModifiable){
        //disable context menu...
        return false;
    }

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);

    if(mouseEvent->type() == QEvent::ContextMenu){

        DragLabel *child = static_cast<DragLabel*>(childAt(mouseEvent->pos()));
        if (!child){
            return false;
        }

        QPoint hotSpot = mouseEvent->pos() - child->pos();
        //QPoint hotSpot = event->pos();

        // for most widgets
        QPoint globalPos = child->mapToGlobal(hotSpot);
        // for QAbstractScrollArea and derived classes you would use:
        //QPoint globalPos = this->viewport()->mapToGlobal(hotSpot);

        QMenu myMenu(this);
        myMenu.addAction(CORRECT_EDITION_STR);
        myMenu.addAction(EDITION_ERROR);
        myMenu.addAction(RECOG_ERROR_STR);
        myMenu.addSeparator();
        myMenu.addAction(EDITION_COMMENT);
        // ...

        QAction* selectedItem = myMenu.exec(globalPos);
        if(selectedItem){
            if (selectedItem->text() == CORRECT_EDITION_STR)
            {
                child->setupLabelType(CorrectEdition);
            }
            else if(selectedItem->text() == EDITION_ERROR)
            {
                child->setupLabelType(EditionError);
            }
            else if(selectedItem->text() == RECOG_ERROR_STR)
            {
                child->setupLabelType(RecognitionError);
            }
            else if(selectedItem->text() == EDITION_COMMENT){
                //Modify comment used in the report...
                QString comment = child->getComment();
                child->setComment(comment);
                child->showCommentEditor();
            }
        }
        return true;
    }
    else {
        return QWidget::eventFilter(obj, event);
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

/*******************************************************************************
 * Returns the size of the widget.
 ******************************************************************************/
QSize DragWidget::getBlockSize()
{
    int height = 0;
    if(m_labelsPointerList->count()>0){
        DragLabel *labelW;
        labelW = m_labelsPointerList->at(0);
        height = labelW->height();
    }

    return QSize(m_maxWidgetWidth+40, (m_numLines+1)*height + 10);
}


double DragWidget::getEditionErrors()
{
    double globalErrorValue = 0;
    double partialErrorValue = 0;

    EditionTypeEnum lastErrorType = NotDefinedYet;

    for(int i=0; i<m_labelsPointerList->count(); ++i){
        DragLabel *labelW = m_labelsPointerList->at(i);

        EditionTypeEnum errorType = labelW->getErrorType();

        if(errorType == EditionError){

            if(errorType != lastErrorType){
                globalErrorValue += partialErrorValue;
                partialErrorValue = labelW->getErrorWeight();
            }
        }

        lastErrorType = errorType;
    }

    return globalErrorValue;
}

double DragWidget::getRecognitionErrors()
{
    double globalErrorValue = 0;
    double partialErrorValue = 0;

    EditionTypeEnum lastErrorType(NotDefinedYet);
    EditionTypeEnum errorType;

    for(int i=0; i<m_labelsPointerList->count(); ++i){
        DragLabel *labelW = m_labelsPointerList->at(i);

         errorType = labelW->getErrorType();

        if(errorType == RecognitionError){

            if(errorType != lastErrorType){
                globalErrorValue += partialErrorValue;
                partialErrorValue = labelW->getErrorWeight();
            }
        }

        lastErrorType = errorType;
    }

    return globalErrorValue;
}

