#include "database.hpp"
#include <filesystem>

std::tuple<bool, std::string> Database::openSQLiteDatabase(const QString &pathToDbFile)
{
    if (!std::filesystem::exists(pathToDbFile.toStdString())) {
        return std::make_tuple(false, "Database::openSQLiteDatabase:: DB doesn't exist");
    }

    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE");

    db->setDatabaseName(pathToDbFile);

    if (!db->open()) {
        return std::make_tuple(false, "Error openDatabase: " + db->lastError().text().toStdString());
    }
    return std::make_tuple(true, "Database open");
}

int Database::closeDatabase()
{
    //db->close();
    return 0;
}

int Database::executeQuery(const QString &queryString)
{
    QSqlQuery query(*db);
    if (!query.exec(queryString)) {
        qDebug() << "Error executeQuery:" << query.lastError().text();
        return 1;
    }
    return 0;
}

int Database::executeQueryWithFields(const QString &queryString)
{
    QSqlQuery query(*db);
    if (!query.exec(queryString)) {
        qDebug() << "Error executeQuery:" << query.lastError().text();
        return 1;
    }
    QSqlRecord record = query.record();
    while (query.next()) {
        for (int i = 0; i < record.count(); i++) {
            QSqlField field = record.field(i);
            QString name = field.metaType().name();
            if (name.compare("int") == 0) {
                qDebug() << "Field name:" << field.name()
                         << "Value:" << query.value(field.name()).toInt();
            } else {
                qDebug() << "Field name:" << field.name()
                         << "Value:" << query.value(field.name()).toString();
            }

            qDebug() << "--------------------------------------";
        }
    }

    return 0;
}
