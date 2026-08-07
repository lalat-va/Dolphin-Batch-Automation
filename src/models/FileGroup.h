#ifndef FILEGROUP_H
#define FILEGROUP_H

#include <QString>
#include <QStringList>

/**
 * @brief Modello per rappresentare un gruppo di file (standard o personalizzato).
 */
class FileGroup {
public:
    FileGroup();
    FileGroup(const QString &id, const QString &name, bool isCustom = false);

    QString groupId() const;
    void setGroupId(const QString &id);

    QString groupName() const;
    void setGroupName(const QString &name);

    bool isCustom() const;
    void setCustom(bool custom);

    QString actionsPipeline() const;
    void setActionsPipeline(const QString &pipeline);

    QStringList filePaths() const;
    void setFilePaths(const QStringList &paths);
    void addFilePath(const QString &path);
    void removeFilePath(const QString &path);

private:
    QString m_groupId;
    QString m_groupName;
    bool m_isCustom{false};
    QString m_actionsPipeline;
    QStringList m_filePaths;
};

#endif // FILEGROUP_H
