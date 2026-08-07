#include "FileListModel.h"

FileListModel::FileListModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int FileListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_files.size();
}

QVariant FileListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_files.size()) {
        return QVariant();
    }

    const FileItem &item = m_files.at(index.row());

    switch (role) {
    case FilePathRole:
        return item.filePath();
    case FileNameRole:
        return item.fileName();
    case IsDirRole:
        return item.isDir();
    case FileSizeRole:
        return item.fileSize();
    case MimeTypeRole:
        return item.mimeType();
    case ModifiedDateRole:
        return item.modifiedDate().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss"));
    case CreatedDateRole:
        return item.createdDate().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss"));
    case ActionsPipelineRole:
        return item.actionsPipeline();
    case CustomGroupIdRole:
        return item.customGroupId();
    case TagsRole:
        return item.tags();
    case IsSelectedRole:
        return item.isSelected();
    default:
        return QVariant();
    }
}

bool FileListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_files.size()) {
        return false;
    }

    FileItem &item = m_files[index.row()];

    if (role == ActionsPipelineRole) {
        item.setActionsPipeline(value.toString());
        Q_EMIT dataChanged(index, index, {ActionsPipelineRole});
        return true;
    } else if (role == IsSelectedRole) {
        item.setSelected(value.toBool());
        Q_EMIT dataChanged(index, index, {IsSelectedRole});
        return true;
    } else if (role == CustomGroupIdRole) {
        item.setCustomGroupId(value.toString());
        Q_EMIT dataChanged(index, index, {CustomGroupIdRole});
        return true;
    } else if (role == TagsRole) {
        item.setTags(value.toStringList());
        Q_EMIT dataChanged(index, index, {TagsRole});
        return true;
    }

    return false;
}

QHash<int, QByteArray> FileListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FilePathRole] = "filePath";
    roles[FileNameRole] = "fileName";
    roles[IsDirRole] = "isDir";
    roles[FileSizeRole] = "fileSize";
    roles[MimeTypeRole] = "mimeType";
    roles[ModifiedDateRole] = "modifiedDate";
    roles[CreatedDateRole] = "createdDate";
    roles[ActionsPipelineRole] = "actionsPipeline";
    roles[CustomGroupIdRole] = "customGroupId";
    roles[TagsRole] = "tags";
    roles[IsSelectedRole] = "isSelected";
    return roles;
}

void FileListModel::setFiles(const QList<FileItem> &files) {
    beginResetModel();
    m_files = files;
    endResetModel();
}

void FileListModel::addFile(const FileItem &file) {
    beginInsertRows(QModelIndex(), m_files.size(), m_files.size());
    m_files.append(file);
    endInsertRows();
}

void FileListModel::clear() {
    beginResetModel();
    m_files.clear();
    endResetModel();
}

QList<FileItem> FileListModel::files() const {
    return m_files;
}

FileItem FileListModel::fileAt(int index) const {
    if (index >= 0 && index < m_files.size()) {
        return m_files.at(index);
    }
    return FileItem();
}

void FileListModel::setPipelineAt(int index, const QString &pipeline) {
    if (index >= 0 && index < m_files.size()) {
        m_files[index].setActionsPipeline(pipeline);
        QModelIndex idx = createIndex(index, 0);
        Q_EMIT dataChanged(idx, idx, {ActionsPipelineRole});
    }
}

void FileListModel::appendPipelineAt(int index, const QString &actionStr) {
    if (index >= 0 && index < m_files.size()) {
        QString current = m_files[index].actionsPipeline();
        QString updated = current.trimmed().isEmpty() ? actionStr : current.trimmed() + QStringLiteral(" AND ") + actionStr;
        m_files[index].setActionsPipeline(updated);
        QModelIndex idx = createIndex(index, 0);
        Q_EMIT dataChanged(idx, idx, {ActionsPipelineRole});
    }
}

void FileListModel::setSelectedAt(int index, bool selected) {
    if (index >= 0 && index < m_files.size()) {
        m_files[index].setSelected(selected);
        QModelIndex idx = createIndex(index, 0);
        Q_EMIT dataChanged(idx, idx, {IsSelectedRole});
    }
}

void FileListModel::setAllSelected(bool selected) {
    for (int i = 0; i < m_files.size(); ++i) {
        m_files[i].setSelected(selected);
    }
    if (!m_files.isEmpty()) {
        Q_EMIT dataChanged(createIndex(0, 0), createIndex(m_files.size() - 1, 0), {IsSelectedRole});
    }
}

QStringList FileListModel::selectedFilePaths() const {
    QStringList selected;
    for (const FileItem &item : m_files) {
        if (item.isSelected()) {
            selected.append(item.filePath());
        }
    }
    return selected;
}
