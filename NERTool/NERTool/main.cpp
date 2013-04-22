#include <qapplication.h>
#include <QSplashScreen>
#include "nermainwindow.h"
#include "sleeper.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resource_items);

    QApplication app(argc, argv);
    app.setOrganizationName("CAIAC");
    app.setApplicationName("NER Tool");
    app.setApplicationVersion("1.0");
    app.setWindowIcon(QIcon(":/resources/pics/icon.png"));
    NERMainWindow mainWin;

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resources/pics/splash2.png"));
    splash->show();
    Qt::Alignment topRight = Qt::AlignLeft | Qt::AlignTop;
    splash->showMessage(QObject::tr("Loading Application..."),
                        topRight, Qt::white);

    Sleeper::sleep(2000);

    mainWin.showMaximized();
    splash->finish(&mainWin);

    //Check if the licence is still OK!
    LIC_ERROR_TYPE error = mainWin.checkLicence();
    if(error != LIC_NO_ERROR){
        mainWin.displayErrorMessage(error);
        return 0;//No licence, no show!
    }

    return app.exec();
}
