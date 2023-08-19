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
    QFileInfo projectFileInfo(projectDir.path()+QDir::separator()+projectName+".xplayer");
    QFile projectFile(projectFileInfo.absoluteFilePath());
    QFileInfo emptySpaceFileInfo(projectDir.path() + QDir::separator()+ "spaces" + QDir::separator() + "empty.space");
    QFile emptySpaceFile(emptySpaceFileInfo.absoluteFilePath());

    if(!projectDir.exists()){
        if(workDir.mkpath(projectDir.path())){
            //project floders
            projectDir.mkdir("spaces");
            projectDir.mkdir("playlists");

            //project file
            if(projectFile.open(QFile::WriteOnly)){
                QJsonDocument jsonDoc;
                QJsonObject rootJsonObject;
                QJsonObject projectJsonObject;
                QJsonArray spaceJsonArray;
                QJsonArray resourcesJsonArray;

                projectJsonObject.insert("name",QJsonValue(projectName));

                rootJsonObject.insert("project",projectJsonObject);
                emptySpaceFile.open(QFile::WriteOnly);
                emptySpaceFile.close();
                spaceJsonArray.append(QJsonValue(emptySpaceFileInfo.absoluteFilePath()));

                rootJsonObject.insert("spaces",spaceJsonArray);
                rootJsonObject.insert("playlists",resourcesJsonArray);



                jsonDoc.setObject(rootJsonObject);
                projectFile.write(jsonDoc.toJson());
                projectFile.close();
                return projectFileInfo;

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
