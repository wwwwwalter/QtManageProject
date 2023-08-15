#include "videoform.h"
#include "ui_videoform.h"
#include <QFileDialog>

VideoForm::VideoForm(QWidget *parent) :
    AbstrackPlugin(parent),
    ui(new Ui::VideoForm)
{
    ui->setupUi(this);

    //for standitem
    setPluginIcon(QIcon(":/images/folder_open.svg"));
    setPluginName(tr("VideoForm"));

    //for right widget
    projectDir = QDir::homePath();
    ui->projectDir->setText(projectDir.path());
    templeteList<<tr("grid")<<tr("splitter");
    ui->comboBox->addItems(templeteList);

    //choose work path
    connect(ui->choose,&QPushButton::clicked,this,[=]{
        ui->projectDir->setText(QFileDialog::getExistingDirectory(this,tr("Project Dir"),ui->projectDir->text()));
    });
}

VideoForm::~VideoForm()
{
    delete ui;
}


void VideoForm::doCreateProject()
{
    projectName = ui->projectName->text();
    projectDir = ui->projectDir->text();
    qDebug()<<"video ok";
}
