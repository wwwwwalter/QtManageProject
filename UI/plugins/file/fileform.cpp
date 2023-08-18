#include "fileform.h"
#include "ui_fileform.h"

#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
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
    workDir = QDir::homePath()+QDir::separator()+"xplayerproject";
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




QDir FileForm::doCreateProject()
{
    projectName = ui->projectName->text();
    workDir = ui->workDir->text();

    if(projectName.isEmpty()||workDir.path().isEmpty()){
        ui->tips->clear();
        ui->tips->setText(tr("Tips: INVALID PARAMETER VALUE"));
        return QDir();
    }

    QDir projectDir = workDir.path()+QDir::separator()+projectName;
    QFile projectFile = projectDir.path()+QDir::separator()+projectName+".xplayer";

    if(!projectDir.exists()){
        if(workDir.mkpath(projectDir.path())){
            //project floders
            projectDir.mkdir("spaces");
            projectDir.mkdir("resources");

            //project file
            if(projectFile.open(QFile::WriteOnly)){
                QJsonDocument jsonDoc;
                QJsonObject rootJsonObject;
                QJsonObject projectJsonObject;
                QJsonArray spaceJsonArray;
                QJsonArray resourcesJsonArray;

                projectJsonObject.insert("name",QJsonValue(projectName));
                projectJsonObject.insert("type",QJsonValue(getPluginName()));

                rootJsonObject.insert("project",projectJsonObject);
                rootJsonObject.insert("spaces",spaceJsonArray);
                rootJsonObject.insert("resources",resourcesJsonArray);



                jsonDoc.setObject(rootJsonObject);
                projectFile.write(jsonDoc.toJson());
                projectFile.close();
                return projectDir;

            }
        }
    }
    else{
        ui->tips->clear();
        ui->tips->setText(tr("Tips: %1 is already exists!").arg(projectDir.path()));
        return QDir();
    }
    return QDir();

}
