#include "videoform.h"
#include "ui_videoform.h"

VideoForm::VideoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoForm)
{
    ui->setupUi(this);

    workPath = QDir::homePath();
    ui->workPath->setText(workPath.path());
    templeteList<<tr("grid")<<tr("splitter");
    ui->comboBox->addItems(templeteList);
}

VideoForm::~VideoForm()
{
    delete ui;
}
