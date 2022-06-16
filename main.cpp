#include "mainwindow.h"

#include <QApplication>

#include "database.h"
#include "listmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataBase database;
    database.connectToDataBase();

    // Объявляем и инициализируем модель данных
    //ListModel *model = new ListModel();

    MainWindow w;
    w.show();
    return a.exec();
}
