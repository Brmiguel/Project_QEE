#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

#include "bluetooth.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    qmlRegisterType<Bluetooth>("bluetooth",1,0,"Bluetooth"); // Name to use inside qml "Bluetooth"

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
