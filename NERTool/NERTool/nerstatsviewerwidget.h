#ifndef NERSTATSVIEWERWIDGET_H
#define NERSTATSVIEWERWIDGET_H

#include <QtCore>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include "nercommon.h"
#include "qcustomplot.h"

enum GraphType {
    EditionErrorsGraph=0,
    RecognitionErrorGraph=1,
    CrossErrorGraph=2
};

class NERStatsViewerWidget : public QWidget
{
    Q_OBJECT
public:
    NERStatsViewerWidget(QWidget *parent=0);
    void loadGraphsData(NERStatsData &nerStatsData);
    void setPropertiesData(NERStatsData &nerStatsData);
    void replotGraphs();
    void clearGraphsData();

private:

    QGroupBox *nerValuesGroupBox;
    QVBoxLayout *mainNerGroupBoxLayout;

    QHBoxLayout *subBoxesLayout;

    QHBoxLayout *nerValuesLayout;
    QLabel *nerLabel;
    QLabel *nerValueLabel;

    QGroupBox *NPropsGroup;
    QVBoxLayout *NMainLayout;
    QHBoxLayout *N_Layout;
    QLabel *N_Label;
    QLabel *N_value_Label;
    QHBoxLayout *N_poctuationLayout;
    QLabel *N_ponctuation_Label;
    QLabel *N_ponctuation_value_Label;
    QHBoxLayout *N_transitionLayout;
    QLabel *N_transition_Label;
    QLabel *N_transition_value_Label;
    QHBoxLayout *N_wordsLayout;
    QLabel *N_words_Label;
    QLabel *N_words_value_Label;

    QGroupBox *recogErrorPropGroupbox;
    QVBoxLayout *recogMainLayout;
    QHBoxLayout *reLayout;
    QLabel *recogErrorLabel;
    QLabel *recogError_value_Label;
    QHBoxLayout *re_w025_Layout;
    QLabel *recogError_weigh025Label;
    QLabel *recogError_weigh025_value_Label;
    QHBoxLayout *re_w050_Layout;
    QLabel *recogError_weigh050Label;
    QLabel *recogError_weigh050_value_Label;
    QHBoxLayout *re_w100_Layout;
    QLabel *recogError_weigh100Label;
    QLabel *recogError_weigh100_value_Label;

    QGroupBox *editionErrorPropGroupbox;
    QVBoxLayout *editionMainLayout;
    QHBoxLayout *editonErrorLayout;
    QLabel *editionErrorLabel;
    QLabel *editionError_value_Label;
    QHBoxLayout *editionError_weight025Layout;
    QLabel *editionError_weigh025Label;
    QLabel *editionError_weigh025_value_Label;
    QHBoxLayout *editionError_weight050Layout;
    QLabel *editionError_weigh050Label;
    QLabel *editionError_weigh050_value_Label;
    QHBoxLayout *editionError_weight100Layout;
    QLabel *editionError_weigh100Label;
    QLabel *editionError_weigh100_value_Label;

    QPushButton *refreshButton;

    QCustomPlot *editionErrorPlot;
    QCustomPlot *recognitionErrorPlot;
    QCustomPlot *crossErrorPlot;
    QVBoxLayout *mainLayout;

    QGroupBox *plotsGroupBox;
    QHBoxLayout *plotsLayout;

    void createElements();
    void createActions();
    void setupBarChartDemo(QCustomPlot *customPlot,
                           NERStatsData &nerStatsData,
                           GraphType graphType);
    void setupBarChartCrossError(QCustomPlot *customPlot,
                                 NERStatsData &nerStatsData);

private slots:
    void refreshNERDataSlot();

signals:
    void refreshNERData();

};

#endif // NERSTATSVIEWERWIDGET_H
