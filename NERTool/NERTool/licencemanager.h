#ifndef LICENCEMANAGER_H
#define LICENCEMANAGER_H

#include <QObject>
#include <QDesktopServices>
#include <QDir>

const QString STR_LIC_FILE = "ner_licence.lic";
const QString STR_LIC_FOLDER = ".nertool";

class LicenceManager : public QObject
{
    Q_OBJECT
public:
    explicit LicenceManager(QObject *parent = 0);
    void installNewLicence(QString &filePath);
    
};

#endif // LICENCEMANAGER_H
