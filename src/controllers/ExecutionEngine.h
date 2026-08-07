#ifndef EXECUTIONENGINE_H
#define EXECUTIONENGINE_H

#include <QObject>
#include <QList>
#include <QVariantMap>
#include "../models/FileItem.h"
#include "../models/ActionPipeline.h"

struct ExecutionLogEntry {
    QString timestamp;
    QString filePath;
    QString actionName;
    QString shellCommand;
    QString status; // "SUCCESS" o "ERROR"
    QString errorMessage;
};

/**
 * @brief Motore di esecuzione asincrona delle azioni sui file con esportazione log CSV.
 */
class ExecutionEngine : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY runningChanged)
    Q_PROPERTY(int totalTasks READ totalTasks NOTIFY progressChanged)
    Q_PROPERTY(int completedTasks READ completedTasks NOTIFY progressChanged)
    Q_PROPERTY(double progressFraction READ progressFraction NOTIFY progressChanged)

public:
    explicit ExecutionEngine(QObject *parent = nullptr);

    bool isRunning() const;
    int totalTasks() const;
    int completedTasks() const;
    double progressFraction() const;

    Q_INVOKABLE void startExecution(const QList<FileItem> &items, const QVariantMap &customCommandsMap);
    Q_INVOKABLE void cancelExecution();
    Q_INVOKABLE bool exportLogToCsv(const QString &targetCsvPath);

Q_SIGNALS:
    void runningChanged();
    void progressChanged();
    void taskFinished(const QString &filePath, const QString &actionName, bool success, const QString &message);
    void executionFinished();

private:
    void processNextTask();
    void executeSingleCommand(const QString &filePath, const FileAction &action);

    bool m_isRunning{false};
    int m_totalTasks{0};
    int m_completedTasks{0};

    struct Task {
        FileItem item;
        FileAction action;
    };

    QList<Task> m_taskQueue;
    QList<ExecutionLogEntry> m_logs;
    QVariantMap m_customCommandsMap;
};

#endif // EXECUTIONENGINE_H
