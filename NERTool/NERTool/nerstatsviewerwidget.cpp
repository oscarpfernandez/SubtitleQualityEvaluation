#include "nerstatsviewerwidget.h"

NERStatsViewerWidget::NERStatsViewerWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("NER Statistics");

    createElements();
    createActions();

    setLayout(mainLayout);

    setFixedSize(sizeHint());

}


void NERStatsViewerWidget::createElements()
{
    mainLayout = new QVBoxLayout;

    mainNerGroupBoxLayout = new QVBoxLayout;

    nerValuesGroupBox = new QGroupBox("NER Properties");
    nerValuesLayout = new QHBoxLayout;
    //Ner Label
    nerLabel = new QLabel("NER (%): ");
    nerLabel->setMaximumWidth(80);
    nerValueLabel = new QLabel(); ////
    nerValueLabel->setMaximumWidth(200);
    nerValueLabel->setText("0");

    subBoxesLayout = new QHBoxLayout;

    // N properties
    N_Layout = new QHBoxLayout;
    N_Label = new QLabel("Total N: ");
    N_Label->setMaximumWidth(160);
    N_Label->setMinimumWidth(160);
    N_value_Label = new QLabel;
    N_value_Label->setText("0");
    N_Layout->addWidget(N_Label);
    N_Layout->addWidget(N_value_Label);

    N_poctuationLayout = new QHBoxLayout;
    N_ponctuation_Label = new QLabel("# Punctuations: ");
    N_ponctuation_Label->setMaximumWidth(160);
    N_ponctuation_Label->setMinimumWidth(160);
    N_ponctuation_value_Label = new QLabel;
    N_ponctuation_value_Label->setText("12312");
    N_poctuationLayout->addWidget(N_ponctuation_Label);
    N_poctuationLayout->addWidget(N_ponctuation_value_Label);

    N_transitionLayout = new QHBoxLayout;
    N_transition_Label = new QLabel("# Transitions: ");
    N_transition_Label->setMaximumWidth(160);
    N_transition_Label->setMinimumWidth(160);
    N_transition_value_Label = new QLabel;
    N_transition_value_Label->setText("0");
    N_transitionLayout->addWidget(N_transition_Label);
    N_transitionLayout->addWidget(N_transition_value_Label);

    N_wordsLayout = new QHBoxLayout;
    N_words_Label = new QLabel("# Words: ");
    N_words_Label->setMaximumWidth(160);
    N_words_Label->setMinimumWidth(160);
    N_words_value_Label = new QLabel;
    N_words_value_Label->setMaximumWidth(150);
    N_words_value_Label->setText("0");
    N_wordsLayout->addWidget(N_words_Label);
    N_wordsLayout->addWidget(N_words_value_Label);

    NMainLayout = new QVBoxLayout;
    NMainLayout->setAlignment(Qt::AlignLeft);
    NMainLayout->addLayout(N_wordsLayout);
    NMainLayout->addLayout(N_poctuationLayout);
    NMainLayout->addLayout(N_transitionLayout);
    NMainLayout->addLayout(N_Layout);

    NPropsGroup = new QGroupBox("Word Properties");
    NPropsGroup->setLayout(NMainLayout);

    //Recogntion Error properties
    recogErrorPropGroupbox = new QGroupBox("Recognition Error Properties");
    recogMainLayout = new QVBoxLayout;

    reLayout = new QHBoxLayout;
    recogErrorLabel = new QLabel("Recognition Error: ");
    recogErrorLabel->setMaximumWidth(160);
    recogErrorLabel->setMinimumWidth(160);
    recogError_value_Label = new QLabel;
    reLayout->addWidget(recogErrorLabel);
    reLayout->addWidget(recogError_value_Label);
    re_w025_Layout = new QHBoxLayout;
    recogError_weigh025Label = new QLabel("# Weight(0.25): ");
    recogError_weigh025Label->setMaximumWidth(160);
    recogError_weigh025Label->setMinimumWidth(160);
    recogError_weigh025_value_Label = new QLabel;
    re_w025_Layout->addWidget(recogError_weigh025Label);
    re_w025_Layout->addWidget(recogError_weigh025_value_Label);
    re_w050_Layout = new QHBoxLayout;
    recogError_weigh050Label = new QLabel("# Weight(0.5): ");
    recogError_weigh050Label->setMaximumWidth(160);
    recogError_weigh050Label->setMinimumWidth(160);
    recogError_weigh050_value_Label = new QLabel;
    re_w050_Layout->addWidget(recogError_weigh050Label);
    re_w050_Layout->addWidget(recogError_weigh050_value_Label);
    re_w100_Layout = new QHBoxLayout;
    recogError_weigh100Label= new QLabel("# Weight(1.0): ");
    recogError_weigh100Label->setMaximumWidth(160);
    recogError_weigh100Label->setMinimumWidth(160);
    recogError_weigh100_value_Label = new QLabel;
    re_w100_Layout->addWidget(recogError_weigh100Label);
    re_w100_Layout->addWidget(recogError_weigh100_value_Label);

    recogMainLayout->addLayout(reLayout);
    recogMainLayout->addLayout(re_w025_Layout);
    recogMainLayout->addLayout(re_w050_Layout);
    recogMainLayout->addLayout(re_w100_Layout);
    recogErrorPropGroupbox->setLayout(recogMainLayout);


    //Edition Errors
    editionErrorPropGroupbox = new QGroupBox("Edition Error Properties");
    editionMainLayout = new QVBoxLayout;
    editonErrorLayout = new QHBoxLayout;
    editionErrorLabel = new QLabel("Edition Error: ");
    editionErrorLabel->setMaximumWidth(160);
    editionErrorLabel->setMinimumWidth(160);
    editionError_value_Label = new QLabel;
    editonErrorLayout->addWidget(editionErrorLabel);
    editonErrorLayout->addWidget(editionError_value_Label);
    editionError_weight025Layout = new QHBoxLayout;
    editionError_weigh025Label = new QLabel("# Weight(0.25):");
    editionError_weigh025Label->setMaximumWidth(160);
    editionError_weigh025Label->setMinimumWidth(160);
    editionError_weigh025_value_Label = new QLabel;
    editionError_weight025Layout->addWidget(editionError_weigh025Label);
    editionError_weight025Layout->addWidget(editionError_weigh025_value_Label);
    editionError_weight050Layout = new QHBoxLayout;
    editionError_weigh050Label= new QLabel("# Weight(0.5):");
    editionError_weigh050Label->setMaximumWidth(160);
    editionError_weigh050Label->setMinimumWidth(160);
    editionError_weigh050_value_Label = new QLabel;
    editionError_weight050Layout->addWidget(editionError_weigh050Label);
    editionError_weight050Layout->addWidget(editionError_weigh050_value_Label);
    editionError_weight100Layout = new QHBoxLayout;
    editionError_weigh100Label = new QLabel("# Weight(1.0):");
    editionError_weigh100Label->setMaximumWidth(160);
    editionError_weigh100Label->setMinimumWidth(160);
    editionError_weigh100_value_Label = new QLabel;
    editionError_weight100Layout->addWidget(editionError_weigh100Label);
    editionError_weight100Layout->addWidget(editionError_weigh100_value_Label);

    editionMainLayout->addLayout(editonErrorLayout);
    editionMainLayout->addLayout(editionError_weight025Layout);
    editionMainLayout->addLayout(editionError_weight050Layout);
    editionMainLayout->addLayout(editionError_weight100Layout);
    editionErrorPropGroupbox->setLayout(editionMainLayout);


    nerValuesLayout->setAlignment(Qt::AlignLeft);
    nerValuesLayout->addWidget(nerLabel, Qt::AlignRight);
    nerValuesLayout->addWidget(nerValueLabel, Qt::AlignLeft);

    //Boxes Layout
    subBoxesLayout->addWidget(NPropsGroup);
    subBoxesLayout->addWidget(recogErrorPropGroupbox);
    subBoxesLayout->addWidget(editionErrorPropGroupbox);

    mainNerGroupBoxLayout->addLayout(nerValuesLayout);
    mainNerGroupBoxLayout->addLayout(subBoxesLayout);

    nerValuesGroupBox->setLayout(mainNerGroupBoxLayout);


    //PLots
    editionErrorPlot = new QCustomPlot();
    recognitionErrorPlot = new QCustomPlot();
    crossErrorPlot = new QCustomPlot();
    editionErrorsModifTypePlot = new QCustomPlot();
    recogErrorsModifTypePlot = new QCustomPlot();
    recogErrorsCrossModifTypePlot = new QCustomPlot();

    plotsLayout = new QVBoxLayout;
    subBoxesInsDelsSubsLayout = new QHBoxLayout;
    subBoxesEdErrorrecogError = new QHBoxLayout;

    subBoxesInsDelsSubsLayout->addWidget(recogErrorsCrossModifTypePlot);
    subBoxesInsDelsSubsLayout->addWidget(recogErrorsModifTypePlot);
    subBoxesInsDelsSubsLayout->addWidget(editionErrorsModifTypePlot);


    plotsLayout->addLayout(subBoxesEdErrorrecogError);
    plotsLayout->addLayout(subBoxesInsDelsSubsLayout);

    subBoxesEdErrorrecogError->addWidget(crossErrorPlot);
    subBoxesEdErrorrecogError->addWidget(recognitionErrorPlot);
    subBoxesEdErrorrecogError->addWidget(editionErrorPlot);

    plotsGroupBox = new QGroupBox("NER Statistics Plots", this);
    plotsGroupBox->setLayout(plotsLayout);
    plotsGroupBox->setMinimumSize(QSize(950,550));

    refreshButton = new QPushButton("Refresh", this);
    refreshButton->setMaximumWidth(100);
    connect(refreshButton,SIGNAL(clicked()), this, SLOT(refreshNERDataSlot()));

    mainLayout->addWidget(nerValuesGroupBox);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(plotsGroupBox);
    mainLayout->addWidget(refreshButton);

}

void NERStatsViewerWidget::refreshNERDataSlot()
{
    emit refreshNERData();
}

void NERStatsViewerWidget::createActions()
{

}

void NERStatsViewerWidget::replotGraphs()
{
    editionErrorPlot->replot();
    recognitionErrorPlot->replot();
    crossErrorPlot->replot();
    editionErrorsModifTypePlot->replot();
    recogErrorsModifTypePlot->replot();
    recogErrorsCrossModifTypePlot->replot();
}

void NERStatsViewerWidget::clearGraphsData()
{
    editionErrorPlot->clearPlottables();
    recognitionErrorPlot->clearPlottables();
    crossErrorPlot->clearPlottables();
    editionErrorsModifTypePlot->clearPlottables();
    recogErrorsModifTypePlot->clearPlottables();
    recogErrorsCrossModifTypePlot->clearPlottables();
}

void NERStatsViewerWidget::loadGraphsData(NERStatsData &nerStatsData)
{
    setupBarChartDemo(editionErrorPlot, nerStatsData, EditionErrorsGraph);
    setupBarChartDemo(recognitionErrorPlot, nerStatsData, RecognitionErrorGraph);
    setupBarChartCrossError(crossErrorPlot, nerStatsData);
    setupBarChartModifTypes(editionErrorsModifTypePlot, nerStatsData, EditionInsDelSubsGraph);
    setupBarChartModifTypes(recogErrorsModifTypePlot,   nerStatsData, RecognitionInsDelSubsGraph);
    setupBarChartCrossModifTypes(recogErrorsCrossModifTypePlot, nerStatsData);

    setPropertiesData(nerStatsData);
}

void NERStatsViewerWidget::setPropertiesData(NERStatsData &nerStatsData)
{
    nerValueLabel->setText(QString::number(nerStatsData.getNerValue()*100));
    N_value_Label->setText(QString::number(nerStatsData.getNCount()));
    N_ponctuation_value_Label->setText(QString::number(nerStatsData.getN_ponctuation()));
    N_transition_value_Label->setText(QString::number(nerStatsData.getN_transitions()));
    N_words_value_Label->setText(QString::number(nerStatsData.getN_words()));

    recogError_value_Label->setText(QString::number(nerStatsData.getRecognitionErrors()));
    recogError_weigh025_value_Label->setText(QString::number(nerStatsData.getRecognitionErrors_w025()));
    recogError_weigh050_value_Label->setText(QString::number(nerStatsData.getRecognitionErrors_w050()));
    recogError_weigh100_value_Label->setText(QString::number(nerStatsData.getRecognitionErrors_w100()));

    editionError_value_Label->setText(QString::number(nerStatsData.getEditionErrors()));
    editionError_weigh025_value_Label->setText(QString::number(nerStatsData.getEditionErrors_w025()));
    editionError_weigh050_value_Label->setText(QString::number(nerStatsData.getEditionErrors_w050()));
    editionError_weigh100_value_Label->setText(QString::number(nerStatsData.getEditionErrors_w100()));
}

void NERStatsViewerWidget::setupBarChartDemo(QCustomPlot *customPlot,
                                             NERStatsData &nerStatsData,
                                             GraphType graphType)
{

    // create empty bar chart objects:
    QCPBars *weight_025_Bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *weight_050_Bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *weight_100_Bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(weight_025_Bar);
    customPlot->addPlottable(weight_050_Bar);
    customPlot->addPlottable(weight_100_Bar);

    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    weight_025_Bar->setName("Weight 0.25");
    pen.setColor(QColor(255, 131, 0));
    weight_025_Bar->setPen(pen);
    weight_025_Bar->setBrush(QColor(255, 131, 0, 50));
    weight_050_Bar->setName("Weight 0.5");
    pen.setColor(QColor(1, 92, 191));
    weight_050_Bar->setPen(pen);
    weight_050_Bar->setBrush(QColor(1, 92, 191, 50));
    weight_100_Bar->setName("Weight 1.0");
    pen.setColor(QColor(150, 222, 0));
    weight_100_Bar->setPen(pen);
    weight_100_Bar->setBrush(QColor(150, 222, 0, 70));
    // stack bars ontop of each other:
    weight_025_Bar->moveAbove(weight_050_Bar);
    weight_050_Bar->moveAbove(weight_100_Bar);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3;
    labels << "0.25" << "0.50" << "1.0";
    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setTickVectorLabels(labels);
    customPlot->xAxis->setTickLabelRotation(0);
    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setGrid(false);
    customPlot->xAxis->setRange(0, 4);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 101); // Y-Axis in percentage!!!;
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    if(graphType == EditionErrorsGraph){
        customPlot->yAxis->setLabel("Edition Error");
    }
    else if(graphType == RecognitionErrorGraph){
        customPlot->yAxis->setLabel("Recognition Error");
    }
//    else if(graphType == CrossErrorGraph){
//        customPlot->yAxis->setLabel("Edition Error vs Recognition Error");
//    }
    customPlot->yAxis->setSubGrid(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->setGridPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->setSubGridPen(gridPen);


    //Extract stats data...

    QVector<double> weight025Data, weight050Data, weight100Data;

    double edError_w025_Percent = 0;
    double edError_w050_Percent = 0;
    double edError_w100_Percent = 0;

    if(graphType == EditionErrorsGraph)
    {
        double edError_w025 = nerStatsData.getEditionErrors_w025();
        double edError_w050 = nerStatsData.getEditionErrors_w050();
        double edError_w100 = nerStatsData.getEditionErrors_w100();

        double sum = edError_w025 + edError_w050 + edError_w100;

        if(sum !=0){
            edError_w025_Percent = (edError_w025 / sum) * 100;
            edError_w050_Percent = (edError_w050 / sum) * 100;
            edError_w100_Percent = (edError_w100 / sum) * 100;
        }

        weight025Data   << edError_w025_Percent << 0 << 0;
        weight050Data   << 0 << edError_w050_Percent << 0;
        weight100Data   << 0 << 0 << edError_w100_Percent;
    }
    else if(graphType == RecognitionErrorGraph)
    {
        double edError_w025 = nerStatsData.getRecognitionErrors_w025();
        double edError_w050 = nerStatsData.getRecognitionErrors_w050();
        double edError_w100 = nerStatsData.getRecognitionErrors_w100();

        double sum = edError_w025 + edError_w050 + edError_w100;

        if(sum !=0){
            edError_w025_Percent = (edError_w025 / sum) * 100;
            edError_w050_Percent = (edError_w050 / sum) * 100;
            edError_w100_Percent = (edError_w100 / sum) * 100;
        }

        weight025Data   << edError_w025_Percent << 0 << 0;
        weight050Data   << 0 << edError_w050_Percent << 0;
        weight100Data   << 0 << 0 << edError_w100_Percent;
    }

    weight_025_Bar->setData(ticks, weight025Data);
    weight_050_Bar->setData(ticks, weight050Data);
    weight_100_Bar->setData(ticks, weight100Data);

    // setup legend:
    customPlot->legend->setVisible(false);
    customPlot->legend->setPositionStyle(QCPLegend::psTop);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    customPlot->legend->setFont(legendFont);
}

void NERStatsViewerWidget::setupBarChartCrossError(QCustomPlot *customPlot,
                                                   NERStatsData &nerStatsData)
{

    // create empty bar chart objects:
    QCPBars *edErrorBar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *recogErrorBar = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(edErrorBar);
    customPlot->addPlottable(recogErrorBar);

    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    edErrorBar->setName("Edition Errors");
    pen.setColor(QColor(255, 131, 140));
    edErrorBar->setPen(pen);
    edErrorBar->setBrush(QColor(255, 131, 0, 50));
    recogErrorBar->setName("Recognition Error");
    pen.setColor(QColor(30, 92, 191));
    recogErrorBar->setPen(pen);
    recogErrorBar->setBrush(QColor(1, 92, 191, 50));
    // stack bars ontop of each other:

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2;
    labels << "EE" << "RE";
    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setTickVectorLabels(labels);
    customPlot->xAxis->setTickLabelRotation(0);
    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setGrid(false);
    customPlot->xAxis->setRange(0, 4);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 101); // Y-Axis in percentage!!!;
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Edition vs Recognition \nError");

    customPlot->yAxis->setSubGrid(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->setGridPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->setSubGridPen(gridPen);

    QVector<double> edErrorData, recogErrorData;

    double edError_w025 = nerStatsData.getEditionErrors_w025();
    double edError_w050 = nerStatsData.getEditionErrors_w050();
    double edError_w100 = nerStatsData.getEditionErrors_w100();

    double recogError_w025 = nerStatsData.getRecognitionErrors_w025();
    double recogError_w050 = nerStatsData.getRecognitionErrors_w050();
    double recogError_w100 = nerStatsData.getRecognitionErrors_w100();

    double edErrorSum = edError_w025 + edError_w050 + edError_w100;
    double recogErrorSum = recogError_w025 + recogError_w050 + recogError_w100;

    double globalSum = edErrorSum + recogErrorSum;

    double edError_percent = 0;
    double recogError_percent = 0;

    if(globalSum !=0){
        edError_percent = (edErrorSum/globalSum)*100;
        recogError_percent = (recogErrorSum/globalSum)*100;
    }

    edErrorData << edError_percent << 0;
    recogErrorData << 0 << recogError_percent;

    edErrorBar->setData(ticks, edErrorData);
    recogErrorBar->setData(ticks, recogErrorData);


    // setup legend:
    customPlot->legend->setVisible(false);
    customPlot->legend->setPositionStyle(QCPLegend::psBottomRight);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(5);
    customPlot->legend->setFont(legendFont);

}

void NERStatsViewerWidget::setupBarChartModifTypes(QCustomPlot *customPlot,
                                                   NERStatsData &nerStatsData,
                                                   GraphType graphType)
{
    // create empty bar chart objects:
    QCPBars *inserton_Bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *deletion_Bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *substitution_Bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(inserton_Bar);
    customPlot->addPlottable(deletion_Bar);
    customPlot->addPlottable(substitution_Bar);

    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    inserton_Bar->setName("Insertion");
    pen.setColor(QColor(255, 131, 0));
    inserton_Bar->setPen(pen);
    inserton_Bar->setBrush(QColor(255, 131, 0, 50));
    deletion_Bar->setName("Deletion");
    pen.setColor(QColor(1, 92, 191));
    deletion_Bar->setPen(pen);
    deletion_Bar->setBrush(QColor(1, 92, 191, 50));
    substitution_Bar->setName("Substitution");
    pen.setColor(QColor(150, 222, 0));
    substitution_Bar->setPen(pen);
    substitution_Bar->setBrush(QColor(150, 222, 0, 70));


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3;
    labels << "Ins" << "Del" << "Subs";
    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setTickVectorLabels(labels);
    customPlot->xAxis->setTickLabelRotation(0);
    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setGrid(false);
    customPlot->xAxis->setRange(0, 4);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 101); // Y-Axis in percentage!!!;
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    if(graphType == EditionInsDelSubsGraph){
        customPlot->yAxis->setLabel("Edition Error");
    }
    else if(graphType == RecognitionInsDelSubsGraph){
        customPlot->yAxis->setLabel("Recognition Error");
    }

    customPlot->yAxis->setSubGrid(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->setGridPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->setSubGridPen(gridPen);


    //Extract stats data...
    QVector<double> insData, delData, subsData;

    double ins_percent = 0;
    double dels_percent = 0;
    double subs_percent = 0;

    if(graphType == EditionInsDelSubsGraph)
    {
        double ins = nerStatsData.getEdErrorInsertions();
        double dels = nerStatsData.getEdErrorDeletions();
        double subs = nerStatsData.getEdErrorSubstitutions();


        double sum = ins + dels + subs;

        if(sum !=0){
            ins_percent = (ins / sum) * 100;
            dels_percent = (dels / sum) * 100;
            subs_percent = (subs / sum) * 100;
        }
    }
    else if(graphType == RecognitionInsDelSubsGraph)
    {
        double ins  = nerStatsData.getRecogErrorInsertions();
        double dels = nerStatsData.getRecogErrorDeletions();
        double subs = nerStatsData.getRecogErrorSubstitutions();

        double sum = ins + dels + subs;

        if(sum !=0){
            ins_percent = (ins / sum) * 100;
            dels_percent = (dels / sum) * 100;
            subs_percent = (subs / sum) * 100;
        }
    }

    insData   << ins_percent << 0 << 0;
    delData   << 0 << dels_percent << 0;
    subsData   << 0 << 0 << subs_percent;

    inserton_Bar->setData(ticks, insData);
    deletion_Bar->setData(ticks, delData);
    substitution_Bar->setData(ticks, subsData);

    // setup legend:
    customPlot->legend->setVisible(false);
    customPlot->legend->setPositionStyle(QCPLegend::psTop);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    customPlot->legend->setFont(legendFont);
}

void NERStatsViewerWidget::setupBarChartCrossModifTypes(QCustomPlot *customPlot,
                                                        NERStatsData &nerStatsData)
{
    // create empty bar chart objects:
    QCPBars *inserton_Bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *deletion_Bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *substitution_Bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(inserton_Bar);
    customPlot->addPlottable(deletion_Bar);
    customPlot->addPlottable(substitution_Bar);

    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    inserton_Bar->setName("Insertion");
    pen.setColor(QColor(255, 131, 0));
    inserton_Bar->setPen(pen);
    inserton_Bar->setBrush(QColor(255, 131, 0, 50));
    deletion_Bar->setName("Deletion");
    pen.setColor(QColor(1, 92, 191));
    deletion_Bar->setPen(pen);
    deletion_Bar->setBrush(QColor(1, 92, 191, 50));
    substitution_Bar->setName("Substitution");
    pen.setColor(QColor(150, 222, 0));
    substitution_Bar->setPen(pen);
    substitution_Bar->setBrush(QColor(150, 222, 0, 70));


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3;
    labels << "Ins" << "Del" << "Subs";
    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setTickVectorLabels(labels);
    customPlot->xAxis->setTickLabelRotation(0);
    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setGrid(false);
    customPlot->xAxis->setRange(0, 4);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 101); // Y-Axis in percentage!!!;
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Ins vs Del vs Subs");

    customPlot->yAxis->setSubGrid(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->setGridPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->setSubGridPen(gridPen);


    //Extract stats data...
    QVector<double> insData, delData, subsData;

    double ins_percent = 0;
    double dels_percent = 0;
    double subs_percent = 0;

    double ins = nerStatsData.getEdErrorInsertions() + nerStatsData.getRecogErrorInsertions();
    double dels = nerStatsData.getEdErrorDeletions() + nerStatsData.getRecogErrorDeletions();
    double subs = nerStatsData.getEdErrorSubstitutions() + nerStatsData.getRecogErrorSubstitutions();


    double sum = ins + dels + subs;

    if(sum !=0){
        ins_percent = (ins / sum) * 100;
        dels_percent = (dels / sum) * 100;
        subs_percent = (subs / sum) * 100;
    }

    insData   << ins_percent << 0 << 0;
    delData   << 0 << dels_percent << 0;
    subsData   << 0 << 0 << subs_percent;

    inserton_Bar->setData(ticks, insData);
    deletion_Bar->setData(ticks, delData);
    substitution_Bar->setData(ticks, subsData);


    // setup legend:
    customPlot->legend->setVisible(false);
    customPlot->legend->setPositionStyle(QCPLegend::psTop);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    customPlot->legend->setFont(legendFont);
}

QString NERStatsViewerWidget::saveWidgetToImg(QString &filePath)
{

    const QSize imgSize(size().width(), size().height()-40);
    QImage img(imgSize, QImage::Format_RGB32);
    QPainter painter(&img);
    render(&painter);
    img.save(filePath);

    QFile sourceFile(filePath);
    sourceFile.open(QIODevice::ReadOnly);

    QByteArray srcRawData = sourceFile.readAll();
    QByteArray base64Encoded = srcRawData.toBase64();

    return base64Encoded;

}
