#include "audioform.h"
#include "ui_audioform.h"


AudioForm::AudioForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioForm)
{
    ui->setupUi(this);

    workPath = QDir::homePath();
    ui->workPath->setText(workPath.path());
    templeteList<<tr("单声道")<<tr("立体声");
    ui->comboBox->addItems(templeteList);
}

AudioForm::~AudioForm()
{
    delete ui;
}
