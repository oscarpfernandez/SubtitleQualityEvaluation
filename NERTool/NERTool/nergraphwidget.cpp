#include "nergraphwidget.h"

/*******************************************************************************
 * This classes produces the bar plot of the NER statistics associated with
 * the several respoken tables. It gives the account of Correct Edition, Edition
 * errors and Recognition Errors.
 ******************************************************************************/

NERGraphWidget::NERGraphWidget(QWidget *parent) : QWidget(parent)
{
    customPlot = new QCustomPlot(parent);

    // create empty bar chart objects:
    correctEditions = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    editionErrors = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    recogErrors = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(correctEditions);
    customPlot->addPlottable(editionErrors);
    customPlot->addPlottable(recogErrors);
    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    recogErrors->setName("Recognition Errors");
    pen.setColor(QColor(255, 131, 0));
    recogErrors->setPen(pen);
    recogErrors->setBrush(QColor(255, 131, 0, 50));
    editionErrors->setName("Edition Errors");
    pen.setColor(QColor(1, 92, 191));
    editionErrors->setPen(pen);
    editionErrors->setBrush(QColor(1, 92, 191, 50));
    correctEditions->setName("Correct Editions");
    pen.setColor(QColor(150, 222, 0));
    correctEditions->setPen(pen);
    correctEditions->setBrush(QColor(150, 222, 0, 70));
    // stack bars ontop of each other:
    editionErrors->moveAbove(recogErrors);
    correctEditions->moveAbove(editionErrors);

    // prepare x axis with country labels:
//    QVector<double> ticks;
//    QVector<QString> labels;
//    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
//    labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
//    customPlot->xAxis->setAutoTicks(false);
//    customPlot->xAxis->setAutoTickLabels(false);
//    customPlot->xAxis->setTickVector(ticks);
//    customPlot->xAxis->setTickVectorLabels(labels);
//    customPlot->xAxis->setTickLabelRotation(60);
//    customPlot->xAxis->setSubTickCount(0);
//    customPlot->xAxis->setTickLength(0, 4);
//    customPlot->xAxis->setGrid(false);
//    customPlot->xAxis->setRange(0, 8);

    // prepare y axis:
//    customPlot->yAxis->setRange(0, 12.1);
//    customPlot->yAxis->setPadding(5); // a bit more space to the left border
//    customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
//    customPlot->yAxis->setSubGrid(true);
//    QPen gridPen;
//    gridPen.setStyle(Qt::SolidLine);
//    gridPen.setColor(QColor(0, 0, 0, 25));
//    customPlot->yAxis->setGridPen(gridPen);
//    gridPen.setStyle(Qt::DotLine);
//    customPlot->yAxis->setSubGridPen(gridPen);

    // Add data:
//    QVector<double> recogErrorsData, editionErrorsData, correctEditionsData;
//    recogErrorsData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
//    editionErrorsData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
//    correctEditionsData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
//    recogErrors->setData(ticks, recogErrorsData);
//    editionErrors->setData(ticks, editionErrorsData);
//    correctEditions->setData(ticks, correctEditionsData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->legend->setPositionStyle(QCPLegend::psTop);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);

    customPlot->setRangeDrag(Qt::Horizontal|Qt::Vertical);
    customPlot->setRangeZoom(Qt::Horizontal|Qt::Vertical);

}


/*******************************************************************************
 * The method updates the plot graph with the labels (X-axis) and data (Y-axis)
 * of each table and the associated data for each case.
 ******************************************************************************/
void NERGraphWidget::setupBarPlot(QVector<QString> &tickNerTableNames,
                                  QList<NERStatsData> &data)
{
    if(tickNerTableNames.count() == data.count()){
        return;
    }

    QVector<double> ticks;
    QVector<QString> labels;



    /*
     * Set ticks and labels for the X axis...
     */
    for(int i=0; i<tickNerTableNames.count(); i++)
    {
        ticks << i+1;
        labels << tickNerTableNames.at(i);
    }

    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setTickVectorLabels(labels);
    customPlot->xAxis->setTickLabelRotation(90);
    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setGrid(false);
    customPlot->xAxis->setRange(0, ticks.count());

    QVector<double> recogErrorsData, editionErrorsData, correctEditionsData;

    int maxN = 0;

    for(int k=0; k<data.count(); k++){
        NERStatsData stats = data.at(k);
        recogErrorsData  << stats.getRecognitionErrors();
        editionErrorsData << stats.getEditionErrors();
        correctEditionsData  << stats.getNCount()
                                - stats.getEditionErrors()
                                - stats.getRecognitionErrors();

        maxN = std::max(maxN, stats.getNCount());
    }

    recogErrors->clearData();
    recogErrors->setData(ticks, recogErrorsData);
    editionErrors->clearData();
    editionErrors->setData(ticks, editionErrorsData);
    correctEditions->clearData();
    correctEditions->setData(ticks, correctEditionsData);

    /*
     * Prepare Y-axis
     */
    customPlot->yAxis->setRange(0, maxN);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Number of words");
    customPlot->yAxis->setSubGrid(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->setGridPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->setSubGridPen(gridPen);


    //Redraw everything...
    customPlot->replot();
}
