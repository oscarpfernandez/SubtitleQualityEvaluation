#include "licencemanager.h"

LicenceManager::LicenceManager(QObject *parent) :
    QObject(parent)
{
}


/*******************************************************************************
 * Installs a new NER llicence file assuming the file  was already checked and
 * validated!
 *
 */
void LicenceManager::installNewLicence(QString &filePath)
{
    if(filePath.isEmpty() || !QFile::exists(filePath)){
        //nothing to do...
        return;
    }

    //home location...
    QString path = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);

    QString fullLicPath = QString(path).append("/").append(STR_LIC_FOLDER);

    QDir dir;
    bool isLicFolderAvailable = dir.exists(fullLicPath);

    //Not available: create folder;
    if(!isLicFolderAvailable){
        dir.mkdir(fullLicPath);
    }

    QString nerLicFile = fullLicPath.append("/").append(STR_LIC_FILE);

    bool isLicFileAvailable = QFile::exists(nerLicFile);

    //copy the new licence file to the default destination
    if(isLicFileAvailable){
        QFile::rename(nerLicFile, nerLicFile.append(".old"));
    }

    QFile::copy(filePath, nerLicFile);//new licence installed

}
