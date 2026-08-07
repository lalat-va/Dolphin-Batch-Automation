#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QDir>
#include <QUrl>
#include <KLocalizedString>
#include <KAboutData>

#include "controllers/FileAutomationController.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("dolphin-batch-automation");

    KAboutData aboutData(
        QStringLiteral("dolphin-batch-automation"),
        i18n("Automazione File Massiva Dolphin"),
        QStringLiteral("1.0.0"),
        i18n("Componente aggiuntivo per KDE Dolphin per l'automazione massiva di azioni sui file."),
        KAboutLicense::GPL_V3,
        i18n("(c) 2026 KDE Community")
    );

    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);
    parser.addPositionalArgument(QStringLiteral("directory"), i18n("Cartella o file su cui operare"));
    parser.process(app);

    QString targetPath = QDir::currentPath();
    const QStringList posArgs = parser.positionalArguments();
    if (!posArgs.isEmpty()) {
        targetPath = posArgs.first();
    }

    QQmlApplicationEngine engine;

    FileAutomationController controller;
    controller.setCurrentDirectory(targetPath);

    engine.rootContext()->setContextProperty(QStringLiteral("controller"), &controller);
    engine.rootContext()->setContextProperty(QStringLiteral("fileModel"), controller.fileModel());
    engine.rootContext()->setContextProperty(QStringLiteral("tagManager"), controller.tagManager());
    engine.rootContext()->setContextProperty(QStringLiteral("customCommandManager"), controller.customCommandManager());
    engine.rootContext()->setContextProperty(QStringLiteral("executionEngine"), controller.executionEngine());

    const QUrl url(QStringLiteral("qrc:/src/ui/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
