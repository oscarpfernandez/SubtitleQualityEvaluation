#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include <QObject>
#include <QTreeWidgetItem>
#include "nertablewidget.h"
#include "xmlhandler.h"


#ifndef NER_PACK_ITEM
#define NER_PACK_ITEM

struct NerPackItem
{
private:
    QString name;
    QString responsible;
    QString description;
    QList<BlockTRS> *subsList;
    QTreeWidgetItem *treeNode;
    NERTableWidget  *table;
public:
    NerPackItem& setName(QString &pname){}
    QString getName(){return name;}
    QString getResponsible(){ return responsible;}
    QString getDescription(){ return description;}
    QList<BlockTRS>* getTRSBlock(){ return subsList;}
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
    void loadTranscriptionFile(QString &fileName);
    void loadSubtitleFile(QString &fileName);

private:
    QList<BlockTRS> *transcriptionList;
    bool isTranscriptionLoaded;
    XMLHandler *xmlHandler;


};

#endif // CONTENTMANAGER_H
