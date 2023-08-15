#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

#include <QFileDialog>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
    setMinimumWidth(880);
    setWindowTitle(tr("Create new project"));


    ui->titlelabel->setFont(QFont(ui->titlelabel->font().family(),20,-1));


    //listview
    ui->widget_2->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    model = new QStandardItemModel;
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->listView->setStyleSheet(":/qss/listview.qss");

    ui->listView->setIconSize(QSize(30,30));

//    QString stylesheet = "";
//    stylesheet += "QListView::item:alternate {background-image: transparent; background-color: transparent;}";
//    stylesheet += "QListView::item:selected {background-image: transparent; background-color: transparent;padding: 0px;color: black;}";
//    stylesheet += "QListView::item:selected:active{background-image: transparent;background-color: transparent; color: black;}";
//    stylesheet += "QListView::item:selected:!active{background-image: transparent;background-color: transparent;color: black;}";
//    ui->listView->setStyleSheet(stylesheet);

    model->appendRow(new QStandardItem(QIcon(":/images/folder_open.svg"),tr("FileProject")));
    model->appendRow(new QStandardItem(QIcon(":/images/folder_open.svg"),tr("VideoProject")));
    model->appendRow(new QStandardItem(QIcon(":/images/folder_open.svg"),tr("AudioProject")));

    //stackedWidet
    while(ui->stackedWidget->currentWidget()){
        ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());
    }
    ui->stackedWidget->addWidget(new FileForm);
    ui->stackedWidget->addWidget(new VideoForm);
    ui->stackedWidget->addWidget(new AudioForm);

    connect(ui->listView,&QListView::pressed,ui->stackedWidget,[&](const QModelIndex &index){
        ui->stackedWidget->setCurrentIndex(index.row());
    });













}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}
