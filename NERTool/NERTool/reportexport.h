#ifndef REPORTEXPORT_H
#define REPORTEXPORT_H

#include "nercommon.h"
#include <QDir>

class ReportExport
{
public:
    ReportExport();
    static void generateExportFile(QString &filePath,
                                   QString &imgResName,
                                   NERStatsData nerData,
                                   QString name,
                                   QString resp,
                                   QString desc);
};

#endif // REPORTEXPORT_H
