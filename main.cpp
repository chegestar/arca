#include <QtGui/QApplication>
#include <QtDeclarative>
#include <QtServiceFramework/QServiceManager>
#include "qmlapplicationviewer.h"
#include "dbsession.h"
#include "dbrestclient.h"
#include "apikeys.h"

QTM_USE_NAMESPACE

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Synchroma");
    QCoreApplication::setOrganizationDomain("synchroma.com.au");
    QCoreApplication::setApplicationName("Arca");

    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QmlApplicationViewer viewer;

    QDeclarativeEngine *engine = viewer.engine();
    QDeclarativeContext *context = engine->rootContext();

    DBSession session;
    session.setConsumerKey(DROPBOX_APP_KEY);
    session.setConsumerSecret(DROPBOX_APP_SECRET);

    // Have the REST client visible in the QML
    DBRestClient restClient(session);
    context->setContextProperty("restClient", &restClient);

    // TESTING
    context->setContextProperty("param", QString(argv[1]));

    // TESTING
    qDebug() << "temp dir: " << QDir::tempPath();
    qDebug() << "home dir: " << QDir::homePath();
    qDebug() << "current dir: " << QDir::currentPath();

    QServiceManager serviceManager(QService::SystemScope);
    QStringList stringList = serviceManager.findServices();
    foreach (QString interfaceName, stringList)
        qDebug() << "service interface: " << interfaceName;

    QList<QServiceInterfaceDescriptor> descriptors = serviceManager.findInterfaces();
    for (int i=0; i<descriptors.count(); i++)
    {
        QString service = descriptors[i].serviceName();

        if (descriptors[i].scope() == QService::SystemScope)
            service += " (system)";

        qDebug() << "service: " << service;
    }

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/arca/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
