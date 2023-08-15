#include "fileform.h"
#include "ui_fileform.h"

#include <QFileDialog>

FileForm::FileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileForm)
{
    ui->setupUi(this);

    workPath = QDir::homePath();
    ui->workPath->setText(workPath.path());
    templeteList<<tr("tab")<<tr("file");
    ui->comboBox->addItems(templeteList);



    //choose work path
    connect(ui->choose,&QPushButton::clicked,this,[=]{
        ui->workPath->setText(QFileDialog::getExistingDirectory(this,tr("Work path"),ui->workPath->text()));
    });

}

FileForm::~FileForm()
{
    delete ui;
}
