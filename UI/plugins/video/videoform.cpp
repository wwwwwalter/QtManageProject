#include "videoform.h"
#include "ui_videoform.h"
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
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


QFileInfo VideoForm::doCreateProject()
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
