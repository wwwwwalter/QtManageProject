#include "audioform.h"
#include "ui_audioform.h"
#include <QFileDialog>


AudioForm::AudioForm(QWidget *parent) :
    AbstrackPlugin(parent),
    ui(new Ui::AudioForm)
{
    ui->setupUi(this);
    //for standitem
    setPluginIcon(QIcon(":/images/folder_open.svg"));
    setPluginName(tr("AudioForm"));

    //for right widget
    projectDir = QDir::homePath();
    ui->projectDir->setText(projectDir.path());
    templeteList<<tr("单声道")<<tr("立体声");
    ui->comboBox->addItems(templeteList);

    //choose work path
    connect(ui->choose,&QPushButton::clicked,this,[=]{
        ui->projectDir->setText(QFileDialog::getExistingDirectory(this,tr("Project Dir"),ui->projectDir->text()));
    });
}

AudioForm::~AudioForm()
{
    delete ui;
}


void AudioForm::doCreateProject()
{
    projectName = ui->projectName->text();
    projectDir = ui->projectDir->text();
    qDebug()<<"audio ok";
}

