#ifndef NERSUMMARYWIDGET_H
#define NERSUMMARYWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>

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
    QLabel *nerProps_NERLabel;
    QLabel *nerValueLabel;
    QHBoxLayout *nerPropos_RELayout;
    QLabel *nerPropos_RELabel;
    QHBoxLayout *nerPropos_ERLayout;
    QLabel *nerPropos_ERLabel;
    QHBoxLayout *nerPropos_CELayout;
    QLabel *nerPropos_CELabel;
    QHBoxLayout *nerPropos_NLayout;
    QLabel *nerPropos_NLabel;
    QLabel *nerPropos_N_value_Label;
    QPushButton *computeNERPushBotton;
    QPushButton *viewStatsDetailsButton;

private slots:
    void computeNERValuesSlot();
    void viewStatsSlot();

public slots:
    void setNERStatistics(double &delay, double &ner);

signals:
    void computeNERValues();
    void viewNerStats();
};

#endif // NERSUMMARYWIDGET_H
