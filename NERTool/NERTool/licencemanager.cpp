#include "licencemanager.h"

LicenceManager::LicenceManager(QObject *parent) :
    QObject(parent)
{
//    ntpClient = new NtpClient();
//    connect(ntpClient, SIGNAL(replyReceived(QHostAddress,quint16,NtpReply)),
//                              this, SLOT(replyReceived(QHostAddress,quint16,NtpReply)));
}

LicenceManager::~LicenceManager()
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
        QFile::remove(nerLicFile);
    }

    QFile::copy(filePath, nerLicFile);//new licence installed

}

LIC_ERROR_TYPE LicenceManager::checkLicence()
{
    //home location...
    QString path = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);

    QString licPath = QString(path).append("/").append(STR_LIC_FOLDER)
            .append("/").append(STR_LIC_FILE);


    if(!QFile::exists(licPath)){
        return LIC_UNDEF_ERROR;
    }

    QString xml = Utils::readLicenceFile(licPath);

    if(xml.isEmpty()){
        return LIC_INVALID_FILE;
    }

    QString user, org, macAddress;
    QDate startDate, finishDate;
    Utils::fromXML(xml, user, org, macAddress, startDate, finishDate);

    licenceData.user = user;
    licenceData.org = org;
    licenceData.mac = macAddress;
    licenceData.startDate = startDate;
    licenceData.finishDate = finishDate;


    /*
     *QHostInfo addInfo = QHostInfo::fromName("46.16.60.129");

    QList<QHostAddress> list = addInfo.addresses();
    if(list.count()==0){
        return false;
    }

    QHostAddress ntpAddress("46.16.60.129");
    ntpClient = new NtpClient(ntpAddress,(qint16)123 );
    connect(ntpClient, SIGNAL(replyReceived(QHostAddress,quint16,NtpReply)),
                              this, SLOT(replyReceived(QHostAddress,quint16,NtpReply)));
    ntpClient->sendRequest(ntpAddress, (qint16)123);
    */
    QDate currentDate = QDate::currentDate();
    if(!(currentDate>=startDate && currentDate<=finishDate)){
        return LIC_INVALID_TIME;
    }



    QList<QString> macs = Utils::getMachinesMACAddresses();

    if(!macs.contains(macAddress.toLower().replace("-",":"))){
        return LIC_INVALID_MAC_ADDRESS;
    }

    return LIC_NO_ERROR;

}


LicenceData LicenceManager::getLicenceInfo()
{
    return licenceData;
}
