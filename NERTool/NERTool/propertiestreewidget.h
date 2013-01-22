#ifndef PROPERTIESTREEWIDGET_H
#define PROPERTIESTREEWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QGroupBox>
#include <QSplitter>
#include <QMenu>

class PropertiesTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesTreeWidget(QWidget *parent = 0);
    void insertNewSubtitle(QString &fileName, QString &responsible, QString &description);
    void insertNewSpeaker(QString &speaker);
    
private:
    QSplitter   *splitter;
    QVBoxLayout *mainVLayout;
    QGroupBox   *mainTreeGroupBox;
    QVBoxLayout *mainTreeGroupBoxLayout;
    QGroupBox   *nerPropsGroupBox;
    QVBoxLayout *nerPropsGroupBoxLayout;
    QTreeWidget *mainTreeWidget;
    QTreeWidgetItem *mainItemTrans;
    QTreeWidgetItem *mainItemSubs;
    QTreeWidget *nerPropsTreeWidget;
    QAction *openSubAction;
    QAction *removeSubAction;
    QAction *editSubPropertiesAction;
    void initTrees();
    void initContextMenuAction();
//    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void onTreeWidgetItemDoubleClicked(QTreeWidgetItem * item, int column);
    void openSubDocumentNodeSlot();
    void editSubPropertiesNode();
    void removeSubNodeSlot();

    
};

#endif // PROPERTIESTREEWIDGET_H
