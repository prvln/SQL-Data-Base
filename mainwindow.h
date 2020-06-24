#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
/* Подключаем заголовочный файл для работы с информацией, которая помещена в базу данных */
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void SignIn();

    void InsertStudentButton();
    void InsertKafedraButton();
    void InsertFakultetButton();

    void UpdateStudentButton();
    void UpdateKafedraButton();
    void UpdateFakultetButton();

    void DeleteStudentButton();
    void DeleteKafedraButton();
    void DeleteFakultetButton();

    void UpdateButton();
    void dialValueChanged(int value);
    void dial_2ValueChanged(int value);


private:
    Ui::MainWindow  *ui;
    /* В проекте используются объекты для взаимодействия с информацией в базе данных
     * и моделью представления таблицы базы данных
     * */
    DataBase        *db;
    QSqlTableModel  *model;

private:
    /* Также присутствуют два метода, которые формируют модель
     * и внешний вид TableView
     * */
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
    void UpdateTables();
};

#endif // MAINWINDOW_H
