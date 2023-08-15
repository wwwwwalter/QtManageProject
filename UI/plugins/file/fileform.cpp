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
    workPath = QDir::homePath();
    ui->workPath->setText(workPath.path());
    templeteList<<tr("tab")<<tr("file");
    ui->comboBox->addItems(templeteList);



    //choose work path
    connect(ui->choose,&QPushButton::clicked,this,[=]{
        ui->workPath->setText(QFileDialog::getExistingDirectory(this,tr("Project Dir"),ui->workPath->text()));
    });



}

FileForm::~FileForm()
{
    delete ui;
}




void FileForm::doCreateProject()
{
    projectName = ui->projectName->text();
    workPath = ui->workPath->text();

    if(projectName.isEmpty()||workPath.path().isEmpty()){
        return;
    }

    QDir projectDir = workPath.path()+QDir::separator()+projectName;
    QFile projectFile = projectDir.path()+QDir::separator()+projectName+".xplayer";

    qDebug()<<projectFile.fileName();


    if(workPath.mkpath(projectDir.path())){
        if(projectFile.open(QIODevice::WriteOnly)){
            QTextStream stream(&projectFile);
            stream << "[XPlayer]\n";
            stream << "File\n";
            stream << "[File]\n";
            stream << "[Template]\n";
            stream << ui->comboBox->currentText();

            projectFile.close();
            QMessageBox::information(this, "information", "create project complete");
        }
        else{
            QMessageBox::critical(this, "critical", "projectFile already exists");
        }
    }
    else{
        QMessageBox::critical(this, "critical", "projectDir already exists");
    }

}
