#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QObject>
#include <QStringList>
#include <QVariantMap>

/**
 * @brief Controller per la gestione dei Tag Plasma 6 / Baloo e XDG Extended Attributes (user.xdg.tags).
 */
class TagManager : public QObject {
    Q_OBJECT

public:
    explicit TagManager(QObject *parent = nullptr);

    Q_INVOKABLE QStringList availableTags() const;

    Q_INVOKABLE bool createTag(const QString &tagName, const QString &parentTag = QString());

    Q_INVOKABLE bool deleteTag(const QString &tagName);

    Q_INVOKABLE QVariantMap extractMetadata(const QString &filePath);

    Q_INVOKABLE bool applyTagsToFile(const QString &filePath, const QStringList &tags);

    Q_INVOKABLE QStringList getFileTags(const QString &filePath);

Q_SIGNALS:
    void tagsChanged();

private:
    void loadAvailableTags();
    QStringList m_systemTags;
};

#endif // TAGMANAGER_H
