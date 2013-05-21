#include "reportexport.h"

ReportExport::ReportExport()
{
}

void ReportExport::generateExportFile(QString &filePath,
                                      QString &imgResName,
                                      NERStatsData nerData,
                                      QString name,
                                      QString resp,
                                      QString desc)
{
    if(filePath.isEmpty()){
        //nothing to do...
        return;
    }

    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    out << "<!doctype html>" << endl;
    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title>NER Project Report</title>" << endl;
    //CSS
    out << "<STYLE type=\"text/css\">" << endl;
    out << "html, body{  margin:0;  padding:0;  text-align:center; }  " << endl;
    out << "#pagewidth{  width:72%;  text-align:left;  margin:0 auto; } " << endl;
    out << "#header{ position:relative;  height:80px;  background-color:#99CCFF;  width:100%; display:block; overflow:auto;} " << endl;
    out << "#maincol{  background-color: #DFFFD3;   position: relative;  }"  << endl;

    //Table CSS
    out << "#psdgraphics-com-table {margin:0;padding: 4px;width: 350px;font: 11px Arial, Helvetica, sans-serif;color:#747474;background-color:#0c2a62;}" << endl;
    out << "#psdg-header {margin:0;padding: 14px 0 0 24px;width: 350px;height: 55px;color:#FFF;font-size:13px;background: #0c2c65 url(images/head-bcg.jpg) no-repeat right top;}" << endl;
    out << ".psdg-bold {font: bold 22px Arial, Helvetica, sans-serif;}" << endl;
    out << "#psdg-top {margin:0;padding: 0;width: 374px;height: 46px;border-top: 2px solid #FFF;background: #eff4ff url(images/top-light-blue.png) repeat-x left top;}" <<  endl;
    out << ".psdg-top-cell {float:left;padding: 15px 0 0 0;text-align:center;width:218px;height: 31px;border-right: 1px solid #ced9ec;color:#1f3d71;font: 13px Arial, Helvetica, sans-serif;}" << endl;
    out << "#psdg-middle {margin:0;padding: 0;width: 374px;background: #f6f6f6 url(images/center-bcg.png) repeat-y right top;}" << endl;
    out << ".psdg-left {float:left;margin:0;padding: 10px 0 0 24px;width: 129px;text-align: left;height: 25px;border-right: 1px solid #ced9ec;border-bottom: 1px solid #b3c1db;color:#1f3d71;font: 13px Arial, Helvetica, sans-serif;background: #e4ebf8 url(images/center-blue.png) repeat-y left top;}" << endl;
    out << ".psdg-right {float:left;margin:0;padding: 11px 0 0 0;width: 218px;text-align:center;height: 24px;border-right: 1px solid #ced9ec;border-bottom: 1px solid #b3c1db;}" << endl;
    out << "#psdg-bottom {clear:both;margin:0;padding: 0;width: 578px;height: 48px;border-top: 2px solid #FFF;background: #e4e3e3 url(images/bottom-line.png) repeat-x left top;}" << endl;
    out << ".psdg-bottom-cell {float:left;padding: 15px 0 0 0;text-align:center;width:105px;height: 33px;border-right: 1px solid #ced9ec;color:#070707;font: 13px Arial, Helvetica, sans-serif;}" << endl;
    out << "#psdg-footer {font-size: 10px;color:#8a8a8a;margin:0;padding: 8px 0 8px 12px;width: 566px;background: #f6f6f6 url(images/center-bcg.png) repeat-y right top;}" << endl;
    out << "</STYLE>"  << endl;

    out << "</head>" << endl;

    out << "<body>" << endl;
    out << "<div id=\"pagewidth\" >" << endl;
    out << "<div id=\"header\"><h1>NER Report</h1></div>" << endl;
    out << "<div id=\wrapper\" class=\"clearfix\">" << endl;
    out << "<div id=\"maincol\"><h2>Evaluation Results</h2><p>Table: <b>"<< name << "</b> </p>"
        << endl;

    out << "</div>"  << endl;

    out << "<div align=\"center\" id=\"psdg-header\" style=\"float:left\">" << endl;
    out << "<span class=\"psdg-bold\">NER Global Stats</span>" << endl;
    out << "</div>" << endl;

    out << "<div id=\"psdg-middle\">" << endl;
    out << "    <div class=\"psdg-left\">NER (&#37;)</div>" << endl;
    out << "    <div class=\"psdg-right\">" << QString::number(nerData.getNerValue()) << "</div>" << endl;
    out << "    <div class=\"psdg-left\">Average Delay (s)</div>" << endl;
    out << "    <div class=\"psdg-right\">" << QString::number(nerData.getAvgDelay())  << "</div>" << endl;
    out << "    <div class=\"psdg-left\">Text Reduction (&#37;)</div>" << endl;
    out << "    <div class=\"psdg-right\">" << QString::number(nerData.getReduction())  << "</div>" << endl;
    out << "</div>" << endl;


    out << "<p align=\"left\"><img src=\"" << "data:image/jpg;base64," << imgResName << "\" ></p>" << endl;
    out << "</div>"  << endl;
    out << "<div id=\"header\"><p align=\"left\"><h4> Generated in "
        << QDate::currentDate().toString() << " - "<< QTime::currentTime().toString()
        <<"</h4></p></div>" << endl;
    out << "</div>"  << endl;    
    out << "</div>"  << endl;

    out << "</body>" << endl;
    out << "</html>" << endl;

    out.flush();
    file.close();
}


