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
#include <QProgressBar>
#include <QPushButton>
#include "nertablewidget.h"

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
    void removeAllSubNodes();
    QMap<QTreeWidgetItem*, QMdiSubWindow *> *getTreeSubWindowsMap();
    QTreeWidgetItem* getTranslationNode();

private:
    QVBoxLayout *mainVLayout;
    QGroupBox   *mainTreeGroupBox;
    QVBoxLayout *mainTreeGroupBoxLayout;
    QGroupBox   *nerPropsGroupBox;
    QVBoxLayout *nerPropsGroupBoxLayout;

//    QGridLayout *nerGridLayout;
//    QHBoxLayout *nerProps_NERLayout;
//    QLabel *nerProps_NERLabel;
//    QLabel *nerValueLabel;
//    QHBoxLayout *nerPropos_RELayout;
//    QLabel *nerPropos_RELabel;
//    QProgressBar *nerPropos_RE_value_Progress;
//    QHBoxLayout *nerPropos_ERLayout;
//    QLabel *nerPropos_ERLabel;
//    QProgressBar *nerPropos_ER_value_Progress;
//    QHBoxLayout *nerPropos_CELayout;
//    QLabel *nerPropos_CELabel;
//    QProgressBar *nerPropos_CE_value_Progress;
//    QHBoxLayout *nerPropos_NLayout;
//    QLabel *nerPropos_NLabel;
//    QLabel *nerPropos_N_value_Label;
//    QPushButton *computeNERPushBotton;
//    QPushButton *viewStatsDetailsButton;

    QTreeWidget *mainTreeWidget;
    QTreeWidgetItem *mainItemTrans;
    QTreeWidgetItem *mainItemSubs;
    QTreeWidget *nerPropsTreeWidget;
    QAction *openSubAction;
    QAction *removeSubAction;
    QAction *editSubPropertiesAction;

    QMap<QTreeWidgetItem*, QMdiSubWindow*> *subWindowsMap;

    QAction* openSubtitleAction;
    QAction* removeFileAction;

    void initTrees();
    void createActions();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private slots:
    void onTreeWidgetItemDoubleClicked(QTreeWidgetItem * item, int column);
    void openSubtitleWindowSlot();
    void removeSubNodeSlot();
    void renameDocumentNodeSlot(QTreeWidgetItem*item, int column);
    void computeNERValuesSlot();
    void viewStatsSlot();

public slots:
    void setNERStatistics(double &delay, double &ner);

signals:
    void computeNERValues();
    void viewNerStats();
    
};

#endif // PROPERTIESTREEWIDGET_H
