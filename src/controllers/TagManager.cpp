#include "TagManager.h"
#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

// KFileMetaData headers
#include <KFileMetaData/ExtractorCollection>
#include <KFileMetaData/Extractor>
#include <KFileMetaData/ExtractionResult>
#include <KFileMetaData/Properties>
#include <KFileMetaData/PropertyInfo>

TagManager::TagManager(QObject *parent) : QObject(parent) {
    loadAvailableTags();
}

QStringList TagManager::availableTags() const {
    return m_systemTags;
}

void TagManager::loadAvailableTags() {
    m_systemTags.clear();
    // Esegue balootag per elencare i tag disponibili o legge dai tag salvati nella configurazione
    QProcess process;
    process.start(QStringLiteral("balootag"), QStringList() << QStringLiteral("--list"));
    if (process.waitForFinished(1000) && process.exitCode() == 0) {
        QString output = QString::fromUtf8(process.readAllStandardOutput());
        const QStringList lines = output.split(QLatin1Char('\n'), Qt::SkipEmptyParts);
        for (const QString &line : lines) {
            QString trimmed = line.trimmed();
            if (!trimmed.isEmpty() && !m_systemTags.contains(trimmed)) {
                m_systemTags.append(trimmed);
            }
        }
    }

    // Aggiunge alcuni tag predefiniti se la lista è vuota
    if (m_systemTags.isEmpty()) {
        m_systemTags << QStringLiteral("MUSICA")
                     << QStringLiteral("MUSICA/rock")
                     << QStringLiteral("DOCUMENTI")
                     << QStringLiteral("DOCUMENTI/lavoro")
                     << QStringLiteral("IMMAGINI")
                     << QStringLiteral("IMPORTANT");
    }
}

bool TagManager::createTag(const QString &tagName, const QString &parentTag) {
    if (tagName.trimmed().isEmpty()) return false;

    QString fullTag = tagName.trimmed();
    if (!parentTag.trimmed().isEmpty()) {
        fullTag = parentTag.trimmed() + QStringLiteral("/") + fullTag;
    }

    if (!m_systemTags.contains(fullTag)) {
        m_systemTags.append(fullTag);
        Q_EMIT tagsChanged();
        return true;
    }
    return false;
}

bool TagManager::deleteTag(const QString &tagName) {
    if (m_systemTags.contains(tagName)) {
        m_systemTags.removeAll(tagName);
        Q_EMIT tagsChanged();
        return true;
    }
    return false;
}

QVariantMap TagManager::extractMetadata(const QString &filePath) {
    QVariantMap result;
    QFileInfo info(filePath);
    if (!info.exists()) return result;

    KFileMetaData::ExtractorCollection collection;
    QList<KFileMetaData::Extractor*> extractors = collection.fetchExtractors(filePath);

    class SimpleExtractionResult : public KFileMetaData::ExtractionResult {
    public:
        SimpleExtractionResult(const QString &url)
            : KFileMetaData::ExtractionResult(url, QString(), KFileMetaData::ExtractionResult::ExtractMetaData) {}

        void add(KFileMetaData::Property::Property property, const QVariant &value) override {
            KFileMetaData::PropertyInfo info(property);
            m_properties.insert(info.displayName(), value);
        }

        void append(const QString &text) override {
            Q_UNUSED(text);
        }

        void addType(KFileMetaData::Type::Type type) override {
            Q_UNUSED(type);
        }

        QVariantMap m_properties;
    };

    SimpleExtractionResult extractionResult(filePath);
    for (KFileMetaData::Extractor *extractor : extractors) {
        extractor->extract(&extractionResult);
    }

    // Aggiunge i metadati trovati o di base
    result = extractionResult.m_properties;
    if (result.isEmpty()) {
        result.insert(QStringLiteral("Nome File"), info.completeBaseName());
        result.insert(QStringLiteral("Estensione"), info.suffix());
        result.insert(QStringLiteral("Dimensione (Bytes)"), info.size());
    }

    return result;
}

bool TagManager::applyTagsToFile(const QString &filePath, const QStringList &tags) {
    if (filePath.isEmpty() || tags.isEmpty()) return false;
    QString tagStr = tags.join(QStringLiteral(","));
    QProcess process;
    process.start(QStringLiteral("setfattr"), QStringList() << QStringLiteral("-n") << QStringLiteral("user.xdg.tags") << QStringLiteral("-v") << tagStr << filePath);
    return process.waitForFinished() && (process.exitCode() == 0);
}

QStringList TagManager::getFileTags(const QString &filePath) {
    QStringList tags;
    if (filePath.isEmpty()) return tags;

    QProcess process;
    process.start(QStringLiteral("getfattr"), QStringList() << QStringLiteral("-n") << QStringLiteral("user.xdg.tags") << QStringLiteral("--only-values") << filePath);
    if (process.waitForFinished() && process.exitCode() == 0) {
        QString out = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
        if (!out.isEmpty()) {
            tags = out.split(QLatin1Char(','), Qt::SkipEmptyParts);
        }
    }
    return tags;
}
