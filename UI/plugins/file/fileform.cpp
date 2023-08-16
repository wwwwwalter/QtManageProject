#include "fileform.h"
#include "ui_fileform.h"

#include <QFileDialog>
#include <QMessageBox>

FileForm::FileForm(QWidget *parent) :
    AbstrackPlugin(parent),
    ui(new Ui::FileForm)
{
    ui->setupUi(this);

    //for standitem
    setPluginIcon(QIcon(":/images/folder_open.svg"));
    setPluginName(tr("FileForm"));

    //for right widget
    workDir = QDir::homePath();
    ui->workDir->setText(workDir.path());
    templeteList<<tr("tab")<<tr("file");
    ui->comboBox->addItems(templeteList);



    //choose work path
    connect(ui->choose,&QPushButton::clicked,this,[=]{
        ui->workDir->setText(QFileDialog::getExistingDirectory(this,tr("Project Dir"),ui->workDir->text()));
    });



}

FileForm::~FileForm()
{
    delete ui;
}




int FileForm::doCreateProject()
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
            if(projectFile.open(QIODevice::WriteOnly)){
                QTextStream stream(&projectFile);
                stream << "[XPlayer]\n";
                stream << "File\n";
                stream << "[File]\n";
                stream << "[Template]\n";
                stream << ui->comboBox->currentText();

                projectFile.close();
                return 0;
                //QMessageBox::information(this, "information", "create project complete");
            }
        }
    }
    else{
        ui->tips->clear();
        ui->tips->setText(tr("Tips: %1 is already exists!").arg(projectDir.path()));
    }
    return -1;
}
