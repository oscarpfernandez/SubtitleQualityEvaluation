#include "propertiestreewidget.h"

PropertiesTreeWidget::PropertiesTreeWidget(QWidget *parent) : QWidget(parent)
{
    mainVLayout = new QVBoxLayout(parent);
    mainTreeWidget = new QTreeWidget(parent);

    //Set tree header
    QTreeWidgetItem* headerItem = new QTreeWidgetItem();
    headerItem->setText(0,QString("File Name"));
    headerItem->setText(1,QString("Responsible"));
    mainTreeWidget->setHeaderItem(headerItem);

    mainVLayout->addWidget(mainTreeWidget);

    setLayout(mainVLayout);

}

void PropertiesTreeWidget::insertNewNerTable(QString &name)
{

}

void PropertiesTreeWidget::insertNewSpeaker(QString &speaker)
{

}
