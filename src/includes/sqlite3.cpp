#include "sqlite3.hpp"

std::tuple<bool, std::string> SQLite3::openDb(QString &pathToFile)
{
    return (openSQLiteDatabase(pathToFile));
}

int SQLite3::closeDb()
{
    return (closeDatabase());
}

int SQLite3::createTable()
{
    QString query
        = "CREATE TABLE IF NOT EXISTS MyTable(Id INTEGER PRIMARY KEY, Name TEXT, Age INTEGER);";
    return executeQuery(query);
}

int SQLite3::deleteTable()
{
    return 0;
}

int SQLite3::insertData()
{
    QString query = "INSERT INTO MyTable(Name, Age) VALUES('Bote', 60);";
    return executeQuery(query);
}

int SQLite3::selectData()
{
    QString query = "SELECT * FROM MyTable;";
    return executeQuery(query);
}

int SQLite3::selectDataWithField()
{
    QString query = "SELECT * FROM MyTable;";
    return executeQueryWithFields(query);
}

int SQLite3::updateData()
{
    return 0;
}

int SQLite3::deleteData()
{
    return 0;
}
