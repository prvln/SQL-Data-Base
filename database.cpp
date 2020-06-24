#include "database.h"



DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile(PATH).exists()){
        qDebug() << "Не удалось найти базу данных";
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(PATH);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE 'fakultet_table' ("
                    "'ID'	INTEGER NOT NULL UNIQUE ,"
                    "'fakultet_name'  TEXT NOT NULL,"
                    "PRIMARY KEY('ID' AUTOINCREMENT);"
                    )
      &!query.exec( "CREATE TABLE 'kafedra_table' ("
                    "'ID'	INTEGER NOT NULL UNIQUE,"
                    "'kafedra_name'	TEXT NOT NULL,"
                    "PRIMARY KEY('ID' AUTOINCREMENT);"
                    )
      &!query.exec(
                    "CREATE TABLE 'students_table'("
                    "'id'	INTEGER NOT NULL UNIQUE,"
                    "'name'	VARCHAR(255) NOT NULL,"
                    "'last_name'	VARCHAR(255) NOT NULL,"
                    "'group'	VARCHAR(255) NOT NULL,"
                    "'index'	VARCHAR(255) NOT NULL,"
                    "'age'	INTEGER NOT NULL,"
                    "'kafedra'	TEXT NOT NULL DEFAULT 0,"
                    "'fakultet'	TEXT NOT NULL DEFAULT 0,"
                    "PRIMARY KEY('id' AUTOINCREMENT),"
                    "FOREIGN KEY('kafedra') REFERENCES 'kafedra_table'('kafedra_name'),"
                    "FOREIGN KEY('fakultet') REFERENCES 'fakultet_table'('fakultet_name');"
                  ) ){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::IntoTable(const QVariantList &data, const int Table, const int Command)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    switch(Command){
    case(1):{
        switch (Table) {
        case(1):{
            query.prepare("INSERT INTO \"main\".\"students_table\" ( \"name\", \"last_name\", \"group\", \"index\", \"age\", \"kafedra_name\", \"fakultet_name\") VALUES ( :name, :last_name, :group, :index, :age , :kafedra, :fakultet); ");
            query.bindValue(":name",       data[0].toString());
            query.bindValue(":last_name",  data[1].toString());
            query.bindValue(":group",      data[2].toString());
            query.bindValue(":index",      data[3].toString());
            query.bindValue(":age",        data[4].toInt());
            query.bindValue(":kafedra",    data[5].toString());
            query.bindValue(":fakultet",   data[6].toString());
            break;
        }
        case(2):{
            query.prepare("INSERT INTO \"main\".\"kafedra_table\" (\"kafedra_name\") VALUES (:kafedra); ");
            query.bindValue(":kafedra",    data[0].toString());
            break;
        }
        case(3):{
            query.prepare("INSERT INTO \"main\".\"fakultet_table\" (\"fakultet_name\") VALUES (:fakultet); ");
            query.bindValue(":fakultet",   data[0].toString());
            break;
        }
        }
        break;

    }
    case(2):{
        switch (Table) {
        case(1):{
            query.prepare("UPDATE \"main\".\"students_table\" SET \"name\" = :name, \"last_name\" = :last_name, \"group\" = :group, \"index\" = :index, \"age\" = :age, \"kafedra_name\" = :kafedra_name, \"fakultet_name\" = :fakultet_name WHERE \"ID\" = :ID;" );
            query.bindValue(":name",       data[0].toString());
            query.bindValue(":last_name",  data[1].toString());
            query.bindValue(":group",      data[2].toString());
            query.bindValue(":index",      data[3].toString());
            query.bindValue(":age",        data[4].toInt());
            query.bindValue(":kafedra_name",    data[5].toString());
            query.bindValue(":fakultet_name",   data[6].toString());
            query.bindValue(":ID",         data[7].toInt());
            break;
        }
        case(2):{
            query.prepare("UPDATE \"main\".\"kafedra_table\" SET \"kafedra_name\" = :kafedra WHERE \"ID\" = :ID; ");
            query.bindValue(":kafedra",    data[0].toString());
            query.bindValue(":ID",         data[1].toInt());
            break;
        }
        case(3):{
            query.prepare("UPDATE \"main\".\"fakultet_table\" SET \"fakultet_name\" = :fakultet WHERE \"ID\" = :ID; ");
            query.bindValue(":fakultet",   data[0].toString());
            query.bindValue(":ID",         data[1].toInt());
            break;
        }
            break;
        }
        break;
    }
    case(3):{
        switch (Table) {
        case(1):{
            query.prepare("DELETE FROM \"main\".\"students_table\" WHERE \"ID\" = :ID;");
            query.bindValue(":ID",       data[0].toString());
            break;
        }
        case(2):{
            query.prepare("DELETE FROM \"main\".\"kafedra_table\" WHERE \"ID\" = :ID;");
            query.bindValue(":ID",       data[0].toString());
            break;
        }
        case(3):{
            query.prepare("DELETE FROM \"main\".\"fakultet_table\" WHERE \"ID\" = :ID;");
            query.bindValue(":ID",       data[0].toString());
            break;
        }
            break;
        }
        break;
    }
    }
    if(!query.exec()){
        qDebug() << "error" << Command << " into " << Table;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
    } else {
        return true;
    }
    return false;
}


QStringList DataBase::getComboBoxData(const QString TableName)
{
    QSqlQuery query;
    query.exec("SELECT * FROM " + TableName);
    QStringList result;
    while (query.next()) {
            result.append(query.value(1).toString());
    }
    return result;
}
