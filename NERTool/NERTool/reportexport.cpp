#include "reportexport.h"

ReportExport::ReportExport()
{
}

void ReportExport::writeHeader(QString &filePath)
{
    if(filePath.isEmpty()){
        //nothing to do...
        return;
    }

    QFile file(filePath);
    file.open(QIODevice::WriteOnly );
    QTextStream out(&file);

    out << "<!doctype html>" << endl;
    out << "<META HTTP-EQUIV=\"content-type\" CONTENT=\"text/html; charset=utf-8\">" << endl;
    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title>NER Project Report</title>" << endl;
    //CSS
    out << "<STYLE type=\"text/css\">" << endl;
    out << "html, body{  margin:0;  padding:0;  text-align:center; }  " << endl;
    out << "#pagewidth{  width:72%;  text-align:left;  margin:0 auto; } " << endl;
    out << "#header{ position:relative;  height:198px;  background-color:#99CCFF;  width:100%; display:block; overflow:auto;} " << endl;
    out << "#footer{ position:relative;  height:80px;  background-color:#99CCFF;  width:100%; display:block; overflow:auto;} " << endl;
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

    out << ".datagrid table { border-collapse: collapse; text-align: left; width: 100%; }" << endl;
    out << ".datagrid {padding: 10px; font: normal 12px/150% Arial, Helvetica, sans-serif; background: #fff; overflow: hidden; border: 1px solid #006699; -webkit-border-radius: 3px; -moz-border-radius: 3px; border-radius: 3px; }" << endl;
    out << ".datagrid table td, .datagrid table th { padding: 3px 10px; border:1px solid black;}" << endl;
    out << ".datagrid table thead th {background:-webkit-gradient( linear, left top, left bottom, color-stop(0.05, #006699), color-stop(1, #00557F) );background:-moz-linear-gradient( center top, #006699 5%, #00557F 100% );filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#006699', endColorstr='#00557F');background-color:#006699; color:#FFFFFF; font-size: 14px; font-weight: bold; border-left: 1px solid #0070A8; } " << endl;
    out << ".datagrid table thead th:first-child { border: none;}" << endl;
    out << ".datagrid table tbody td {  color: #00496B; font-size: 14px;border-bottom: 2px solid #E1EEF4;font-weight: normal; width:20%; border:1px solid black; }" << endl;
    out << ".datagrid table tbody .alt td { background: #E1EEF4; color: #00496B;}" << endl;
    out << ".datagrid table tbody td:first-child { border-left: none; }" << endl;
    out << ".datagrid table tbody tr:last-child td { border-bottom: 2px solid #E1EEF4; }" << endl;
    out << "table.fixed { table-layout:fixed; }" << endl;
    out << "table.fixed td { overflow: hidden; }" << endl;

    out << "</STYLE>"  << endl;

    out << "</head>" << endl;

    out << "<body>" << endl;
    out << "<div id=\"pagewidth\" >" << endl;
    out << "<div id=\"header\">" << endl;

    out << "<div id=\"box\"><table width=\"100%\" border=\"0\"> <tr> <td>" << endl;

    QString logoBase64Encoded = Utils::getBase64ImageEncode(":/resources/pics/reportLogo.png");

    out << "<img src=\"" << "data:image/jpg;base64," << logoBase64Encoded << "\">" << endl;

    out << "</td> <td> <h1>NER Project Report</h1> </td> </tr> </table> </div> </div>" << endl;

    out.flush();
    file.close();
}

void ReportExport::generateExportFile(QString &filePath,
                                      QString &imgResName,
                                      NERTableWidget *table)
{
    if(filePath.isEmpty() || table==0){
        //nothing to do...
        return;
    }

    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&file);

    NERStatsData nerData = table->getNERStatsValues();

    out << "<div id=\wrapper\" class=\"clearfix\">" << endl;
    out << "<div class=\"datagrid\">  <div id=\"box\">" << endl;
    out << "<div id=\"maincol\"><h2><br>Evaluation Results | Table: <b>"<< table->getTableName() << "</b>  <br><br></h2>" << endl;
    out << "</div>"  << endl;

//    //Ner Properties...
//    out << "<div align=\"center\" id=\"psdg-header\" style=\"float:left\">" << endl;
//    out << "<span class=\"psdg-bold\">NER Global Stats</span>" << endl;
//    out << "</div>" << endl;

    out << "<div class=\"datagrid\">" << endl;
    out << "<div id=\"maincol\"><h2><br>Assessment<br><br></h2></div>" <<  table->getAssessment() << endl;
    out << "</div>" << endl;
    out << "</div> <br>" << endl;

//    out << "<div id=\"psdg-middle\">" << endl;
//    out << "    <div class=\"psdg-left\">NER (&#37;)</div>" << endl;
//    out << "    <div class=\"psdg-right\">" << QString::number(nerData.getNerValue()) << "</div>" << endl;
//    out << "    <div class=\"psdg-left\">Average Delay (s)</div>" << endl;
//    out << "    <div class=\"psdg-right\">" << QString::number(nerData.getAvgDelay())  << "</div>" << endl;
//    out << "    <div class=\"psdg-left\">Text Reduction (&#37;)</div>" << endl;
//    out << "    <div class=\"psdg-right\">" << QString::number(nerData.getReduction())  << "</div>" << endl;
//    out << "</div>" << endl;


    out << "<div class=\"datagrid\">" << endl;
    out << "<div id=\"maincol\"><h2><br> <b> Evaluation Comments </b>  <br><br></h2>" << "</div>" << endl;
    out << "<div class=\"datagrid\"><table class=\"fixed\">" << endl;
    out << "<col width=\"9%\" /> <col width=\"15%\" /> <col width=\"30%\" />" << endl;
    out << "<thead><tr><th>Line #</th><th>Error Type</th><th>Phrase</th><th>Comment</th></tr></thead>" << endl;
    out << "<tbody>" << endl;
    ReportExport::appendTableComments(table, out);
    out << "</tbody>" << endl;
    out << "</table></div></div><br>" << endl;


    out << "<p align=\"left\"><img src=\"" << "data:image/jpg;base64," << imgResName << "\" ></p>" << endl;
    out << "</div>"  << endl;

    out << "</div><br>"  << endl;


    out.flush();
    file.close();
}

void ReportExport::appendTableComments(NERTableWidget *table, QTextStream &out)
{
    for(int i=0; i<table->rowCount(); i++)
    {
        //First get the comments of the transcription...
        DragWidget *dw = static_cast<DragWidget*>(table->cellWidget(i, TRANSCRIPTION_COLUMN_INDEX));
        if(dw==0){
            continue;
        }

        QString comment;
        QString words;
        QList<DragLabel*> labels = dw->getLabels();

        //Only one word
        if(labels.count()==1){
            DragLabel* lab = labels.first();

            if(!lab->getComment().simplified().isEmpty()){
                //Include a new table line with the comments...
                out << "<tr><td>"  << i+1
                    << "</td><td>"<< lab->editionEnumToString(lab->getErrorType())
                    << "</td><td>" << lab->labelText()
                    << "</td><td>" <<  lab->getComment() << "</td></tr>" << endl;
            }

            continue; //to the next block
        }


        for(int j=0; j<labels.count(); j++)
        {

            DragLabel* labLeft = labels.at(j);
            if(labLeft->getErrorType() == CorrectEdition
                    || labLeft->getErrorType() == EditionError
                    || labLeft->getErrorType() == RecognitionError){

                int nextIndex = ReportExport::getIndexForSameError(j, labels);

                for(int k=j; k<=nextIndex; k++){
                    DragLabel* lab = labels.at(k);
                    if(!lab->getComment().isEmpty()){
                        comment.append(lab->getComment()).append("<br>");
                    }
                    words.append(" ").append(lab->labelText());
                }

                //Write to table...
                if(!comment.simplified().isEmpty()){
                    //Include a new table line with the comments...
                    out << "<tr><td> T-"  << i+1
                        << "</td><td>"<< labLeft->editionEnumToString(labLeft->getErrorType())
                        << "</td><td>" << words.simplified()
                        << "</td><td>" <<  comment << "</td></tr>" << endl;
                }
                words.clear();
                comment.clear();

                j=nextIndex;
            }
        }

        //***********************************************
        //Process the corresponding subtable entries...
        //***********************************************
        NERSubTableWidget *subTable = static_cast<NERSubTableWidget*>(table->cellWidget(i, SUBTITLES_COLUMN_INDEX));
        if(subTable==0){
            continue;
        }


        for(int s=0; s<subTable->rowCount(); s++)
        {
            QString commentSub;
            QString words;

            DragWidget *dw = static_cast<DragWidget*>(subTable->cellWidget(s, SUB_SUBTITLES_COLUMN_INDEX));
            if(dw==0){
                continue;
            }

            QList<DragLabel*> labels = dw->getLabels();

            //Only one word
            if(labels.count()==1){
                DragLabel* lab = labels.first();

                if(!lab->getComment().simplified().isEmpty()){
                    //Include a new table line with the comments...
                    out << "<tr><td>"  << i+1
                        << "</td><td bgcolor=#FF00FF>"<< lab->editionEnumToString(lab->getErrorType())
                        << "</td><td>" << lab->labelText()
                        << "</td><td>" <<  lab->getComment() << "</td></tr>" << endl;
                }

                continue; //to the next block
            }


            for(int m=0; m<labels.count(); m++)
            {

                DragLabel* labLeft = labels.at(m);
                if(labLeft->getErrorType() == CorrectEdition
                        || labLeft->getErrorType() == EditionError
                        || labLeft->getErrorType() == RecognitionError){

                    int nextIndexSub = ReportExport::getIndexForSameError(m, labels);

                    for(int k=m; k<=nextIndexSub; k++){
                        DragLabel* lab = labels.at(k);
                        if(!lab->getComment().isEmpty()){
                            commentSub.append(lab->getComment()).append("<br>");
                        }
                        words.append(" ").append(lab->labelText());
                    }

                    //Write to table...
                    if(!commentSub.simplified().isEmpty()){
                        //Include a new table line with the comments...
                        out << "<tr><td> T-"  << i+1 << " | S-" << s+1
                            << "</td><td>"<< labLeft->editionEnumToString(labLeft->getErrorType())
                            << "</td><td>" << words.simplified()
                            << "</td><td>" <<  commentSub << "</td></tr>" << endl;
                    }
                    words.clear();
                    commentSub.clear();

                    m=nextIndexSub;
                }
            }
        }
    }
}

int ReportExport::getIndexForSameError(int i, QList<DragLabel*> labels)
{
    if(i > labels.count()-1 || i<0){
        return -1;
    }

    DragLabel* lab = labels.at(i);

    int finalIndex=i;

    for(int k=i; k<labels.count(); k++)
    {
        DragLabel* nextLab = labels.at(k);
        if(nextLab->getErrorType() == lab->getErrorType()){
            finalIndex = k;
        }
        else{
            return finalIndex;
        }
    }

    return finalIndex;
}

QString ReportExport::ampersand_encode(const QString &string) {
  QString encoded;
  for(int i=0;i<string.size();++i) {
    QChar ch = string.at(i);
    if(ch.unicode() > 255)
      encoded += QString("&#%1;").arg((int)ch.unicode());
    else
      encoded += ch;
  }
  return encoded;
}

void ReportExport::writeFooter(QString &filePath)
{
    if(filePath.isEmpty()){
        //nothing to do...
        return;
    }

    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&file);

    out << "</div>"  << endl;
    out << "</div>"  << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;

    out << "<footer>"
        << "<div id=\"pagewidth\" >" << endl
        << "<div id=\"footer\"><p align=\"left\"><h4> Generated in "
        << QDate::currentDate().toString() << " - "<< QTime::currentTime().toString()
        << "</h4></p></div></div>" << endl
        << "</footer>" << endl;

    out.flush();
    file.close();
}

