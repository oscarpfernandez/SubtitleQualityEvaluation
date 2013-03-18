#include "utils.h"

Utils::Utils(QObject *parent) :
    QObject(parent)
{
}


void Utils::generateLicenceFile(QString &licenceFile,
                                QString &user,
                                QString &org,
                                QString &mac,
                                QDate &startDate,
                                QDate &finishDate)
{
    if(user.isEmpty() || org.isEmpty() || mac.isEmpty()){
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setText("Input data is not valid!                                ");
        box.setInformativeText("Some of the required values are empty.       ");
        box.exec();

        return;
    }

    if(startDate.daysTo(finishDate) <=0 ){
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setText("Invalid date information!                                 ");
        box.setInformativeText("The date information provided is inconsistent. ");
        box.exec();

        return;
    }

    QFile file(licenceFile);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    // Write a header with a "magic number" and a version
    out << (quint32)0xAABBCCDD;
    out << (qint32)23;

    out.setVersion(QDataStream::Qt_4_0);

    // Write the data
    out << user.count();
    out << user;
    out << org.count();
    out << org;
    out << mac.count();
    out << mac;

    file.close();
}
