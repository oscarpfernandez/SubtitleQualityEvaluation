#include "nersummarywidget.h"

NERSummaryWidget::NERSummaryWidget(QWidget *parent)
{
    nerPropsGroupBox = new QGroupBox(QString("NER Properties"), this);
    nerPropsGroupBoxLayout = new QVBoxLayout();
    mainVLayout = new QHBoxLayout();

    nerProps_NERLayout = new QHBoxLayout();
    nerProps_NERLabel = new QLabel("NER (%): ");
    nerProps_NERLabel->setMaximumWidth(70);
    nerValueLabel = new QLabel;
    nerValueLabel->setText("0");
    nerProps_NERLayout->addWidget(nerProps_NERLabel, Qt::AlignRight);
    nerProps_NERLayout->addWidget(nerValueLabel, Qt::AlignLeft);

    nerPropos_NLayout = new QHBoxLayout();
    nerPropos_NLabel = new QLabel("Delay (s): ");
    nerPropos_NLabel->setMaximumWidth(70);
    nerPropos_N_value_Label = new QLabel;
    nerPropos_N_value_Label->setText("0");
    nerPropos_NLayout->addWidget(nerPropos_NLabel, Qt::AlignRight);
    nerPropos_NLayout->addWidget(nerPropos_N_value_Label, Qt::AlignLeft);


    wordReductionGroupBox = new QGroupBox(QString("Word Reduction"), this);
    wordReductionLayout = new QVBoxLayout;
    wordReductionGroupBox->setLayout(wordReductionLayout);
    reduct_percentLayout = new QHBoxLayout;
    reduct_percentLabel = new QLabel();
    reduct_percentLabel->setText("Reduction(%): ");
    reduct_percentLabel->setMinimumWidth(85);
    reduct_percentLabel->setMaximumWidth(100);
    reduct_percent_valueLabel = new QLabel;
    reduct_percentLayout->addWidget(reduct_percentLabel, Qt::AlignRight);
    reduct_percentLayout->addWidget(reduct_percent_valueLabel, Qt::AlignLeft);

    subsWordCount_Layout = new QHBoxLayout;
    subsWordCount_Label = new QLabel;
    subsWordCount_Label->setText("#S Words : ");
    subsWordCount_Label->setMinimumWidth(90);
    subsWordCount_Label->setMaximumWidth(100);
    subsWordCount_valueLabel = new QLabel;
    subsWordCount_Layout->addWidget(subsWordCount_Label);
    subsWordCount_Layout->addWidget(subsWordCount_valueLabel);

    transWordCount_Layout = new QHBoxLayout;
    transWordCount_Label = new QLabel;
    transWordCount_Label->setText("#T Words : ");
    transWordCount_Label->setMinimumWidth(90);
    transWordCount_Label->setMaximumWidth(100);
    transWordCount_valueLabel = new QLabel;
    transWordCount_Layout->addWidget(transWordCount_Label);
    transWordCount_Layout->addWidget(transWordCount_valueLabel);

    wordReductionLayout->addLayout(reduct_percentLayout);
    wordReductionLayout->addLayout(subsWordCount_Layout);
    wordReductionLayout->addLayout(transWordCount_Layout);

    computeNERPushBotton = new QPushButton("Compute NER");
    computeNERPushBotton->setMaximumWidth(170);
    connect(computeNERPushBotton, SIGNAL(clicked()), this, SLOT(computeNERValuesSlot()));

    viewStatsDetailsButton = new QPushButton("NER Statistics");
    viewStatsDetailsButton->setMaximumWidth(170);
    connect(viewStatsDetailsButton, SIGNAL(clicked()), this, SLOT(viewStatsSlot()));

    wordReductionGroupBox->setMaximumHeight(wordReductionGroupBox->sizeHint().height());
    wordReductionGroupBox->setMaximumWidth(200);
    nerPropsGroupBoxLayout->addLayout(nerProps_NERLayout);
    nerPropsGroupBoxLayout->addLayout(nerPropos_NLayout);

    nerPropsGroupBox->setLayout(nerPropsGroupBoxLayout);
    nerPropsGroupBox->setMaximumHeight(nerPropsGroupBox->sizeHint().height());
    nerPropsGroupBox->setMaximumWidth(180);

    mainVLayout->addWidget(nerPropsGroupBox);
    mainVLayout->addWidget(wordReductionGroupBox, Qt::AlignTop);
    mainVLayout->addWidget(computeNERPushBotton, Qt::AlignTop);
    mainVLayout->addWidget(viewStatsDetailsButton, Qt::AlignTop);

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

void NERSummaryWidget::setNERStatistics(NERStatsData &ner)
{
    nerValueLabel->setText(QString::number(ner.getNerValue()*100));
    nerPropos_N_value_Label->setText(QString::number(ner.getAvgDelay()));
    reduct_percent_valueLabel->setText(QString::number(ner.getReduction()*100));
    subsWordCount_valueLabel->setText(QString::number(ner.getN_words()));
    transWordCount_valueLabel->setText(QString::number(ner.getTransWordCount()));
}
