#include "nersummarywidget.h"

NERSummaryWidget::NERSummaryWidget(QWidget *parent)
{
    nerPropsGroupBox = new QGroupBox(QString("NER Properties"), this);
    nerPropsGroupBoxLayout = new QVBoxLayout();
    mainVLayout = new QHBoxLayout();

    nerProps_NERLayout = new QHBoxLayout();
    nerProps_NERLabel = new QLabel("NER (%): ");
    nerProps_NERLabel->setMaximumWidth(75);
    nerValueLabel = new QLabel;
    nerValueLabel->setText("0");
    nerProps_NERLayout->addWidget(nerProps_NERLabel, Qt::AlignRight);
    nerProps_NERLayout->addWidget(nerValueLabel, Qt::AlignLeft);

    nerPropos_NLayout = new QHBoxLayout();
    nerPropos_NLabel = new QLabel("Delay (s): ");
    nerPropos_NLabel->setMaximumWidth(75);
    nerPropos_N_value_Label = new QLabel;
    nerPropos_N_value_Label->setText("0");
    nerPropos_NLayout->addWidget(nerPropos_NLabel, Qt::AlignRight);
    nerPropos_NLayout->addWidget(nerPropos_N_value_Label, Qt::AlignLeft);

    computeNERPushBotton = new QPushButton("Compute NER");
    computeNERPushBotton->setMaximumWidth(250);
    connect(computeNERPushBotton, SIGNAL(clicked()), this, SLOT(computeNERValuesSlot()));

    viewStatsDetailsButton = new QPushButton("NER Statistics");
    viewStatsDetailsButton->setMaximumWidth(250);
    connect(viewStatsDetailsButton, SIGNAL(clicked()), this, SLOT(viewStatsSlot()));

    nerPropsGroupBoxLayout->addLayout(nerProps_NERLayout);
    nerPropsGroupBoxLayout->addLayout(nerPropos_NLayout);

//    nerPropsGroupBoxLayout->addWidget(computeNERPushBotton, Qt::AlignCenter);
//    nerPropsGroupBoxLayout->addWidget(viewStatsDetailsButton, Qt::AlignCenter);

    nerPropsGroupBox->setLayout(nerPropsGroupBoxLayout);
    nerPropsGroupBox->setMaximumHeight(nerPropsGroupBox->sizeHint().height());

    mainVLayout->addWidget(nerPropsGroupBox);
    mainVLayout->addWidget(computeNERPushBotton, Qt::AlignCenter);
    mainVLayout->addWidget(viewStatsDetailsButton, Qt::AlignCenter);

    setLayout(mainVLayout);

    setWindowIcon(QIcon(":/resources/pics/stats.png"));

}

void NERSummaryWidget::computeNERValuesSlot()
{
    emit computeNERValues();
}

void NERSummaryWidget::viewStatsSlot()
{
    emit viewNerStats();
}

void NERSummaryWidget::setNERStatistics(double &delay, double &ner)
{
    nerValueLabel->setText(QString::number(ner));
    nerPropos_N_value_Label->setText(QString::number(delay));
}
