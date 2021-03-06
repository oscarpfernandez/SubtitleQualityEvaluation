#ifndef REPORTEXPORT_H
#define REPORTEXPORT_H

#include "nercommon.h"
#include <QDir>
#include "utils.h"
#include "nertablewidget.h"

class ReportExport
{
public:
    ReportExport();
    static void writeHeader(QString &filePath);
    static void generateExportFile(QString &filePath,
                                   QString &imgResName,
                                   NERTableWidget *table);
    static void writeFooter(QString &filePath);
    static void appendTableComments(NERTableWidget *table, QTextStream &out);
    static QString ampersand_encode(const QString& str);
    static int getIndexForSameError(int i, QList<DragLabel*> labels);
};

#endif // REPORTEXPORT_H
