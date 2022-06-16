#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    database.connectToDataBase();    
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    update_ListWidget();

    ui->addPlainTextEdit->setVisible(false);
    ui->confirmAddButton->setVisible(false);
    ui->cancelAddButton->setVisible(false);

    ui->editPlainTextEdit->setVisible(false);
    ui->confirmEditButton->setVisible(false);
    ui->cancelEditButton->setVisible(false);

    ui->deleteButton->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::update_ListWidget()
{
    ui->listWidget->clear();

    QSqlQuery query;
    if (!query.exec("SELECT * FROM " TABLE)) {
        qDebug() << "Ooops";
        return false;
    }
    QSqlRecord rec = query.record();
    while(query.next()) {
        QString s = query.value(rec.indexOf(TABLE_DATEN)).toString();
        ui->listWidget->addItem(s);
    }

    return true;
}

void MainWindow::on_confirmAddButton_clicked()
{
    if(ui->addPlainTextEdit->toPlainText() == ""){
        qDebug() << "More words";
        QMessageBox msgBox;
        msgBox.setText("Notes is Empty");
        msgBox.setInformativeText("Are you sure?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    } else {
        database.insertIntoTable(ui->addPlainTextEdit->toPlainText(),
                                 QDateTime::currentDateTime().date().toString(Qt::ISODate)+" "+
                                 QDateTime::currentDateTime().time().toString());

        update_ListWidget();

        ui->addPlainTextEdit->setPlainText("");
        ui->addPlainTextEdit->setVisible(false);
        ui->confirmAddButton->setVisible(false);
        ui->cancelAddButton->setVisible(false);
        ui->deleteButton->setVisible(false);

        ui->listWidget->setVisible(true);
        ui->addButton->setVisible(true);
    }
}

void MainWindow::on_addButton_clicked()
{
    ui->listWidget->setVisible(false);
    ui->addButton->setVisible(false);

    ui->addPlainTextEdit->setVisible(true);
    ui->confirmAddButton->setVisible(true);
    ui->cancelAddButton->setVisible(true);
}

void MainWindow::on_listWidget_itemSelectionChanged()
{

}

void MainWindow::on_confirmEditButton_clicked()
{
    if(ui->editPlainTextEdit->toPlainText() == ""){
        qDebug() << "More words";
    } else {
        database.updateTextNote(ui->editPlainTextEdit->toPlainText(),ui->listWidget->currentItem()->text());
        update_ListWidget();
        ui->editPlainTextEdit->setPlainText("");
        ui->editPlainTextEdit->setVisible(false);
        ui->confirmEditButton->setVisible(false);
        ui->cancelEditButton->setVisible(false);

        ui->listWidget->setVisible(true);
        ui->addButton->setVisible(true);
    }
}


void MainWindow::on_cancelAddButton_clicked()
{
    ui->addPlainTextEdit->setPlainText("");
    ui->addPlainTextEdit->setVisible(false);
    ui->confirmAddButton->setVisible(false);
    ui->cancelAddButton->setVisible(false);

    ui->listWidget->setVisible(true);
    ui->addButton->setVisible(true);
}


void MainWindow::on_cancelEditButton_clicked()
{
    ui->editPlainTextEdit->setPlainText("");
    ui->editPlainTextEdit->setVisible(false);
    ui->confirmEditButton->setVisible(false);
    ui->cancelEditButton->setVisible(false);
    ui->deleteButton->setVisible(false);

    ui->listWidget->setVisible(true);
    ui->addButton->setVisible(true);
}


void MainWindow::on_deleteButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("The current Note will be deleted");
    msgBox.setInformativeText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Ok:
          database.removeRecord(ui->listWidget->currentItem()->text());
          update_ListWidget();

          ui->editPlainTextEdit->setPlainText("");
          ui->editPlainTextEdit->setVisible(false);
          ui->confirmEditButton->setVisible(false);
          ui->cancelEditButton->setVisible(false);
          ui->deleteButton->setVisible(false);

          ui->listWidget->setVisible(true);
          ui->addButton->setVisible(true);
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          break;
      default:
          // should never be reached
          break;
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString s = ui->listWidget->currentItem()->text();
    QStringList sl = database.getRecord(s);
    ui->editPlainTextEdit->setPlainText(sl[0]);

    ui->editPlainTextEdit->setVisible(true);
    ui->confirmEditButton->setVisible(true);
    ui->cancelEditButton->setVisible(true);
    ui->deleteButton->setVisible(true);

    ui->listWidget->setVisible(false);
    ui->addButton->setVisible(false);
}

