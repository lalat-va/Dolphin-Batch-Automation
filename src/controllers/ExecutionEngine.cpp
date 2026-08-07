#include "ExecutionEngine.h"
#include <QProcess>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QUrl>
#include <QDebug>

ExecutionEngine::ExecutionEngine(QObject *parent) : QObject(parent) {
}

bool ExecutionEngine::isRunning() const {
    return m_isRunning;
}

int ExecutionEngine::totalTasks() const {
    return m_totalTasks;
}

int ExecutionEngine::completedTasks() const {
    return m_completedTasks;
}

double ExecutionEngine::progressFraction() const {
    if (m_totalTasks == 0) return 0.0;
    return static_cast<double>(m_completedTasks) / m_totalTasks;
}

void ExecutionEngine::startExecution(const QList<FileItem> &items, const QVariantMap &customCommandsMap) {
    if (m_isRunning) return;

    m_taskQueue.clear();
    m_logs.clear();
    m_customCommandsMap = customCommandsMap;

    // Costruisce la coda di task da eseguire
    for (const FileItem &item : items) {
        if (item.actionsPipeline().trimmed().isEmpty()) continue;

        QList<FileAction> actions = ActionPipeline::parsePipeline(item.actionsPipeline(), customCommandsMap);
        for (const FileAction &act : actions) {
            m_taskQueue.append({item, act});
        }
    }

    m_totalTasks = m_taskQueue.size();
    m_completedTasks = 0;

    if (m_totalTasks == 0) {
        Q_EMIT executionFinished();
        return;
    }

    m_isRunning = true;
    Q_EMIT runningChanged();
    Q_EMIT progressChanged();

    processNextTask();
}

void ExecutionEngine::cancelExecution() {
    if (!m_isRunning) return;
    m_taskQueue.clear();
    m_isRunning = false;
    Q_EMIT runningChanged();
    Q_EMIT executionFinished();
}

void ExecutionEngine::processNextTask() {
    if (m_taskQueue.isEmpty()) {
        m_isRunning = false;
        Q_EMIT runningChanged();
        Q_EMIT executionFinished();
        return;
    }

    Task task = m_taskQueue.takeFirst();
    executeSingleCommand(task.item.filePath(), task.action);
}

void ExecutionEngine::executeSingleCommand(const QString &filePath, const FileAction &action) {
    QString shellCmd = ActionPipeline::buildShellCommand(action, filePath);
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss"));

    QProcess process;
    process.start(QStringLiteral("sh"), QStringList() << QStringLiteral("-c") << shellCmd);

    bool success = process.waitForFinished(30000); // 30 sec max timeout per azione
    int exitCode = process.exitCode();
    QString stdErr = QString::fromUtf8(process.readAllStandardError()).trimmed();

    ExecutionLogEntry entry;
    entry.timestamp = timestamp;
    entry.filePath = filePath;
    entry.actionName = action.name;
    entry.shellCommand = shellCmd;

    if (success && exitCode == 0) {
        entry.status = QStringLiteral("SUCCESS");
        entry.errorMessage = QString();
        m_logs.append(entry);
        Q_EMIT taskFinished(filePath, action.name, true, QStringLiteral("OK"));
    } else {
        entry.status = QStringLiteral("ERROR");
        entry.errorMessage = stdErr.isEmpty() ? QStringLiteral("Codice errore di sistema: %1").arg(exitCode) : stdErr;
        m_logs.append(entry);
        Q_EMIT taskFinished(filePath, action.name, false, entry.errorMessage);
    }

    m_completedTasks++;
    Q_EMIT progressChanged();

    // Prosegue asincronamente con il prossimo task (tolleranza agli errori)
    QMetaObject::invokeMethod(this, &ExecutionEngine::processNextTask, Qt::QueuedConnection);
}

bool ExecutionEngine::exportLogToCsv(const QString &targetCsvPath) {
    if (targetCsvPath.isEmpty()) return false;

    QString cleanPath = targetCsvPath;
    if (cleanPath.startsWith(QStringLiteral("file://"))) {
        cleanPath = QUrl(targetCsvPath).toLocalFile();
    }

    QFile file(cleanPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    // Intestazione CSV
    out << "\"Timestamp\",\"FilePath\",\"ActionName\",\"ExecutedShellCommand\",\"Status\",\"ErrorMessage\"\n";

    for (const ExecutionLogEntry &log : m_logs) {
        auto esc = [](const QString &str) {
            QString s = str;
            s.replace(QStringLiteral("\""), QStringLiteral("\"\""));
            return QStringLiteral("\"%1\"").arg(s);
        };

        out << esc(log.timestamp) << ","
            << esc(log.filePath) << ","
            << esc(log.actionName) << ","
            << esc(log.shellCommand) << ","
            << esc(log.status) << ","
            << esc(log.errorMessage) << "\n";
    }

    file.close();
    return true;
}
