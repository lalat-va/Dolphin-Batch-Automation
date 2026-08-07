#ifndef CUSTOMCOMMANDMANAGER_H
#define CUSTOMCOMMANDMANAGER_H

#include <QObject>
#include <QVariantMap>
#include <QStringList>

/**
 * @brief Controller per la gestione e la persistenza dei comandi personalizzati (Opzione A e Opzione B).
 */
class CustomCommandManager : public QObject {
    Q_OBJECT

public:
    explicit CustomCommandManager(QObject *parent = nullptr);

    Q_INVOKABLE QStringList savedCommandNames() const;

    Q_INVOKABLE QVariantMap getCommandDetails(const QString &name) const;

    Q_INVOKABLE bool saveCustomCommand(const QString &title, const QString &commandStr, bool createAsNewIfModified = true);

    Q_INVOKABLE bool deleteCustomCommand(const QString &title);

    Q_INVOKABLE QString composeOptionA(const QString &cmd, const QString &attrs, const QString &dest) const;

    Q_INVOKABLE QString composeOptionB(const QString &templateStr) const;

    Q_INVOKABLE QVariantMap allCommands() const;

Q_SIGNALS:
    void commandsChanged();

private:
    void loadCommands();
    void saveCommands();

    QVariantMap m_commands; // Titolo -> Template Comando Shell
    QString m_configFilePath;
};

#endif // CUSTOMCOMMANDMANAGER_H
