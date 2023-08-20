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
    setPluginIcon(QIcon(":/images/green/folder-open.svg"));
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




QFileInfo FileForm::doCreateProject()
{
    projectName = ui->projectName->text();
    workDir = ui->workDir->text();

    if(projectName.isEmpty()||workDir.path().isEmpty()){
        ui->tips->clear();
        ui->tips->setText(tr("Tips: INVALID PARAMETER VALUE"));
        return QFileInfo();
    }

    QDir projectDir = workDir.path()+QDir::separator()+projectName;
    QFileInfo projectConfigFileInfo(projectDir.path()+QDir::separator()+projectName+".xplayer");
    QFile projectConfigFile(projectConfigFileInfo.absoluteFilePath());


    if(!projectDir.exists()){
        if(workDir.mkpath(projectDir.path())){
            //project floders
            //projectDir.mkdir("spaces");
            //projectDir.mkdir("playlists");

            //project file
            if(projectConfigFile.open(QFile::WriteOnly)){
                QJsonDocument jsonDoc;
                QJsonObject rootJsonObject;

                QJsonArray spacesJsonArray;
                QJsonArray resourcesJsonArray;




                rootJsonObject.insert("spaces",spacesJsonArray);
                rootJsonObject.insert("playlists",resourcesJsonArray);



                jsonDoc.setObject(rootJsonObject);
                projectConfigFile.write(jsonDoc.toJson());
                projectConfigFile.close();
                return projectConfigFileInfo;

            }
        }
    }
    else{
        ui->tips->clear();
        ui->tips->setText(tr("Tips: %1 is already exists!").arg(projectDir.path()));
        return QFileInfo();
    }
    return QFileInfo();

}
