#include "propertiestreewidget.h"

/*******************************************************************************
 * This classes mananges the properties tree widget reporting the files loaded
 * both of the translation and subtitles.
 ******************************************************************************/

PropertiesTreeWidget::PropertiesTreeWidget(QWidget *parent) : QWidget(parent)
{
    subWindowsMap = new QMap<QTreeWidgetItem*, QMdiSubWindow*>();

    mainVLayout = new QVBoxLayout();
    mainTreeWidget = new QTreeWidget(parent);
    mainTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    mainTreeWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
    mainTreeWidget->installEventFilter(this);

    //REview!!
    connect(mainTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
            this, SLOT(renameDocumentNodeSlot(QTreeWidgetItem*,int)));

    mainItemTrans = new QTreeWidgetItem();
    mainItemTrans->setText(0, QString("Transcription"));
    mainItemTrans->setIcon(0, QIcon(":/resources/pics/docs.png"));
    mainItemTrans->setExpanded(true);
    mainItemSubs = new QTreeWidgetItem();
    mainItemSubs->setIcon(0, QIcon(":/resources/pics/docs.png"));
    mainItemSubs->setText(0, QString("Subtitles"));
    mainItemSubs->setExpanded(true);

    mainTreeGroupBox = new QGroupBox(QString("Loaded Files"), this);
    mainTreeGroupBoxLayout = new QVBoxLayout();


    //Set tree header
    QTreeWidgetItem* headerItem = new QTreeWidgetItem();
    headerItem->setText(0,QString("Name"));
    headerItem->setText(1,QString("Responsible"));
    headerItem->setText(2,QString("Description"));
    mainTreeWidget->setHeaderItem(headerItem);
    mainTreeWidget->setColumnWidth(0,250);
    mainTreeWidget->setColumnWidth(1,150);
    mainTreeWidget->setColumnWidth(2,150);

    mainTreeWidget->setSortingEnabled(true);

    mainTreeGroupBoxLayout->addWidget(mainTreeWidget);
    mainTreeGroupBox->setLayout(mainTreeGroupBoxLayout);

    mainVLayout->addWidget(mainTreeGroupBox);

    setLayout(mainVLayout);
    setWindowIcon(QIcon(":/resources/pics/docs.png"));

    createActions();
    initTrees();

}

void PropertiesTreeWidget::onTreeWidgetItemDoubleClicked(QTreeWidgetItem * item, int column)
{
    if(subWindowsMap->contains(item)){
        QMdiSubWindow *subwindow = subWindowsMap->value(item);
        subwindow->showMaximized();
    }

}

/*******************************************************************************
 * Initializes the root nodes of the properties tree.
 ******************************************************************************/
void PropertiesTreeWidget::initTrees(){
    mainTreeWidget->addTopLevelItem(mainItemTrans);
    mainTreeWidget->addTopLevelItem(mainItemSubs);
}

void PropertiesTreeWidget::createActions()
{
    openSubtitleAction = new QAction(tr("Show table"), this);
    connect(openSubtitleAction, SIGNAL(triggered()), this, SLOT(openSubtitleWindowSlot()));

    removeFileAction = new QAction(tr("Remove..."), this);
    connect(removeFileAction, SIGNAL(triggered()), this, SLOT(removeSubNodeSlot()));

    addAssessmentAction = new QAction(tr("Edit Assessment"), this);
    connect(addAssessmentAction, SIGNAL(triggered()), this, SLOT(addAssessmentSlot()));
}


/*******************************************************************************
 * Inserts a new subtitle document on the tree.
 ******************************************************************************/
QTreeWidgetItem* PropertiesTreeWidget::insertNewSubtitle(QString &fileName,
                                                         QMdiSubWindow *subWindow,
                                                         QString &responsible,
                                                         QString &description)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setFlags(item->flags()
                   | Qt::ItemIsSelectable
                   | Qt::ItemIsEnabled
                   | Qt::ItemIsEditable);
    item->setText(0, fileName);
    item->setText(1,responsible);
    item->setText(2,description);
    item->setIcon(0,QIcon(":/resources/pics/doc_subs.png"));

    mainItemSubs->addChild(item);
    mainTreeWidget->expandAll();

    subWindowsMap->insert(item, subWindow);

    return item;
}

/*******************************************************************************
 * Insert a new transklation item in  the translastions item.
 ******************************************************************************/
void PropertiesTreeWidget::insertNewTranslation(QString &fileName,
                                                QString &responsible,
                                                QString &description)
{
    if(mainItemTrans->childCount()!=0){
        mainItemTrans->removeChild(mainItemTrans->child(0));
    }

    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setFlags(item->flags()
                   | Qt::ItemIsSelectable
                   | Qt::ItemIsEnabled
                   | Qt::ItemIsEditable);
    item->setText(0, fileName);
    item->setText(1, responsible);
    item->setText(2, description);
    item->setIcon(0, QIcon(":/resources/pics/doc_subs.png"));

    mainItemTrans->addChild(item);
    mainTreeWidget->expandAll();

}

/*******************************************************************************
 * Remove all the tree data.
 ******************************************************************************/
void PropertiesTreeWidget::clearAllTreeData()
{
    //Remove all childs from both trees..
    qDeleteAll(mainItemSubs->takeChildren());
    qDeleteAll(mainItemTrans->takeChildren());
}

/*******************************************************************************
 * Event filter to customize action ,like context menu, etc...
 ******************************************************************************/
bool PropertiesTreeWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::ContextMenu)
    {
        //Disable context menu for main nodes AND translation node...
        QList<QTreeWidgetItem*> itemList = mainTreeWidget->selectedItems();
        QTreeWidgetItem* item = itemList.at(0);

        if(mainItemTrans->childCount()>0){
            QTreeWidgetItem* itemC = mainItemTrans->child(0);
            if(itemC == item){
                //disable...
                return true;
            }
        }


        if(item->parent()==NULL){
            //If the node is top level (==NULL), don't enable context menu
            return true;
        }

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        QMenu *menu = new QMenu(this);

        menu->addAction(openSubtitleAction);
        menu->addSeparator();
        menu->addAction(removeFileAction);
        menu->addSeparator();
        menu->addAction(addAssessmentAction);
        menu->exec(mouseEvent->globalPos());

        return false;
    }
    else {
        return QWidget::eventFilter(obj, event);
    }
}

/*******************************************************************************
 * Context Menu actions for the tree items.
 ******************************************************************************/
void PropertiesTreeWidget::openSubtitleWindowSlot()
{
    QList<QTreeWidgetItem*> itemList = mainTreeWidget->selectedItems();
    QTreeWidgetItem* item = itemList.at(0);
    if(item!=NULL && subWindowsMap->contains(item)){
        QMdiSubWindow *subwindow = subWindowsMap->value(item);
        subwindow->showMaximized();
    }
}

void PropertiesTreeWidget::renameDocumentNodeSlot(QTreeWidgetItem* item, int column)
{
    if(item!=NULL && column==0){
        QMdiSubWindow *subwindow = subWindowsMap->value(item);
        if(subwindow!=NULL){
            subwindow->setWindowTitle(item->text(0));
        }
    }

}

/*******************************************************************************
 * Key listener method overriden to monitor keys.
 ******************************************************************************/
void PropertiesTreeWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        QList<QTreeWidgetItem*> itemList = mainTreeWidget->selectedItems();
        QTreeWidgetItem* item = itemList.at(0);
        if(item!=NULL && subWindowsMap->contains(item)){
            QMdiSubWindow *subwindow = subWindowsMap->value(item);
            subwindow->showMaximized();
        }
    }
}

void PropertiesTreeWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {

    }
}

/*******************************************************************************
 * Remove Subtitle file node from the tree AND the table data.
 ******************************************************************************/
void PropertiesTreeWidget::removeSubNodeSlot()
{
    QList<QTreeWidgetItem*> itemList = mainTreeWidget->selectedItems();
    QTreeWidgetItem* item = itemList.at(0);
    QMdiSubWindow *subwindow = subWindowsMap->value(item);

    QMessageBox box;
    QString text;
    text.append("Delete table ")
            .append("\"")
            .append(subwindow->windowTitle())
            .append("\" ?");
    box.setText(text);
    box.setInformativeText("After deletion the data is NOT recoverable.");
    box.setBaseSize(150,60);
    box.setIcon(QMessageBox::Warning);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);
    int ret = box.exec();
    switch (ret) {
    case QMessageBox::No:
        return;//Get out of here!!!...Deletion aborted!
    default:
        // should never be reached
        break;
    }


    if(item!=NULL && subWindowsMap->contains(item)){
        QMdiSubWindow *subwindow = subWindowsMap->value(item);
        NERTableWidget *table = static_cast<NERTableWidget*>(subwindow->widget());
        subwindow->close();
        subWindowsMap->remove(item);
        table->close();
        mainItemSubs->removeChild(item);
    }

    subWindowsMap->remove(item);
}

/*******************************************************************************
 * Adds an assessment evaluation to the selected subtitle evaluation
 ******************************************************************************/
void PropertiesTreeWidget::addAssessmentSlot()
{
    QList<QTreeWidgetItem*> itemList = mainTreeWidget->selectedItems();
    QTreeWidgetItem* item = itemList.at(0);

    if(item!=NULL && subWindowsMap->contains(item)){
        QMdiSubWindow *subwindow = subWindowsMap->value(item);
        NERTableWidget *table = static_cast<NERTableWidget*>(subwindow->widget());

        if(table != 0){
            table->showAssessment();
        }
    }
}

void PropertiesTreeWidget::removeAllSubNodes()
{
    QList<QTreeWidgetItem*> nodes = subWindowsMap->keys();

    for(int i=0; i<nodes.count();i++){
        QTreeWidgetItem *item = nodes.at(i);
        QMdiSubWindow *subwindow = subWindowsMap->value(item);
        subwindow->close();
        subWindowsMap->remove(item);
        mainItemSubs->removeChild(item);
    }

}

QMap<QTreeWidgetItem*, QMdiSubWindow*>* PropertiesTreeWidget::getTreeSubWindowsMap()
{
    return subWindowsMap;
}

QTreeWidgetItem* PropertiesTreeWidget::getTranslationNode()
{
    if(mainItemTrans->childCount()==0){
        return NULL;
    }
    return mainItemTrans->child(0);
}


void PropertiesTreeWidget::computeNERValuesSlot()
{
    emit computeNERValues();
}

void PropertiesTreeWidget::viewStatsSlot()
{
    emit viewNerStats();
}

void PropertiesTreeWidget::setNERStatistics(double &delay, double &ner)
{

//    nerValueLabel->setText(QString::number(ner));
//    nerPropos_N_value_Label->setText(QString::number(delay));

//    int sum = EdErrors + RecogErrors + correctEds;

//    int re = 0;
//    int er = 0;
//    int ce = 0;

//    if(sum!=0){
//        re = RecogErrors / sum;
//        er = EdErrors / sum;
//        ce = correctEds / sum;
//    }

//    nerPropos_RE_value_Progress->setValue((int)re);
//    nerPropos_ER_value_Progress->setValue((int)er);
//    nerPropos_CE_value_Progress->setValue((int)ce);
}
