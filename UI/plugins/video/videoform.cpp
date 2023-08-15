#include "videoform.h"
#include "ui_videoform.h"
#include <QFileDialog>
#include <QMessageBox>

VideoForm::VideoForm(QWidget *parent) :
    AbstrackPlugin(parent),
    ui(new Ui::VideoForm)
{
    ui->setupUi(this);

    //for standitem
    setPluginIcon(QIcon(":/images/folder_open.svg"));
    setPluginName(tr("VideoForm"));

    //for right widget
    workDir = QDir::homePath();
    ui->workDir->setText(workDir.path());
    templeteList<<tr("grid")<<tr("splitter");
    ui->comboBox->addItems(templeteList);

    //choose work path
    connect(ui->choose,&QPushButton::clicked,this,[=]{
        ui->workDir->setText(QFileDialog::getExistingDirectory(this,tr("Work Dir"),ui->workDir->text()));
    });
}

VideoForm::~VideoForm()
{
    delete ui;
}


void VideoForm::doCreateProject()
{
    projectName = ui->projectName->text();
    workDir = ui->workDir->text();

    if(projectName.isEmpty()||workDir.path().isEmpty()){
        return;
    }

    QDir projectDir = workDir.path()+QDir::separator()+projectName;
    QFile projectFile = projectDir.path()+QDir::separator()+projectName+".xplayer";

    if(workDir.mkpath(projectDir.path())){
        if(projectFile.open(QIODevice::WriteOnly)){
            QTextStream stream(&projectFile);
            stream << "[XPlayer]\n";
            stream << "Video\n";
            stream << "[Video]\n";
            stream << "[Template]\n";
            stream << ui->comboBox->currentText();

            projectFile.close();
            //QMessageBox::information(this, "information", "create project complete");
        }
        else{
            QMessageBox::critical(this, "critical", "projectFile already exists");
        }
    }
    else{
        QMessageBox::critical(this, "critical", "projectDir already exists");
    }
}
