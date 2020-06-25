#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "DataBase.db"

#define TABLE                "students_table"
#define TABLE_NAME           "name"
#define TABLE_LASTNAME       "last_name"
#define TABLE_GROUP          "group"
#define TABLE_INDEX          "index"
#define TABLE_AGE            "age"
#define TABLE_KAFEDRA        "kafedra"
#define TABLE_FAKULTET       "fakultet"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool IntoTable(const QVariantList &data, const int Table, const int Command);
    bool updateTable(const QVariantList &data, const int Table);
    int log_in(const QString login, const QString password);
    QStringList getComboBoxData(const QString TableName);


private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // DATABASE_H
