#ifndef FILEITEM_H
#define FILEITEM_H

#include <QString>
#include <QDateTime>
#include <QStringList>

/**
 * @brief Modello per rappresentare un singolo file o sottocartella nell'applicazione.
 */
class FileItem {
public:
    FileItem();
    FileItem(const QString &path, bool isDirectory = false);

    QString filePath() const;
    void setFilePath(const QString &path);

    QString fileName() const;
    bool isDir() const;
    qint64 fileSize() const;
    void setFileSize(qint64 size);

    QString mimeType() const;
    void setMimeType(const QString &mime);

    QDateTime modifiedDate() const;
    void setModifiedDate(const QDateTime &dt);

    QDateTime createdDate() const;
    void setCreatedDate(const QDateTime &dt);

    QString actionsPipeline() const;
    void setActionsPipeline(const QString &pipeline);

    QString customGroupId() const;
    void setCustomGroupId(const QString &groupId);

    QStringList tags() const;
    void setTags(const QStringList &tags);

    bool isSelected() const;
    void setSelected(bool selected);

private:
    QString m_filePath;
    QString m_fileName;
    bool m_isDir{false};
    qint64 m_fileSize{0};
    QString m_mimeType{QStringLiteral("application/octet-stream")};
    QDateTime m_modifiedDate;
    QDateTime m_createdDate;
    QString m_actionsPipeline;
    QString m_customGroupId;
    QStringList m_tags;
    bool m_selected{false};
};

#endif // FILEITEM_H
