#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "FileItem.h"

/**
 * @brief Modello per la gestione dell'elenco dei file per l'interfaccia Kirigami QML.
 */
class FileListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        FilePathRole = Qt::UserRole + 1,
        FileNameRole,
        IsDirRole,
        FileSizeRole,
        MimeTypeRole,
        ModifiedDateRole,
        CreatedDateRole,
        ActionsPipelineRole,
        CustomGroupIdRole,
        TagsRole,
        IsSelectedRole
    };

    explicit FileListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    void setFiles(const QList<FileItem> &files);
    void addFile(const FileItem &file);
    void clear();

    QList<FileItem> files() const;
    FileItem fileAt(int index) const;

    Q_INVOKABLE void setPipelineAt(int index, const QString &pipeline);
    Q_INVOKABLE void appendPipelineAt(int index, const QString &actionStr);
    Q_INVOKABLE void setSelectedAt(int index, bool selected);
    Q_INVOKABLE void setAllSelected(bool selected);
    Q_INVOKABLE QStringList selectedFilePaths() const;

private:
    QList<FileItem> m_files;
};

#endif // FILELISTMODEL_H
