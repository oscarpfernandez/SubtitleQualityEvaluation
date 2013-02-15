#ifndef PROPERTIESTREEWIDGET_H
#define PROPERTIESTREEWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QGroupBox>
#include <QSplitter>
#include <QMdiSubWindow>
#include <QMenu>
#include <QEvent>
#include <QMouseEvent>
#include <QMap>

class PropertiesTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesTreeWidget(QWidget *parent = 0);
    QTreeWidgetItem* insertNewSubtitle(QString &fileName,
                                       QMdiSubWindow *subWindow,
                                       QString &responsible,
                                       QString &description);
    void insertNewTranslation(QString &fileName,
                              QString &responsible,
                              QString &description);
    void insertNewSpeaker(QString &speaker);
    void clearAllTreeData();
    
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
    QMap<QTreeWidgetItem*, QMdiSubWindow*> *subWindowsMap;

    void initTrees();
    void initContextMenuAction();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void onTreeWidgetItemDoubleClicked(QTreeWidgetItem * item, int column);
    void openSubDocumentNodeSlot();
    void editSubPropertiesNode();
    void removeSubNodeSlot();

    
};

#endif // PROPERTIESTREEWIDGET_H
