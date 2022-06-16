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
    if(!QFile(DATABASE_NAME).exists()){
        this->createDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::createDataBase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    if(this->openDataBase()){
        // Производим создание базы данных
        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Не удалось создать базу данных";
        return false;
    }
    return false;
}


/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    // Если база данных открылась ...
    if(this->openDataBase()){
        // Производим восстановление базы данных
        return (this->createTable()) ? true : false;
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
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
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
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_TEXTN     " VARCHAR(255)    NOT NULL,"
                            TABLE_DATEN     " VARCHAR(255)    NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        insertIntoTable("First note",
                        QDateTime::currentDateTime().date().toString(Qt::ISODate)+" "+
                        QDateTime::currentDateTime().time().toString());
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::insertIntoTable(const QVariantList& data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_TEXTN ", "
                                             TABLE_DATEN " ) "
                  "VALUES (:TextN, :DateN)");
    query.bindValue(":TextN",       data[0].toString());
    query.bindValue(":DateN",       data[1].toString());

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Второй метод для вставки записи в базу данных
 * */
bool DataBase::insertIntoTable(const QString& textn, const QString& daten)
{
    QVariantList data;
    data.append(textn);
    data.append(daten);

    if(insertIntoTable(data))
        return true;
    else
        return false;
}

bool DataBase::updateTextNote(const QString& textn, const QString& daten)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    // После чего выполняется запросом методом exec()
    if(!query.exec("UPDATE " TABLE " SET " TABLE_TEXTN " = '" + textn + "'" " WHERE " TABLE_DATEN " = '" + daten + "'")){
        qDebug() << "error update" << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для удаления записи из таблицы
 * */
bool DataBase::removeRecord(const int id)
{
    // Удаление строки из базы данных будет производитсья с помощью SQL-запроса
    QSqlQuery query;

    // Удаление производим по id записи, который передается в качестве аргумента функции
    query.prepare("DELETE FROM " TABLE " WHERE id= :ID ;");
    query.bindValue(":ID", id);

    // Выполняем удаление
    if(!query.exec()){
        qDebug() << "error delete row " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::removeRecord(const QString& daten)
{
    // Удаление строки из базы данных будет производитсья с помощью SQL-запроса
    QSqlQuery query;

    // Выполняем удаление
    if(!query.exec("DELETE FROM " TABLE " WHERE " TABLE_DATEN " = '" + daten + "'")){
        qDebug() << "error delete row " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
QStringList DataBase::getRecord(const QString& daten){
    // Удаление строки из базы данных будет производитсья с помощью SQL-запроса
    QSqlQuery query;

    // Выполняем удаление
    if(!query.exec("SELECT * FROM " TABLE " WHERE " TABLE_DATEN " = '" + daten + "'")){
        qDebug() << "error get row " << TABLE;
        qDebug() << query.lastError().text();
    }
    QSqlRecord rec = query.record();
    while(query.next()){
        break;
    }
    QStringList sl = {query.value(rec.indexOf(TABLE_TEXTN)).toString(),query.value(rec.indexOf(TABLE_DATEN)).toString()};
    return sl;
}
