#ifndef ACTIONPIPELINE_H
#define ACTIONPIPELINE_H

#include <QString>
#include <QList>
#include <QVariantMap>

enum class ActionType {
    Copy,
    Move,
    Trash,
    Tag,
    CustomCommand,
    Unknown
};

struct FileAction {
    ActionType type{ActionType::Unknown};
    QString name;               // Nome visualizzato dell'azione (es. "Copia", "Tagga", "converti_mp3")
    QString parameter;          // Parametro associato (es. cartella destinazione, nome tag, o comando shell)
    QString rawRepresentation;  // Rappresentazione testuale originale nella pipeline
};

/**
 * @brief Gestisce il parsing e la composizione delle stringhe di azioni concatenate tramite "AND".
 */
class ActionPipeline {
public:

    static QString appendAction(const QString &existingPipeline, const QString &newActionStr);

    static QList<FileAction> parsePipeline(const QString &pipelineStr, const QVariantMap &customCommandsMap = {});

    static QString formatAction(ActionType type, const QString &name, const QString &parameter);

    static QString buildShellCommand(const FileAction &action, const QString &filePath, const QString &destinationDir = QString());
};

#endif // ACTIONPIPELINE_H
