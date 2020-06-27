#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QCommandLineParser>
#include "infomodel.h"
#include "infomanager.h"
#include <thread>
void qmlRegister(){
    qmlRegisterSingletonType<InfoModel>("Collector", 1, 0, "InfoModel", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)Q_UNUSED(scriptEngine)return SInfoModel::instance();
    });
}
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QCoreApplication::setOrganizationName("ZJUNlict");
    QCoreApplication::setApplicationName("collector");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCommandLineParser parser;
    parser.setApplicationDescription("LAN Device Information Collector");
    parser.addHelpOption();
    parser.addVersionOption();

    // register for qml
    qmlRegister();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    InfoManager im("233.233.233.233",23233);
    std::thread t([&]{
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        for(int i=0;i<10;i++){
            im.manualAdd(i,"fake.");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        im.manualAdd(300,"fake.");
        for(;;){
            for(int i=0;i<5;i++){
                im.manualAdd(i*2,"fakefake.");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    });
    t.detach();
    return app.exec();
}
