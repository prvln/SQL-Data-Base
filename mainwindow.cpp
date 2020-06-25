#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
     * и инициализировать подключение к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();

    this->createUI();

    connect(ui->signin, SIGNAL(clicked()), this, SLOT(SignIn()));

    connect(ui->InsertButton, SIGNAL(clicked()), this, SLOT(InsertStudentButton()));
    connect(ui->KafedraInsertButton, SIGNAL(clicked()), this, SLOT(InsertKafedraButton()));
    connect(ui->FakultetInsertButton, SIGNAL(clicked()), this, SLOT(InsertFakultetButton()));

    connect(ui->StudentChangeButton, SIGNAL(clicked()), this, SLOT(UpdateStudentButton()));
    connect(ui->KafedraChangeButton, SIGNAL(clicked()), this, SLOT(UpdateKafedraButton()));
    connect(ui->FakultetChangeButton, SIGNAL(clicked()), this, SLOT(UpdateFakultetButton()));

    connect(ui->StudentDeleteButton, SIGNAL(clicked()), this, SLOT(DeleteStudentButton()));
    connect(ui->KafedraDeleteButton, SIGNAL(clicked()), this, SLOT(DeleteKafedraButton()));
    connect(ui->FakultetDeleteButton, SIGNAL(clicked()), this, SLOT(DeleteFakultetButton()));

    connect(ui->UpdateButton, SIGNAL(clicked()), this, SLOT(UpdateButton()));
    connect(ui->UpdateButton_2, SIGNAL(clicked()), this, SLOT(UpdateButton()));
    connect(ui->UpdateButton_3, SIGNAL(clicked()), this, SLOT(UpdateButton()));

    connect(ui->dial, SIGNAL(valueChanged(int)), this , SLOT(dialValueChanged(int)));
    connect(ui->dial_2, SIGNAL(valueChanged(int)), this , SLOT(dial_2ValueChanged(int)));
    ui->dial->setMinimum(0);
    ui->dial->setMaximum(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Метод для инициализации модеи представления данных
 * */
void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
    /*ui->tableView->setColumnHidden(0, true);
    ui->tableView_2->setColumnHidden(0, true);
    ui->tableView_3->setColumnHidden(0, true);*/
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_3->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_3->resizeColumnsToContents();

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_3->horizontalHeader()->setStretchLastSection(true);

    UpdateButton();
}

void MainWindow::SignIn(){
    const QString login = ui->login->text();
    const QString password = ui->password->text();

    int result = db->log_in(login, password);

    if(result == 1){
            ui->label_login->setHidden(true);
            ui->label_password->setHidden(true);
            ui->login->setHidden(true);
            ui->password->setHidden(true);
            ui->signin->setHidden(true);
            ui->blocker->setHidden(true);
            ui->blocker_user->setHidden(true);
    }else if(result == 2){
            ui->label_login->setHidden(true);
            ui->label_password->setHidden(true);
            ui->login->setHidden(true);
            ui->password->setHidden(true);
            ui->signin->setHidden(true);
            ui->blocker->setHidden(true);
            ui->blocker_user->setHidden(true);
    }else if(result == 3){
            ui->label_login->setHidden(true);
            ui->label_password->setHidden(true);
            ui->login->setHidden(true);
            ui->password->setHidden(true);
            ui->signin->setHidden(true);
            ui->blocker->setHidden(true);
    }else{
        ui->signin->setText("Неверная связка логин/пароль");
    }
}

void MainWindow::UpdateButton(){
    this->setupModel("students_table",
        QStringList() << trUtf8("ID")
                      << trUtf8("Имя")
                      << trUtf8("Фамилия")
                      << trUtf8("Группа")
                      << trUtf8("Индекс")
                      << trUtf8("Возраст")
                      << trUtf8("Кафедра")
                      << trUtf8("Факультет")    );
    ui->tableView->setModel(model);
    model->select();


    this->setupModel("kafedra_table",
        QStringList() << trUtf8("ID")
                      << trUtf8("Кафедра")    );
    ui->tableView_2->setModel(model);
    model->select();

    this->setupModel("fakultet_table",
        QStringList() << trUtf8("ID")
                      << trUtf8("Факультет")    );
    ui->tableView_3->setModel(model);
    model->select();


    QStringList buffer;

    buffer = db->getComboBoxData("kafedra_table");
    ui->comboBox->clear();
    ui->comboBox_5->clear();
    for (int i = 0; i < buffer.size(); ++i){
             ui->comboBox->addItem(buffer.at(i));
             ui->comboBox_5->addItem(buffer.at(i));
    }

    buffer.clear();

    buffer = db->getComboBoxData("fakultet_table");

    ui->comboBox_2->clear();
    ui->comboBox_6->clear();
    for (int i = 0; i < buffer.size(); ++i){
             ui->comboBox_2->addItem(buffer.at(i));
             ui->comboBox_6->addItem(buffer.at(i));
    }
}

void MainWindow::InsertStudentButton()
{
    QVariantList data;
    data.append(ui->NameLine->text());
    data.append(ui->LastNameLine->text());
    data.append(ui->GroupLine->text());
    data.append(ui->IndexLine->text());
    data.append(ui->AgeLine->text());
    data.append(ui->comboBox->currentText());
    data.append(ui->comboBox_2->currentText());
    db->IntoTable(data, 1 ,1);
}

void MainWindow::UpdateStudentButton()
{
    QVariantList data;
    data.append(ui->NameLine_5->text());
    data.append(ui->LastNameLine_3->text());
    data.append(ui->GroupLine_3->text());
    data.append(ui->IndexLine_3->text());
    data.append(ui->AgeLine_3->text());
    data.append(ui->comboBox_5->currentText());
    data.append(ui->comboBox_6->currentText());
    data.append(ui->StudentChangeID->text());
    db->IntoTable(data, 1, 2);
}

void MainWindow::DeleteStudentButton()
{
    QVariantList data;
    data.append(ui->StudentDeleteID->text());
    qDebug() << data[0];
    db->IntoTable(data, 1, 3);
}

void MainWindow::InsertKafedraButton()
{
    QVariantList data;
    data.append(ui->KafedraInsertName->text());
    qDebug() << data[0];
    db->IntoTable(data, 2, 1);
}

void MainWindow::UpdateKafedraButton()
{
    QVariantList data;
    data.append(ui->KafedraChangeName->text());
    data.append(ui->KafedraChangeID->text());
    db->IntoTable(data, 2, 2);
}

void MainWindow::DeleteKafedraButton()
{
    QVariantList data;
    data.append(ui->KafedraDeleteID->text());
    db->IntoTable(data, 2, 3);
}

void MainWindow::InsertFakultetButton()
{
    QVariantList data;
    data.append(ui->FakultetInsertName->text());
    db->IntoTable(data, 3, 1);
}

void MainWindow::UpdateFakultetButton()
{
    QVariantList data;
    data.append(ui->FakultetChangeName->text());
    data.append(ui->FakultetChangeID->text());
    db->IntoTable(data, 3, 2);
}

void MainWindow::DeleteFakultetButton()
{
    QVariantList data;
    data.append(ui->FakultetDeleteID->text());
    db->IntoTable(data, 3, 3);
}



void MainWindow::dialValueChanged(int value)
{
  ui->progressBar->setRange(0, 100);
  ui->progressBar->setValue(value);
}

void MainWindow::dial_2ValueChanged(int value)
{
  ui->progressBar->setMinimumWidth(value * 8);
  ui->progressBar->setMaximumWidth(value * 8);
}
