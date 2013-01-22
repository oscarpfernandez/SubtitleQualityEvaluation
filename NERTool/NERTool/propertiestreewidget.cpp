#include "propertiestreewidget.h"

PropertiesTreeWidget::PropertiesTreeWidget(QWidget *parent) : QWidget(parent)
{
    mainVLayout = new QVBoxLayout(parent);
    mainTreeWidget = new QTreeWidget(parent);

    //REview!!
    connect(mainTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onTreeWidgetItemDoubleClicked(QTreeWidgetItem*,int)));

    mainItemTrans = new QTreeWidgetItem();
    mainItemTrans->setText(0, QString("Translation"));
    mainItemTrans->setIcon(0, QIcon(":/resources/pics/docs.png"));
    mainItemSubs = new QTreeWidgetItem();
    mainItemSubs->setIcon(0, QIcon(":/resources/pics/docs.png"));
    mainItemSubs->setText(0, QString("Subtitles"));

    nerPropsTreeWidget = new QTreeWidget(parent);
    splitter = new QSplitter(Qt::Vertical, parent);

    mainTreeGroupBox = new QGroupBox(QString("Loaded Files"), this);
    mainTreeGroupBoxLayout = new QVBoxLayout(this);
    nerPropsGroupBox = new QGroupBox(QString("NER Properties"), this);
    nerPropsGroupBoxLayout = new QVBoxLayout(this);

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

    insertNewSubtitle(QString("Filename"), QString("REposnsible"), QString("Description"));

}

void PropertiesTreeWidget::onTreeWidgetItemDoubleClicked(QTreeWidgetItem * item, int column)
{
    if (column != 0) {
        //Allow editiong all expect the filename...
        qDebug("Item Edited");
        mainTreeWidget->editItem(item, column);
    }
}

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

    //Set the tree context menu
    mainTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    mainTreeWidget->addAction(openSubAction);
    mainTreeWidget->addAction(editSubPropertiesAction);
    mainTreeWidget->addAction(removeSubAction);

}

void PropertiesTreeWidget::openSubDocumentNodeSlot()
{

}

void PropertiesTreeWidget::editSubPropertiesNode(){

}

void PropertiesTreeWidget::removeSubNodeSlot(){

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
//bool PropertiesTreeWidget::eventFilter(QObject *obj, QEvent *event)
//{
//    if(event->type() == QEvent::ContextMenu)
//    {
//        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
//        QMenu *menu = new QMenu(this);

//        menu->addAction(new QAction("Open",this));
//        menu->addAction(new QAction("Edit...",this));
//        menu->addSeparator();
//        menu->addAction(new QAction("Delete",this));
//        menu->exec(mouseEvent->globalPos());

//        return false;
//    }
//    else
//        return QListWidget::eventFilter(obj, event);
//}
