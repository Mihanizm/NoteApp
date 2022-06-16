#ifndef DATABASE_H
#define DATABASE_H

#include <QDateTime>

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "NotesAppDataBase"
#define DATABASE_NAME       "NoteApp.db"

#define TABLE                   "Notes"         // Название таблицы
#define TABLE_TEXTN            "TextNote"         // Вторая колонка
#define TABLE_DATEN             "DateNote"           // Третья колонка

// Первая колонка содержит Autoincrement ID

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool createDataBase();
    bool openDataBase();        // Открытие базы данных
    bool restoreDataBase();     // Восстановление базы данных
    void closeDataBase();       // Закрытие базы данных
    bool createTable();         // Создание базы таблицы в базе данных

public slots:
    bool insertIntoTable(const QVariantList& data);      // Добавление записей в таблицу
    bool insertIntoTable(const QString& textn, const QString& daten);
    bool updateTextNote(const QString& textn, const QString& daten);
    bool removeRecord(const int id); // Удаление записи из таблицы по её id
    bool removeRecord(const QString& daten); // Удаление записи из таблицы по её id
    QStringList getRecord(const QString& daten);
};

#endif // DATABASE_H
