#include "FileGroup.h"

FileGroup::FileGroup() {
}

FileGroup::FileGroup(const QString &id, const QString &name, bool isCustom)
    : m_groupId(id), m_groupName(name), m_isCustom(isCustom) {
}

QString FileGroup::groupId() const {
    return m_groupId;
}

void FileGroup::setGroupId(const QString &id) {
    m_groupId = id;
}

QString FileGroup::groupName() const {
    return m_groupName;
}

void FileGroup::setGroupName(const QString &name) {
    m_groupName = name;
}

bool FileGroup::isCustom() const {
    return m_isCustom;
}

void FileGroup::setCustom(bool custom) {
    m_isCustom = custom;
}

QString FileGroup::actionsPipeline() const {
    return m_actionsPipeline;
}

void FileGroup::setActionsPipeline(const QString &pipeline) {
    m_actionsPipeline = pipeline;
}

QStringList FileGroup::filePaths() const {
    return m_filePaths;
}

void FileGroup::setFilePaths(const QStringList &paths) {
    m_filePaths = paths;
}

void FileGroup::addFilePath(const QString &path) {
    if (!m_filePaths.contains(path)) {
        m_filePaths.append(path);
    }
}

void FileGroup::removeFilePath(const QString &path) {
    m_filePaths.removeAll(path);
}
