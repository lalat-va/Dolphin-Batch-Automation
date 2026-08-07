#include "ActionPipeline.h"
#include <QFileInfo>
#include <QDateTime>
#include <QRegularExpression>
#include <QDir>

QString ActionPipeline::appendAction(const QString &existingPipeline, const QString &newActionStr) {
    QString trimmed = existingPipeline.trimmed();
    if (trimmed.isEmpty()) {
        return newActionStr;
    }
    return trimmed + QStringLiteral(" AND ") + newActionStr;
}

QList<FileAction> ActionPipeline::parsePipeline(const QString &pipelineStr, const QVariantMap &customCommandsMap) {
    QList<FileAction> actions;
    if (pipelineStr.trimmed().isEmpty()) {
        return actions;
    }

    // Split in base alla parola chiave " AND " (case insensitive, con spazi)
    QStringList rawSegments = pipelineStr.split(QRegularExpression(QStringLiteral("\\s+AND\\s+"), QRegularExpression::CaseInsensitiveOption), Qt::SkipEmptyParts);

    for (const QString &segment : rawSegments) {
        QString trimmed = segment.trimmed();
        FileAction action;
        action.rawRepresentation = trimmed;

        if (trimmed.startsWith(QStringLiteral("Copia"), Qt::CaseInsensitive)) {
            action.type = ActionType::Copy;
            action.name = QStringLiteral("Copia");
            QRegularExpression re(QStringLiteral("Copia\\s*\\((.*)\\)"), QRegularExpression::CaseInsensitiveOption);
            auto match = re.match(trimmed);
            if (match.hasMatch()) {
                action.parameter = match.captured(1).trimmed();
            }
        } else if (trimmed.startsWith(QStringLiteral("Sposta"), Qt::CaseInsensitive)) {
            action.type = ActionType::Move;
            action.name = QStringLiteral("Sposta");
            QRegularExpression re(QStringLiteral("Sposta\\s*\\((.*)\\)"), QRegularExpression::CaseInsensitiveOption);
            auto match = re.match(trimmed);
            if (match.hasMatch()) {
                action.parameter = match.captured(1).trimmed();
            }
        } else if (trimmed.startsWith(QStringLiteral("Cancella"), Qt::CaseInsensitive)) {
            action.type = ActionType::Trash;
            action.name = QStringLiteral("Cancella");
        } else if (trimmed.startsWith(QStringLiteral("Tagga"), Qt::CaseInsensitive)) {
            action.type = ActionType::Tag;
            action.name = QStringLiteral("Tagga");
            QRegularExpression re(QStringLiteral("Tagga\\s*\\((.*)\\)"), QRegularExpression::CaseInsensitiveOption);
            auto match = re.match(trimmed);
            if (match.hasMatch()) {
                action.parameter = match.captured(1).trimmed();
            }
        } else {
            // È un comando personalizzato o sconosciuto
            action.type = ActionType::CustomCommand;
            action.name = trimmed;
            if (customCommandsMap.contains(trimmed)) {
                action.parameter = customCommandsMap.value(trimmed).toString();
            } else {
                action.parameter = trimmed;
            }
        }

        actions.append(action);
    }

    return actions;
}

QString ActionPipeline::formatAction(ActionType type, const QString &name, const QString &parameter) {
    switch (type) {
    case ActionType::Copy:
        return QStringLiteral("Copia (%1)").arg(parameter);
    case ActionType::Move:
        return QStringLiteral("Sposta (%1)").arg(parameter);
    case ActionType::Trash:
        return QStringLiteral("Cancella");
    case ActionType::Tag:
        return QStringLiteral("Tagga (%1)").arg(parameter);
    case ActionType::CustomCommand:
        return name; // Mostra il titolo del comando personalizzato
    default:
        return name;
    }
}

QString ActionPipeline::buildShellCommand(const FileAction &action, const QString &filePath, const QString &destinationDir) {
    QFileInfo info(filePath);
    QString escPath = QStringLiteral("\"%1\"").arg(filePath);

    switch (action.type) {
    case ActionType::Copy: {
        QString targetDir = action.parameter.isEmpty() ? destinationDir : action.parameter;
        if (targetDir.isEmpty()) targetDir = info.absolutePath();
        return QStringLiteral("cp -r %1 \"%2\"").arg(escPath, QDir::cleanPath(targetDir));
    }
    case ActionType::Move: {
        QString targetDir = action.parameter.isEmpty() ? destinationDir : action.parameter;
        if (targetDir.isEmpty()) targetDir = info.absolutePath();
        return QStringLiteral("mv %1 \"%2\"").arg(escPath, QDir::cleanPath(targetDir));
    }
    case ActionType::Trash: {
        // Usa trash-cli (trash-put) come specificato nelle dipendenze forti
        return QStringLiteral("trash-put %1").arg(escPath);
    }
    case ActionType::Tag: {
        // Sintassi setfattr per attributi estesi XDG usati da Baloo/Plasma 6
        QString tags = action.parameter;
        return QStringLiteral("setfattr -n user.xdg.tags -v \"%1\" %2").arg(tags, escPath);
    }
    case ActionType::CustomCommand: {
        QString tmpl = action.parameter;
        // Se il template contiene segnaposto come {file}, {name}, {ext}, {dir}, {date}
        if (tmpl.contains(QStringLiteral("{file}")) || tmpl.contains(QStringLiteral("{name}")) || tmpl.contains(QStringLiteral("{ext}")) || tmpl.contains(QStringLiteral("{dir}"))) {
            tmpl.replace(QStringLiteral("{file}"), escPath);
            tmpl.replace(QStringLiteral("{name}"), QStringLiteral("\"%1\"").arg(info.completeBaseName()));
            tmpl.replace(QStringLiteral("{ext}"), QStringLiteral("\"%1\"").arg(info.suffix()));
            tmpl.replace(QStringLiteral("{dir}"), QStringLiteral("\"%1\"").arg(info.absolutePath()));
            tmpl.replace(QStringLiteral("{date}"), QStringLiteral("\"%1\"").arg(info.lastModified().toString(QStringLiteral("yyyy-MM-dd"))));
            tmpl.replace(QStringLiteral("{dest}"), action.parameter.isEmpty() ? QStringLiteral("\"%1\"").arg(destinationDir) : QStringLiteral("\"%1\"").arg(action.parameter));
            return tmpl;
        } else if (tmpl.contains(QStringLiteral("<FILE>"))) {
            tmpl.replace(QStringLiteral("<FILE>"), escPath);
            return tmpl;
        } else {
            // Modalità semplice o stringa generica: appendi il file se non è presente
            if (!tmpl.contains(filePath)) {
                return QStringLiteral("%1 %2").arg(tmpl, escPath);
            }
            return tmpl;
        }
    }
    default:
        return QStringLiteral("echo \"Azione non valida: %1\"").arg(action.name);
    }
}
