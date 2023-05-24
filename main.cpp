#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <imageorientation.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/RotateImage/Main.qml"_qs);

    qmlRegisterType<ImageOrientation>("ImageOrientationpackage",1,0,"ImageOrientation");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
