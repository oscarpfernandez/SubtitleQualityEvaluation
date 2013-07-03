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
    createActions();

    m_isModifiable = isModifiable;
    m_labelsPointerList = new QList<DragLabel *>();
    int x = 5;
    int y = 2;
    m_maxWidgetWidth = maxWidth;
    m_numLines = 0;

    QStringList wordsList = textBlock.simplified().split(" ");

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


/*******************************************************************************
 * Dragwidget constructor used in NER XML imports
 *
 ******************************************************************************/
DragWidget::DragWidget(QWidget *parent, int maxWidth, bool isModifiable)
    : QWidget(parent)
{
    createActions();

    m_isModifiable = isModifiable;
    m_maxWidgetWidth = maxWidth;

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

void DragWidget::initializeData(QList<DragLabel*> labelList)
{

    m_labelsPointerList = new QList<DragLabel *>();
    int x = 5;
    int y = 2;
    m_numLines = 0;

    for(int i=0; i<labelList.count(); i++) {
        DragLabel* wordLabel = labelList.at(i);
        wordLabel->move(x, y);
        wordLabel->show();
        wordLabel->setAttribute(Qt::WA_DeleteOnClose);

        if (wordLabel != 0) {
            m_labelsPointerList->append(wordLabel);
            x += wordLabel->width()+1;
            if (x >= m_maxWidgetWidth && i-1<labelList.count()) {
                x = 5;
                y += wordLabel->height() + 2;
                m_numLines++;
            }
        }
    }
}

void DragWidget::createActions()
{
    m_editionErrorAction = new QAction(EDITION_ERROR_STR, this);
    m_editionErrorAction->setCheckable(true);
    m_recognitionErrorAction = new QAction(RECOG_ERROR_STR, this);
    m_recognitionErrorAction->setCheckable(true);
    m_noErrorAction = new QAction(CORRECT_EDITION_STR, this);
    m_noErrorAction->setCheckable(true);
    m_Error025Action = new QAction(ERROR_WEIGHT_025_STR, this);
    m_Error025Action->setCheckable(true);
    m_Error050Action = new QAction(ERROR_WEIGHT_05_STR, this);
    m_Error050Action->setCheckable(true);
    m_Error100Action = new QAction(ERROR_WEIGHT_1_STR, this);
    m_Error100Action->setCheckable(true);
    m_Error0Action = new QAction(ERROR_WEIGHT_0_STR, this);
    m_Error0Action->setCheckable(true);

    m_insertionAction = new QAction(INSERTION_STR, this);
    m_insertionAction->setCheckable(true);
    m_substitutionAction = new QAction(SUBSTITUTION_STR, this);
    m_substitutionAction->setCheckable(true);
    m_delectionAction = new QAction(DELETION_STR, this);
    m_delectionAction->setCheckable(true);

    m_commentAction = new QAction(EDITION_COMMENT_STR, this);
    m_commentAction->setCheckable(true);
    m_commentAction->setChecked(false);

}

void DragWidget::uncheckAllErrorActions()
{
    m_editionErrorAction->setChecked(false);
    m_recognitionErrorAction->setChecked(false);
    m_noErrorAction->setChecked(false);
}

void DragWidget::uncheckAllWeightActions()
{
    m_Error025Action->setChecked(false);
    m_Error050Action->setChecked(false);
    m_Error100Action->setChecked(false);
    m_Error0Action->setChecked(false);
}

void DragWidget::uncheckAllTypeActions()
{
    m_insertionAction->setChecked(false);
    m_delectionAction->setChecked(false);
    m_substitutionAction->setChecked(false);
}

/*******************************************************************************
 * Provides the number of words contained in the text block.
 ******************************************************************************/
int DragWidget::countWords()
{
    if(m_labelsPointerList->isEmpty()){
        return 0;
    }

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


void DragWidget::setActionsEnabledForLabel(DragLabel* label)
{
    if(label==0){
        return;
    }

    EditionTypeEnum errorType = label->getErrorType();
    m_noErrorAction->setChecked(errorType==CorrectEdition);
    m_editionErrorAction->setChecked(errorType==EditionError);
    m_recognitionErrorAction->setChecked(errorType==RecognitionError);

    double errorWeight = label->getErrorWeight();
    m_Error025Action->setChecked(errorWeight==ERROR_WEIGHT_025);
    m_Error050Action->setChecked(errorWeight==ERROR_WEIGHT_050);
    m_Error100Action->setChecked(errorWeight==ERROR_WEIGHT_1);
    m_Error0Action->setChecked(errorWeight==ERROR_WEIGHT_0);

    ModificationType modType = label->getErrorClass();
    m_insertionAction->setChecked(modType==Insertion);
    m_delectionAction->setChecked(modType==Deletion);
    m_substitutionAction->setChecked(modType==Substitution);

    m_commentAction->setChecked(!label->getComment().isEmpty());

}

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

        EditionTypeEnum previousType = child->getErrorType();

        QPoint hotSpot = mouseEvent->pos() - child->pos();
        QPoint globalPos = child->mapToGlobal(hotSpot);

        setActionsEnabledForLabel(child);

        QMenu myMenu(this);
        myMenu.addAction(m_noErrorAction);
        myMenu.addAction(m_editionErrorAction);
        myMenu.addAction(m_recognitionErrorAction);
        myMenu.addSeparator();
        myMenu.addAction(m_commentAction);
        myMenu.addSeparator();
        //QMenu subMenu("Weight Error");
        myMenu.addAction(m_Error0Action);
        myMenu.addAction(m_Error025Action);
        myMenu.addAction(m_Error050Action);
        myMenu.addAction(m_Error100Action);
        //QMenu subMenu2("Type");
        myMenu.addSeparator();
        myMenu.addAction(m_insertionAction);
        myMenu.addAction(m_delectionAction);
        myMenu.addAction(m_substitutionAction);
        //myMenu.addMenu(&subMenu);
        //myMenu.addMenu(&subMenu2);

        // ...

        QAction* selectedItem = myMenu.exec(globalPos);
        if(selectedItem){
            if (selectedItem->text() == CORRECT_EDITION_STR)
            {
                uncheckAllErrorActions();
                m_noErrorAction->setChecked(true);
                child->setupLabelType(CorrectEdition);
                child->setErrorWeight(ERROR_WEIGHT_0);
                child->setErrorClass(NotDefined);
                propagateProperties(child, previousType);
            }
            else if(selectedItem->text() == EDITION_ERROR_STR)
            {
                uncheckAllErrorActions();
                m_editionErrorAction->setChecked(true);
                child->setupLabelType(EditionError);
                if(child->getErrorWeight()==ERROR_WEIGHT_0){
                    child->setErrorWeight(ERROR_WEIGHT_025);
                }
                propagateProperties(child, previousType);
            }
            else if(selectedItem->text() == RECOG_ERROR_STR)
            {
                uncheckAllErrorActions();
                m_recognitionErrorAction->setChecked(true);
                child->setupLabelType(RecognitionError);
                if(child->getErrorWeight()==ERROR_WEIGHT_0){
                    child->setErrorWeight(ERROR_WEIGHT_025);
                }
                propagateProperties(child, previousType);
            }
            else if(selectedItem->text() == EDITION_COMMENT_STR){
                //Modify comment used in the report...
                QString comment = child->getComment();
                child->setComment(comment);
                child->showCommentEditor();
            }
            else if(selectedItem->text() == ERROR_WEIGHT_025_STR){
                uncheckAllWeightActions();
                m_Error025Action->setChecked(true);
                child->setErrorWeight(ERROR_WEIGHT_025);
                propagateProperties(child, previousType);
            }
            else if(selectedItem->text() == ERROR_WEIGHT_05_STR){
                uncheckAllWeightActions();
                m_Error050Action->setChecked(true);
                child->setErrorWeight(ERROR_WEIGHT_050);
                propagateProperties(child, previousType);
            }
            else if(selectedItem->text() == ERROR_WEIGHT_1_STR){
                uncheckAllWeightActions();
                m_Error100Action->setChecked(true);
                child->setErrorWeight(ERROR_WEIGHT_1);
                propagateProperties(child, previousType);
            }
            else if(selectedItem->text() == ERROR_WEIGHT_0_STR){
                uncheckAllWeightActions();
                m_Error0Action->setChecked(true);
                child->setErrorWeight(ERROR_WEIGHT_0);
                propagateProperties(child, previousType);
            }
            else if(selectedItem->text() == INSERTION_STR){
                uncheckAllTypeActions();
                child->setErrorClass(Insertion);
                m_insertionAction->setChecked(true);
                propagateModificationProperties(child);
            }
            else if(selectedItem->text() == SUBSTITUTION_STR){
                uncheckAllTypeActions();
                child->setErrorClass(Substitution);
                m_substitutionAction->setChecked(true);
                propagateModificationProperties(child);
            }
            else if(selectedItem->text() == DELETION_STR){
                uncheckAllTypeActions();
                child->setErrorClass(Deletion);
                m_delectionAction->setChecked(true);
                propagateModificationProperties(child);
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


double DragWidget::getEditionErrors(NERStatsData &nerStats)
{
    double globalErrorValue = 0;

    EditionTypeEnum lastErrorType = NotDefinedYet;

    for(int i=0; i<m_labelsPointerList->count(); ++i){
        DragLabel *labelW = m_labelsPointerList->at(i);

        EditionTypeEnum errorType = labelW->getErrorType();

        if(errorType == EditionError){

            if(errorType != lastErrorType || i==0){
                double weight = labelW->getErrorWeight();
                globalErrorValue += weight;

                //Save wichweight type
                if(weight == ERROR_WEIGHT_0){
                    nerStats.incEditionErrors_w000();
                }
                else if(weight == ERROR_WEIGHT_025){
                    nerStats.incEditionErrors_w025();
                }
                else if(weight == ERROR_WEIGHT_050){
                    nerStats.incEditionErrors_w050();
                }
                else if(weight == ERROR_WEIGHT_1){
                    nerStats.incEditionErrors_w100();
                }
            }
        }

        lastErrorType = errorType;
    }

    return globalErrorValue;
}

double DragWidget::getRecognitionErrors(NERStatsData &nerStats)
{
    double globalErrorValue = 0;

    EditionTypeEnum lastErrorType(NotDefinedYet);
    EditionTypeEnum errorType;

    for(int i=0; i<m_labelsPointerList->count(); ++i){
        DragLabel *labelW = m_labelsPointerList->at(i);

         errorType = labelW->getErrorType();

        if(errorType == RecognitionError){

            if(errorType != lastErrorType || i==0){
                double weight = labelW->getErrorWeight();
                globalErrorValue += labelW->getErrorWeight();

                //Save wichweight type
                if(weight == ERROR_WEIGHT_0){
                    nerStats.incRecognitionErrors_w000();
                }
                else if(weight == ERROR_WEIGHT_025){
                    nerStats.incRecognitionErrors_w025();
                }
                else if(weight == ERROR_WEIGHT_050){
                    nerStats.incRecognitionErrors_w050();
                }
                else if(weight == ERROR_WEIGHT_1){
                    nerStats.incRecognitionErrors_w100();
                }
            }
        }

        lastErrorType = errorType;
    }

    return globalErrorValue;
}

double DragWidget::getInsertions(NERStatsData &nerStats)
{
    double globalInsertions = 0;

    ModificationType lastModification(NotDefined);
    ModificationType modificationType;

    for(int i=0; i<m_labelsPointerList->count(); ++i){
        DragLabel *labelW = m_labelsPointerList->at(i);

         modificationType = labelW->getErrorClass();

        if(modificationType == Insertion){

            if(modificationType != lastModification || i==0){
                if(labelW->getErrorType()==EditionError){
                    nerStats.incEdErrorInsertions();
                    globalInsertions +=nerStats.getEdErrorInsertions();
                }
                else if(labelW->getErrorType()==RecognitionError){
                    nerStats.incRecogErrorInsertions();
                    globalInsertions +=nerStats.getRecogErrorInsertions();
                }
            }
        }

        lastModification = modificationType;
    }

    return globalInsertions;
}

double DragWidget::getDeletions(NERStatsData &nerStats)
{
    double globalInsertions = 0;

    ModificationType lastModification(NotDefined);
    ModificationType modificationType;

    for(int i=0; i<m_labelsPointerList->count(); ++i){
        DragLabel *labelW = m_labelsPointerList->at(i);

         modificationType = labelW->getErrorClass();

        if(modificationType == Deletion){

            if(modificationType != lastModification || i==0){
                if(labelW->getErrorType()==EditionError){
                    nerStats.incEdErrorDeletions();
                    globalInsertions +=nerStats.getEdErrorDeletions();
                }
                else if(labelW->getErrorType()==RecognitionError){
                    nerStats.incRecogErrorDeletions();
                    globalInsertions +=nerStats.getRecogErrorDeletions();
                }
            }
        }

        lastModification = modificationType;
    }

    return globalInsertions;
}

double DragWidget::getSubstitutions(NERStatsData &nerStats)
{
    double globalSubstitutions = 0;

    ModificationType lastModification(NotDefined);
    ModificationType modificationType;

    for(int i=0; i<m_labelsPointerList->count(); ++i){
        DragLabel *labelW = m_labelsPointerList->at(i);

         modificationType = labelW->getErrorClass();

        if(modificationType == Substitution){

            if(modificationType != lastModification || i==0){
                if(labelW->getErrorType()==EditionError){
                    nerStats.incEdErrorSubstitutions();
                    globalSubstitutions +=nerStats.getEdErrorSubstitutions();
                }
                else if(labelW->getErrorType()==RecognitionError){
                    nerStats.incRecogErrorSubstitutions();
                    globalSubstitutions +=nerStats.getRecogErrorSubstitutions();
                }
            }
        }

        lastModification = modificationType;
    }

    return globalSubstitutions;
}

/*******************************************************************************
 * Propagates properties across neighbour labels with the same EditionType error.
 * like the weight and comment.
 ******************************************************************************/
void DragWidget::propagateProperties(DragLabel* label, EditionTypeEnum previousType)
{
    if(label==0){
        return;
    }
    int index = m_labelsPointerList->indexOf(label);

    EditionTypeEnum errorType = label->getErrorType();

    //propagate to the right...
    if(index+1 < m_labelsPointerList->count()){
        for(int i=index+1; i<m_labelsPointerList->count(); i++){
            DragLabel* neighLab = m_labelsPointerList->at(i);
            if(previousType==TrancriptionDeletion && previousType==neighLab->getErrorType()){
                //Transcription case... propagate the labels type...
                neighLab->setupLabelType(label->getErrorType());
                neighLab->setErrorWeight(label->getErrorWeight());
                QString s(label->getComment());
                neighLab->setComment(s);
            }

            else if(neighLab->getErrorType() != label->getErrorType()
                    || (neighLab->getErrorType()!=TrancriptionDeletion && previousType==TrancriptionDeletion))
            {
                //neighbour is different
                break;
            }
            neighLab->setErrorWeight(label->getErrorWeight());
            QString s(label->getComment());
        }
    }

    //propagate to left
    if(index-1 > 0){
        for(int i=index-1; i>=0; i--){
            DragLabel* neighLab = m_labelsPointerList->at(i);

            if(previousType==TrancriptionDeletion && previousType==neighLab->getErrorType()){
                //Transcription case... propagate the labels type...
                neighLab->setupLabelType(label->getErrorType());
                neighLab->setErrorWeight(label->getErrorWeight());
                QString s(label->getComment());
                neighLab->setComment(s);
            }
            else if(neighLab->getErrorType() != label->getErrorType() ||
                    (neighLab->getErrorType()!=TrancriptionDeletion && previousType==TrancriptionDeletion))
            {
                //neighbour is different
                break;
            }
            neighLab->setErrorWeight(label->getErrorWeight());
            QString s(label->getComment());
        }
    }
}

void DragWidget::propagateModificationProperties(DragLabel* label)
{
    if(label==0){
        return;
    }
    int index = m_labelsPointerList->indexOf(label);

    //propagate to the right...
    if(index+1 < m_labelsPointerList->count()){
        for(int i=index+1; i<m_labelsPointerList->count(); i++){
            DragLabel* neighLab = m_labelsPointerList->at(i);
            if(neighLab->getErrorType() != label->getErrorType()){
                //neighbour is different
                break;
            }
            neighLab->setErrorClass(label->getErrorClass());
        }
    }

    //propagate to left
    if(index-1 > 0){
        for(int i=index-1; i>=0; i--){
            DragLabel* neighLab = m_labelsPointerList->at(i);
            if(neighLab->getErrorType() != label->getErrorType()){
                //neighbour is different
                break;
            }
            neighLab->setErrorClass(label->getErrorClass());
        }
    }
}

QList<DragLabel*> DragWidget::getLabels()
{
    return *m_labelsPointerList;
}

