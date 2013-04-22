#ifndef NERSUMMARYWIDGET_H
#define NERSUMMARYWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include "nercommon.h"

class NERSummaryWidget : public QWidget
{
    Q_OBJECT
public:
    NERSummaryWidget(QWidget *parent=0);

private:
    QHBoxLayout *mainVLayout;
    QGroupBox   *nerPropsGroupBox;
    QVBoxLayout *nerPropsGroupBoxLayout;
    QGridLayout *nerGridLayout;
    QHBoxLayout *nerProps_NERLayout;
    QLabel      *nerProps_NERLabel;
    QLabel      *nerValueLabel;
    QHBoxLayout *nerPropos_RELayout;
    QLabel      *nerPropos_RELabel;
    QHBoxLayout *nerPropos_ERLayout;
    QLabel      *nerPropos_ERLabel;
    QHBoxLayout *nerPropos_CELayout;
    QLabel      *nerPropos_CELabel;
    QHBoxLayout *nerPropos_NLayout;
    QLabel      *nerPropos_NLabel;
    QLabel      *nerPropos_N_value_Label;
    QPushButton *computeNERPushBotton;
    QPushButton *viewStatsDetailsButton;

    QGroupBox   *wordReductionGroupBox;
    QVBoxLayout *wordReductionLayout;
    QHBoxLayout *reduct_percentLayout;
    QLabel      *reduct_percentLabel;
    QLabel      *reduct_percent_valueLabel;
    QHBoxLayout *subsWordCount_Layout;
    QLabel      *subsWordCount_Label;
    QLabel      *subsWordCount_valueLabel;
    QHBoxLayout *transWordCount_Layout;
    QLabel      *transWordCount_Label;
    QLabel      *transWordCount_valueLabel;


private slots:
    void computeNERValuesSlot();
    void viewStatsSlot();

public slots:
    void setNERStatistics(NERStatsData &ner);

signals:
    void computeNERValues();
    void viewNerStats();
};

#endif // NERSUMMARYWIDGET_H
