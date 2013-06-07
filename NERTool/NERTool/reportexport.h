#ifndef REPORTEXPORT_H
#define REPORTEXPORT_H

#include "nercommon.h"
#include <QDir>
#include "utils.h"

class ReportExport
{
public:
    ReportExport();
    static void writeHeader(QString &filePath);
    static void generateExportFile(QString &filePath,
                                   QString &imgResName,
                                   NERStatsData nerData,
                                   QString name,
                                   QString resp,
                                   QString desc);
    static void writeFooter(QString &filePath);
};

#endif // REPORTEXPORT_H
