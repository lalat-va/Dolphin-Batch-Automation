#include "FileAutomationController.h"
#include <QDirIterator>
#include <QMimeDatabase>
#include <QMimeType>
#include <QDateTime>
#include <QFileInfo>
#include <QUrl>
#include <QDebug>

FileAutomationController::FileAutomationController(QObject *parent)
    : QObject(parent), m_groupRule(QStringLiteral("mime")) {
    connect(&m_executionEngine, &ExecutionEngine::executionFinished, this, &FileAutomationController::reloadView);
}

QString FileAutomationController::currentDirectory() const {
    return m_currentDirectory;
}

void FileAutomationController::setCurrentDirectory(const QString &dirPath) {
    QString cleanPath = dirPath;
    if (cleanPath.startsWith(QStringLiteral("file://"))) {
        cleanPath = QUrl(dirPath).toLocalFile();
    }

    if (m_currentDirectory != cleanPath) {
        m_currentDirectory = cleanPath;
        Q_EMIT currentDirectoryChanged();
        scanDirectory(m_currentDirectory);
    }
}

bool FileAutomationController::isRecursive() const {
    return m_isRecursive;
}

void FileAutomationController::setRecursive(bool recursive) {
    if (m_isRecursive != recursive) {
        m_isRecursive = recursive;
        Q_EMIT recursiveChanged();
        scanDirectory(m_currentDirectory);
    }
}

FileListModel* FileAutomationController::fileModel() {
    return &m_fileModel;
}

TagManager* FileAutomationController::tagManager() {
    return &m_tagManager;
}

CustomCommandManager* FileAutomationController::customCommandManager() {
    return &m_customCommandManager;
}

ExecutionEngine* FileAutomationController::executionEngine() {
    return &m_executionEngine;
}

QVariantList FileAutomationController::groups() const {
    QVariantList list;

    // Aggiunge prima i gruppi personalizzati
    for (const FileGroup &g : m_customGroups) {
        QVariantMap map;
        map.insert(QStringLiteral("groupId"), g.groupId());
        map.insert(QStringLiteral("groupName"), QString(g.groupName() + QStringLiteral(" (Personalizzato)")));
        map.insert(QStringLiteral("isCustom"), true);
        map.insert(QStringLiteral("actionsPipeline"), g.actionsPipeline());
        map.insert(QStringLiteral("fileCount"), g.filePaths().size());
        list.append(map);
    }

    // Aggiunge poi i gruppi standard
    for (const FileGroup &g : m_standardGroups) {
        QVariantMap map;
        map.insert(QStringLiteral("groupId"), g.groupId());
        map.insert(QStringLiteral("groupName"), g.groupName());
        map.insert(QStringLiteral("isCustom"), false);
        map.insert(QStringLiteral("actionsPipeline"), g.actionsPipeline());
        map.insert(QStringLiteral("fileCount"), g.filePaths().size());
        list.append(map);
    }

    return list;
}

void FileAutomationController::scanDirectory(const QString &dirPath) {
    QString path = dirPath.isEmpty() ? m_currentDirectory : dirPath;
    if (path.isEmpty()) return;

    QDir dir(path);
    if (!dir.exists()) return;

    QList<FileItem> fileList;
    QMimeDatabase mimeDb;

    QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags;
    if (m_isRecursive) {
        flags |= QDirIterator::Subdirectories;
    }

    QDirIterator it(path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, flags);

    while (it.hasNext()) {
        it.next();
        QFileInfo info = it.fileInfo();

        FileItem item(info.absoluteFilePath(), info.isDir());
        QMimeType mime = mimeDb.mimeTypeForFile(info);
        item.setMimeType(mime.name());

        // Recupera tag xattr
        item.setTags(m_tagManager.getFileTags(info.absoluteFilePath()));

        fileList.append(item);
    }

    m_fileModel.setFiles(fileList);
    rebuildGroups();
}

void FileAutomationController::setGroupRule(const QString &rule) {
    if (m_groupRule != rule) {
        m_groupRule = rule;
        rebuildGroups();
    }
}

bool FileAutomationController::createCustomGroup(const QString &groupName) {
    if (groupName.trimmed().isEmpty()) return false;

    QStringList selectedPaths = m_fileModel.selectedFilePaths();
    if (selectedPaths.isEmpty()) return false;

    QString groupId = QStringLiteral("custom_%1").arg(m_customGroups.size() + 1);
    FileGroup newCustomGroup(groupId, groupName.trimmed(), true);
    newCustomGroup.setFilePaths(selectedPaths);

    // Assegna il customGroupId a ciascun file selezionato nel modello
    QList<FileItem> items = m_fileModel.files();
    for (int i = 0; i < items.size(); ++i) {
        if (selectedPaths.contains(items[i].filePath())) {
            items[i].setCustomGroupId(groupId);
            items[i].setSelected(false); // Resetta selezione dopo associazione
        }
    }
    m_fileModel.setFiles(items);

    m_customGroups.append(newCustomGroup);
    rebuildGroups();
    return true;
}

void FileAutomationController::rebuildGroups() {
    m_standardGroups.clear();
    QMap<QString, FileGroup> groupMap;
    QList<FileItem> items = m_fileModel.files();

    for (const FileItem &item : items) {
        // I file inseriti in un gruppo personalizzato vengono ESCLUSI dai gruppi standard
        if (!item.customGroupId().isEmpty()) {
            continue;
        }

        QString key;
        QString name;

        if (m_groupRule == QStringLiteral("mime")) {
            key = item.mimeType();
            name = QStringLiteral("MIME: %1").arg(key);
        } else if (m_groupRule == QStringLiteral("folder")) {
            QFileInfo info(item.filePath());
            key = info.absolutePath();
            name = QStringLiteral("Cartella: %1").arg(info.dir().dirName());
        } else if (m_groupRule == QStringLiteral("date")) {
            QString dateStr = item.modifiedDate().toString(QStringLiteral("yyyy-MM-dd"));
            key = dateStr;
            name = QStringLiteral("Data: %1").arg(dateStr);
        } else {
            key = QStringLiteral("tutti");
            name = QStringLiteral("Tutti i File");
        }

        if (!groupMap.contains(key)) {
            groupMap.insert(key, FileGroup(key, name, false));
        }
        groupMap[key].addFilePath(item.filePath());
    }

    m_standardGroups = groupMap.values();
    Q_EMIT groupsChanged();
}

void FileAutomationController::applyGroupPipelineToFiles(int groupIndex, const QString &pipeline) {
    QVariantList gList = groups();
    if (groupIndex < 0 || groupIndex >= gList.size()) return;

    QVariantMap gMap = gList.at(groupIndex).toMap();
    QString groupId = gMap.value(QStringLiteral("groupId")).toString();

    // Trova i file appartenenti a questo gruppo
    QStringList paths;
    if (gMap.value(QStringLiteral("isCustom")).toBool()) {
        for (const FileGroup &g : m_customGroups) {
            if (g.groupId() == groupId) {
                paths = g.filePaths();
                break;
            }
        }
    } else {
        for (const FileGroup &g : m_standardGroups) {
            if (g.groupId() == groupId) {
                paths = g.filePaths();
                break;
            }
        }
    }

    // Applica o concatena la pipeline di azioni a tutti i file appartenenti al gruppo
    QList<FileItem> items = m_fileModel.files();
    for (int i = 0; i < items.size(); ++i) {
        if (paths.contains(items[i].filePath())) {
            QString current = items[i].actionsPipeline();
            QString updated = current.trimmed().isEmpty() ? pipeline : current.trimmed() + QStringLiteral(" AND ") + pipeline;
            items[i].setActionsPipeline(updated);
        }
    }
    m_fileModel.setFiles(items);
}

void FileAutomationController::clearAllActions() {
    QList<FileItem> items = m_fileModel.files();
    for (int i = 0; i < items.size(); ++i) {
        items[i].setActionsPipeline(QString());
    }
    m_fileModel.setFiles(items);

    for (int i = 0; i < m_customGroups.size(); ++i) {
        m_customGroups[i].setActionsPipeline(QString());
    }
    for (int i = 0; i < m_standardGroups.size(); ++i) {
        m_standardGroups[i].setActionsPipeline(QString());
    }
    Q_EMIT groupsChanged();
}

void FileAutomationController::reloadView() {
    scanDirectory(m_currentDirectory);
}
