#include "rz_default_metadata.hpp"
#include "includes/rz_config.h"

const QString PLUGIN_SHORTNAME = PROG_EXEC_NAME;
const QString PLUGIN_NAME = PROG_NAME;
const QString PLUGIN_VERSION = PROG_VERSION;
const QString PLUGIN_DESCRIPTION = PROG_DESCRIPTION;

Rz_default_metadata::Rz_default_metadata(QObject *parent)
{
    Q_UNUSED(parent);
    //qDebug() << "Plugin Constructor";
}

Rz_default_metadata::~Rz_default_metadata()
{
    //qDebug() << "Plugin DeConstructor";
}

QString Rz_default_metadata::getPluginNameShort()
{
    return PLUGIN_SHORTNAME;
}

QString Rz_default_metadata::getPluginNameLong()
{
    return PLUGIN_NAME;
}

QString Rz_default_metadata::getPluginVersion()
{
    return PLUGIN_NAME + "-v" + PLUGIN_VERSION;
}

QString Rz_default_metadata::getPluginDescription()
{
    return PLUGIN_DESCRIPTION;
}

void Rz_default_metadata::setHashMap(const QHash<QString, QString> hashMap, QString type) {}

QHash<QString, QString> Rz_default_metadata::getHashMap(QString type)
{
    if (type.contains("IPTC")) {
        return iptcMetaTags;
    }
    if (type.contains("XMP")) {
        return xmpMetaTags;
    }
    return exifMetaTags;
}

std::tuple<bool, std::string> Rz_default_metadata::parseFile(QMap<QString, QString> &configMap,
                                                             QString empty)
{
    QString pathToDb = configMap.value("pathToDb");

    std::tie(oknok, msg) = openDefaultMetaDb(pathToDb);

    if (oknok == false) {
        return std::make_tuple(oknok, "Rz_default_metadata::parseFile::" + msg);
    }

    std::tie(oknok, msg) = setDefaultMetaKeys();
    if (oknok == false) {
        return std::make_tuple(oknok, "Rz_default_metadata::parseFile::" + msg);
    }
    return std::make_tuple(oknok, "Rz_default_metadata::parseFile");
}

std::tuple<bool, std::string> Rz_default_metadata::writeFile(QMap<QString, QString> mapParseKeys,
                                                             QMap<QString, QString> mapFileAttribs,
                                                             QString pathToFile)
{
    return std::make_tuple(true, "Rz_default_metadata::writeFile");
}

std::tuple<bool, std::string> Rz_default_metadata::openDefaultMetaDb(QString &pathToSQLiteDb)
{
    return metaDb.openSQLiteDatabase(pathToSQLiteDb);
}

std::tuple<bool, std::string> Rz_default_metadata::setDefaultMetaKeys()
{
    QString queryStr0 = "SELECT attribute FROM ";
    QString queryStr2 = " WHERE active = 1";

    QSqlQuery query;

    query.prepare(queryStr0 + "EXIF" + queryStr2);
    if (!query.exec()) {
        return std::make_tuple(false, query.lastError().text().toStdString());
    } else {
        while (query.next()) {
            exifMetaTags.insert(query.value("attribute").toString(), "");
        }
    }

    query.prepare(queryStr0 + "IPTC" + queryStr2);
    if (!query.exec()) {
        return std::make_tuple(false, query.lastError().text().toStdString());
    } else {
        while (query.next()) {
            iptcMetaTags.insert(query.value("attribute").toString(), "");
        }
    }

    query.prepare(queryStr0 + "XMP" + queryStr2);
    if (!query.exec()) {
        return std::make_tuple(false, query.lastError().text().toStdString());
    } else {
        while (query.next()) {
            xmpMetaTags.insert(query.value("attribute").toString(), "");
        }
    }

    return std::make_tuple(true, "Default Metatags set");
}
