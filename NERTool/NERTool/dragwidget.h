#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include <QMap>
#include "draglabel.h"
#include "nercommon.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

const QString CORRECT_EDITION_STR = "Correct";
const QString RECOG_ERROR_STR = "RecognitionError";
const QString EDITION_ERROR_STR = "EditionError";
const QString EDITION_COMMENT_STR = "Edit Comment";
const QString INSERTION_STR = "Insertion";
const QString DELETION_STR = "Deletion";
const QString SUBSTITUTION_STR = "Substitution";
const QString ERROR_WEIGHT_0_STR =  "Weight 0";
const QString ERROR_WEIGHT_1_STR =  "Weight 1.00";
const QString ERROR_WEIGHT_05_STR = "Weight 0.50";
const QString ERROR_WEIGHT_025_STR = "Weight 0.25";
const double  ERROR_WEIGHT_0 = 0;
const double  ERROR_WEIGHT_1 = 1.0;
const double  ERROR_WEIGHT_025 = 0.25;
const double  ERROR_WEIGHT_050 = 0.50;

//! [0]
class DragWidget : public QWidget
{
    Q_OBJECT
public:
    DragWidget(QWidget *parent, QString &textBlock, int maxWidth, bool isModifiable);
    DragWidget(QWidget *parent, int maxWidth, bool isModifiable);
    ~DragWidget();
    void initializeData(QList<DragLabel*> labelList);
    QSize getBlockSize();
    void showCommentEditor();
    int countWords();
    DragLabel* getWordAt(int pos);
    QString getText();
    double getEditionErrors(NERStatsData &nerStats);
    double getRecognitionErrors(NERStatsData &nerStats);
    double getInsertions(NERStatsData &nerStats);
    double getDeletions(NERStatsData &nerStats);
    double getSubstitutions(NERStatsData &nerStats);
    QList<DragLabel*> getLabels();

protected:
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QAction* m_editionErrorAction;
    QAction* m_recognitionErrorAction;
    QAction* m_noErrorAction;
    QAction* m_Error0Action;
    QAction* m_Error025Action;
    QAction* m_Error050Action;
    QAction* m_Error100Action;
    QAction* m_insertionAction;
    QAction* m_substitutionAction;
    QAction* m_delectionAction;
    QAction* m_commentAction;

    QList<DragLabel*> *m_labelsPointerList;
    bool m_isModifiable;
    int m_maxWidgetWidth;
    int m_numberOfLines;
    int m_labelSize;
    int m_numLines;

    void createActions();
    void uncheckAllErrorActions();
    void uncheckAllWeightActions();
    void uncheckAllTypeActions();
    void setActionsEnabledForLabel(DragLabel* label);
    void propagateProperties(DragLabel* label, EditionTypeEnum previousType);
    void propagateModificationProperties(DragLabel* label);

};

#endif
