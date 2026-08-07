#include "FileItem.h"
#include <QFileInfo>

FileItem::FileItem() {
}

FileItem::FileItem(const QString &path, bool isDirectory)
    : m_filePath(path), m_isDir(isDirectory) {
    QFileInfo info(path);
    m_fileName = info.fileName();
    if (m_fileName.isEmpty()) {
        m_fileName = path;
    }
    m_fileSize = info.size();
    m_modifiedDate = info.lastModified();
    m_createdDate = info.birthTime().isValid() ? info.birthTime() : info.lastModified();
}

QString FileItem::filePath() const {
    return m_filePath;
}

void FileItem::setFilePath(const QString &path) {
    m_filePath = path;
    QFileInfo info(path);
    m_fileName = info.fileName();
}

QString FileItem::fileName() const {
    return m_fileName;
}

bool FileItem::isDir() const {
    return m_isDir;
}

qint64 FileItem::fileSize() const {
    return m_fileSize;
}

void FileItem::setFileSize(qint64 size) {
    m_fileSize = size;
}

QString FileItem::mimeType() const {
    return m_mimeType;
}

void FileItem::setMimeType(const QString &mime) {
    m_mimeType = mime;
}

QDateTime FileItem::modifiedDate() const {
    return m_modifiedDate;
}

void FileItem::setModifiedDate(const QDateTime &dt) {
    m_modifiedDate = dt;
}

QDateTime FileItem::createdDate() const {
    return m_createdDate;
}

void FileItem::setCreatedDate(const QDateTime &dt) {
    m_createdDate = dt;
}

QString FileItem::actionsPipeline() const {
    return m_actionsPipeline;
}

void FileItem::setActionsPipeline(const QString &pipeline) {
    m_actionsPipeline = pipeline;
}

QString FileItem::customGroupId() const {
    return m_customGroupId;
}

void FileItem::setCustomGroupId(const QString &groupId) {
    m_customGroupId = groupId;
}

QStringList FileItem::tags() const {
    return m_tags;
}

void FileItem::setTags(const QStringList &tags) {
    m_tags = tags;
}

bool FileItem::isSelected() const {
    return m_selected;
}

void FileItem::setSelected(bool selected) {
    m_selected = selected;
}
