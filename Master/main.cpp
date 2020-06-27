#include <QCoreApplication>
#include <QCommandLineParser>
#include <QtDebug>
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("collector");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCommandLineParser parser;
    parser.setApplicationDescription("LAN Device Information Collector");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption masterOption("m", QCoreApplication::translate("main", "Master mode"));
    parser.addOption(masterOption);
    //// Process the actual command line arguments given by the user
    parser.process(app);
    bool masterMode = parser.isSet(masterOption);
    qDebug() << "master Mode : " << masterMode;
    if(masterMode){

    }

    return app.exec();
}
