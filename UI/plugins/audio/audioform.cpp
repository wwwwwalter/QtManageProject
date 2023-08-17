#include "audioform.h"
#include "ui_audioform.h"
#include <QFileDialog>
#include <QMessageBox>


AudioForm::AudioForm(QWidget *parent) :
    AbstrackPlugin(parent),
    ui(new Ui::AudioForm)
{
    ui->setupUi(this);
    //for standitem
    setPluginIcon(QIcon(":/images/folder_open.svg"));
    setPluginName(tr("AudioForm"));

    //for right widget
    workDir = QDir::homePath();
    ui->workDir->setText(workDir.path());
    templeteList<<tr("单声道")<<tr("立体声");
    ui->comboBox->addItems(templeteList);

    //choose work path
    connect(ui->choose,&QPushButton::clicked,this,[=]{
        ui->workDir->setText(QFileDialog::getExistingDirectory(this,tr("Project Dir"),ui->workDir->text()));
    });
}

AudioForm::~AudioForm()
{
    delete ui;
}


QDir AudioForm::doCreateProject()
{
    projectName = ui->projectName->text();
    workDir = ui->workDir->text();


    if(projectName.isEmpty()||workDir.path().isEmpty()){
        ui->tips->clear();
        ui->tips->setText(tr("Tips: INVALID PARAMETER VALUE"));
    }

    QDir projectDir = workDir.path()+QDir::separator()+projectName;
    QFile projectFile = projectDir.path()+QDir::separator()+projectName+".xplayer";

    if(!projectDir.exists()){
        if(workDir.mkpath(projectDir.path())){
            //project floders
            projectDir.mkdir("tabs");
            projectDir.mkdir("resources");

            //project file
            if(projectFile.open(QIODevice::WriteOnly)){
                QTextStream stream(&projectFile);
                stream << "[XPlayer]\n";
                stream << "Audio\n";
                stream << "[Audio]\n";
                stream << "[Template]\n";
                stream << ui->comboBox->currentText();

                projectFile.close();
                return projectDir;
                //QMessageBox::information(this, "information", "create project complete");
            }
        }
    }
    else{
        ui->tips->clear();
        ui->tips->setText(tr("Tips: %1 is already exists!").arg(projectDir.path()));
    }
    return QDir();
}

