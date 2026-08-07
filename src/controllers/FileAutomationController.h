#ifndef FILEAUTOMATIONCONTROLLER_H
#define FILEAUTOMATIONCONTROLLER_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include "../models/FileListModel.h"
#include "../models/FileGroup.h"
#include "TagManager.h"
#include "CustomCommandManager.h"
#include "ExecutionEngine.h"

/**
 * @brief Controller principale dell'applicazione che coordina modello, raggruppamenti ed esecuzione.
 */
class FileAutomationController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentDirectory READ currentDirectory WRITE setCurrentDirectory NOTIFY currentDirectoryChanged)
    Q_PROPERTY(bool isRecursive READ isRecursive WRITE setRecursive NOTIFY recursiveChanged)
    Q_PROPERTY(FileListModel* fileModel READ fileModel CONSTANT)
    Q_PROPERTY(TagManager* tagManager READ tagManager CONSTANT)
    Q_PROPERTY(CustomCommandManager* customCommandManager READ customCommandManager CONSTANT)
    Q_PROPERTY(ExecutionEngine* executionEngine READ executionEngine CONSTANT)
    Q_PROPERTY(QVariantList groups READ groups NOTIFY groupsChanged)

public:
    explicit FileAutomationController(QObject *parent = nullptr);

    QString currentDirectory() const;
    void setCurrentDirectory(const QString &dirPath);

    bool isRecursive() const;
    void setRecursive(bool recursive);

    FileListModel* fileModel();
    TagManager* tagManager();
    CustomCommandManager* customCommandManager();
    ExecutionEngine* executionEngine();

    QVariantList groups() const;

    Q_INVOKABLE void scanDirectory(const QString &dirPath = QString());
    Q_INVOKABLE void setGroupRule(const QString &rule); // "mime", "folder", "date"
    Q_INVOKABLE bool createCustomGroup(const QString &groupName);
    Q_INVOKABLE void applyGroupPipelineToFiles(int groupIndex, const QString &pipeline);
    Q_INVOKABLE void clearAllActions();
    Q_INVOKABLE void reloadView();

Q_SIGNALS:
    void currentDirectoryChanged();
    void recursiveChanged();
    void groupsChanged();

private:
    void rebuildGroups();

    QString m_currentDirectory;
    bool m_isRecursive{false};
    QString m_groupRule; // Initialized in constructor

    FileListModel m_fileModel;
    TagManager m_tagManager;
    CustomCommandManager m_customCommandManager;
    ExecutionEngine m_executionEngine;

    QList<FileGroup> m_customGroups;
    QList<FileGroup> m_standardGroups;
};

#endif // FILEAUTOMATIONCONTROLLER_H
