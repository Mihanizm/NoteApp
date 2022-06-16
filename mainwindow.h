#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>

#include "database.h"
#include "listmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_confirmAddButton_clicked();

    void on_addButton_clicked();

    void on_listWidget_itemSelectionChanged();

    void on_confirmEditButton_clicked();

    void on_cancelAddButton_clicked();

    void on_cancelEditButton_clicked();

    void on_deleteButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    DataBase database;

    bool update_ListWidget();
};
#endif // MAINWINDOW_H
