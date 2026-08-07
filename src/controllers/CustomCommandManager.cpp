#include "CustomCommandManager.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

CustomCommandManager::CustomCommandManager(QObject *parent) : QObject(parent) {
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if (configDir.isEmpty()) {
        configDir = QDir::homePath() + QStringLiteral("/.config/dolphin-batch-automation");
    }
    QDir().mkpath(configDir);
    m_configFilePath = configDir + QStringLiteral("/custom_commands.json");

    loadCommands();
}

QStringList CustomCommandManager::savedCommandNames() const {
    return m_commands.keys();
}

QVariantMap CustomCommandManager::getCommandDetails(const QString &name) const {
    QVariantMap map;
    if (m_commands.contains(name)) {
        map.insert(QStringLiteral("name"), name);
        map.insert(QStringLiteral("command"), m_commands.value(name).toString());
    }
    return map;
}

bool CustomCommandManager::saveCustomCommand(const QString &title, const QString &commandStr, bool createAsNewIfModified) {
    QString trimmedTitle = title.trimmed();
    QString trimmedCmd = commandStr.trimmed();

    if (trimmedTitle.isEmpty() || trimmedCmd.isEmpty()) {
        return false;
    }

    if (m_commands.contains(trimmedTitle) && createAsNewIfModified) {
        // Nome già esistente e richiesto come nuovo: restituisce errore (false)
        return false;
    }

    m_commands.insert(trimmedTitle, trimmedCmd);
    saveCommands();
    Q_EMIT commandsChanged();
    return true;
}

bool CustomCommandManager::deleteCustomCommand(const QString &title) {
    if (m_commands.contains(title)) {
        m_commands.remove(title);
        saveCommands();
        Q_EMIT commandsChanged();
        return true;
    }
    return false;
}

QString CustomCommandManager::composeOptionA(const QString &cmd, const QString &attrs, const QString &dest) const {
    // Opzione A: Schema <Comando> <Attributi> <FILE> <Destinazione>
    QString composed = cmd.trimmed();
    if (!attrs.trimmed().isEmpty()) {
        composed += QStringLiteral(" ") + attrs.trimmed();
    }
    composed += QStringLiteral(" <FILE>");
    if (!dest.trimmed().isEmpty()) {
        composed += QStringLiteral(" ") + dest.trimmed();
    }
    return composed;
}

QString CustomCommandManager::composeOptionB(const QString &templateStr) const {
    // Opzione B: Template flessibile con segnaposto
    return templateStr.trimmed();
}

QVariantMap CustomCommandManager::allCommands() const {
    return m_commands;
}

void CustomCommandManager::loadCommands() {
    m_commands.clear();
    QFile file(m_configFilePath);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        if (doc.isObject()) {
            m_commands = doc.object().toVariantMap();
        }
    }

    // Aggiunge comandi di default di esempio se vuoto
    if (m_commands.isEmpty()) {
        m_commands.insert(QStringLiteral("Converti in MP3 (ffmpeg)"), QStringLiteral("ffmpeg -i {file} -b:a 192k {dir}/{name}.mp3"));
        m_commands.insert(QStringLiteral("Comprimi ZIP"), QStringLiteral("zip -r {dir}/{name}.zip {file}"));
        m_commands.insert(QStringLiteral("Calcola Hash SHA256"), QStringLiteral("sha256sum {file} > {dir}/{name}.sha256"));
        saveCommands();
    }
}

void CustomCommandManager::saveCommands() {
    QFile file(m_configFilePath);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject obj = QJsonObject::fromVariantMap(m_commands);
        QJsonDocument doc(obj);
        file.write(doc.toJson());
        file.close();
    }
}
