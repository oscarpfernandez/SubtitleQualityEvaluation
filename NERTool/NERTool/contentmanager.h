#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include <QObject>
#include <QTreeWidgetItem>
#include "nertablewidget.h"

    #ifndef NER_PACK_ITEM
    #define NER_PACK_ITEM

    struct NerPackItem
    {
    private:
        QString name;
        QString responsible;
        QString description;
        QList<BlockTRS> *trsTable;
        QTreeWidgetItem *treeNode;
        NERTableWidget  *table;
    public:
        QString getName(){return name;}
        QString getResponsible(){ return responsible;}
        QString getDescription(){ return description;}
        QList<BlockTRS>* getTRSBlock(){ return trsTable;}
        QTreeWidgetItem* getTreeNode(){ return treeNode;}
        NERTableWidget*  getTable(){ return table;}
    };

    #endif

class ContentManager : public QObject
{
    Q_OBJECT
public:
    explicit ContentManager(QObject *parent = 0);
    ~ContentManager();

private:


};

#endif // CONTENTMANAGER_H
