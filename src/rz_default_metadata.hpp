#pragma once

#include <QObject>
#include <QtPlugin>

#include "includes/sqlite3.hpp"

#include "includes/rz_photo-gallery_plugins.hpp"

class Rz_default_metadata : public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "net.hase-zheng.photo_gallery_plugins");
    Q_INTERFACES(Plugin);

public:
    explicit Rz_default_metadata(QObject *parent = nullptr);
    ~Rz_default_metadata();

signals:
public slots:

    // Plugin interface
public:
    QString getPluginNameShort() Q_DECL_OVERRIDE;
    QString getPluginNameLong() Q_DECL_OVERRIDE;
    QString getPluginVersion() Q_DECL_OVERRIDE;
    QString getPluginDescription() Q_DECL_OVERRIDE;

    void setHashMap(const QHash<QString, QString> hashMap, QString type) Q_DECL_OVERRIDE;
    QHash<QString, QString> getHashMap(QString type) Q_DECL_OVERRIDE;

    std::tuple<bool, std::string> parseFile(QMap<QString, QString> &configMap,
                                            QString empty) Q_DECL_OVERRIDE;
    std::tuple<bool, std::string> writeFile(QMap<QString, QString> mapParseKeys,
                                            QMap<QString, QString> mapFileAttribs,
                                            QString pathToFile) Q_DECL_OVERRIDE;
    void doClose() Q_DECL_OVERRIDE;

    void closeDB();

private:
    bool oknok{false};
    std::string msg{"blank"};

    SQLite3 metaDb;

    QHash<QString, QString> exifMetaTags;
    QHash<QString, QString> iptcMetaTags;
    QHash<QString, QString> xmpMetaTags;

    std::tuple<bool, std::string> openDefaultMetaDb(QString &pathToSQLiteDb);
    std::tuple<bool, std::string> setDefaultMetaKeys();
};
