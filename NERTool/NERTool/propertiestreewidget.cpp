#include "propertiestreewidget.h"

PropertiesTreeWidget::PropertiesTreeWidget(QWidget *parent) : QWidget(parent)
{
    mainVLayout = new QVBoxLayout();
    mainTreeWidget = new QTreeWidget(parent);
    mainTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    mainTreeWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
    mainTreeWidget->installEventFilter(this);

    //REview!!
//    connect(mainTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
//            this, SLOT(onTreeWidgetItemDoubleClicked(QTreeWidgetItem*,int)));

    mainItemTrans = new QTreeWidgetItem();
    mainItemTrans->setText(0, QString("Transcription"));
    mainItemTrans->setIcon(0, QIcon(":/resources/pics/docs.png"));
    mainItemSubs = new QTreeWidgetItem();
    mainItemSubs->setIcon(0, QIcon(":/resources/pics/docs.png"));
    mainItemSubs->setText(0, QString("Subtitles"));

    nerPropsTreeWidget = new QTreeWidget(parent);
    splitter = new QSplitter(Qt::Vertical, parent);

    mainTreeGroupBox = new QGroupBox(QString("Loaded Files"), this);
    mainTreeGroupBoxLayout = new QVBoxLayout();
    nerPropsGroupBox = new QGroupBox(QString("NER Properties"), this);
    nerPropsGroupBoxLayout = new QVBoxLayout();

    //Set tree header
    QTreeWidgetItem* headerItem = new QTreeWidgetItem();
    headerItem->setText(0,QString("File Name"));
    headerItem->setText(1,QString("Responsible"));
    headerItem->setText(2,QString("Description"));
    mainTreeWidget->setHeaderItem(headerItem);

    mainTreeGroupBoxLayout->addWidget(mainTreeWidget);
    mainTreeGroupBox->setLayout(mainTreeGroupBoxLayout);

    QTreeWidgetItem* headerNerProps = new QTreeWidgetItem();
    headerNerProps->setText(0,QString("Properties"));
    headerNerProps->setText(1,QString("Value"));
    nerPropsTreeWidget->setHeaderItem(headerNerProps);

    nerPropsGroupBoxLayout->addWidget(nerPropsTreeWidget);
    nerPropsGroupBox->setLayout(nerPropsGroupBoxLayout);

    splitter->addWidget(mainTreeGroupBox);
    splitter->addWidget(nerPropsGroupBox);

    mainVLayout->addWidget(splitter);

    setLayout(mainVLayout);
    setWindowIcon(QIcon(":/resources/pics/docs.png"));


    initContextMenuAction();
    initTrees();

    QString f = QString("Filename");
    QString n = QString("REposnsible");
    QString d = QString("Description");
    insertNewSubtitle(f, n, d);

}

//void PropertiesTreeWidget::onTreeWidgetItemDoubleClicked(QTreeWidgetItem * item, int column)
//{
//    if (column != 0) {
//        //Allow editiong all expect the filename...
//        qDebug("Item Edited");
//        mainTreeWidget->editItem(item, column);
//    }
//}

/*******************************************************************************
 * Initializes the root nodes of the properties tree.
 ******************************************************************************/
void PropertiesTreeWidget::initTrees(){
    mainTreeWidget->addTopLevelItem(mainItemTrans);
    mainTreeWidget->addTopLevelItem(mainItemSubs);
}

void PropertiesTreeWidget::initContextMenuAction()
{
    openSubAction = new QAction(QIcon(), QString("Open"), this);
    connect(openSubAction, SIGNAL(triggered()), this, SLOT(openSubDocumentNodeSlot()));

    removeSubAction = new QAction(QIcon(), QString("Edit Properties..."), this);
    connect(removeSubAction, SIGNAL(triggered()), this, SLOT(removeSubNodeSlot()));

    editSubPropertiesAction = new QAction(QIcon(), QString("Remove..."), this);
    connect(editSubPropertiesAction, SIGNAL(triggered()), this, SLOT(editSubPropertiesNode()));

}


/*******************************************************************************
 * Inserts a new subtitle document on the tree.
 ******************************************************************************/
void PropertiesTreeWidget::insertNewSubtitle(QString &fileName,
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

    mainItemTrans->addChild(item);
}

void PropertiesTreeWidget::insertNewSpeaker(QString &speaker)
{

}

/*******************************************************************************
 * Event filter to customize action ,like context menu, etc...
 ******************************************************************************/
bool PropertiesTreeWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::ContextMenu)
    {
        QList<QTreeWidgetItem*> itemList = mainTreeWidget->selectedItems();
        QTreeWidgetItem* item = itemList.at(0);
        if(item->parent()==NULL){
            //If the node is top level (==NULL), don't enable context menu
            return true;
        }

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        QMenu *menu = new QMenu(this);

        menu->addAction(new QAction("Open content",this));
        menu->addAction(new QAction("Edit properties...",this));
        menu->addSeparator();
        menu->addAction(new QAction("Remove",this));
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
void PropertiesTreeWidget::openSubDocumentNodeSlot()
{

}

void PropertiesTreeWidget::editSubPropertiesNode(){

}

void PropertiesTreeWidget::removeSubNodeSlot(){

}
