#include "newfiledialog.h"
#include "ui_newfiledialog.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

    ui->savePath->setText("C:/Users/study/Desktop/testfile");

    model = new QStandardItemModel;
    ui->listView->setModel(model);

    QStandardItem *emptyFileItem = new QStandardItem(QIcon(":images/folder_open.svg"),tr("Empty File"));
    emptyFileItem->setData(".space",Qt::UserRole+1);
    QStandardItem *videoSpaceItem = new QStandardItem(QIcon(":images/folder_open.svg"),tr("Video Space"));
    videoSpaceItem->setData(".space",Qt::UserRole+1);
    QStandardItem *audioSpaceItem = new QStandardItem(QIcon(":images/folder_open.svg"),tr("Audio Space"));
    audioSpaceItem->setData(".space",Qt::UserRole+1);
    QStandardItem *playlistItem = new QStandardItem(QIcon(":images/folder_open.svg"),tr("Play list"));
    playlistItem->setData(".playlist",Qt::UserRole+1);
    model->appendRow(emptyFileItem);
    model->appendRow(videoSpaceItem);
    model->appendRow(audioSpaceItem);
    model->appendRow(playlistItem);


    connect(ui->listView,&QListView::clicked,this,[=](const QModelIndex &index){
        extensionName = index.data(Qt::UserRole+1).toString();
    });




    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,[=]{
        fileName = ui->fileName->text();
        savePath = ui->savePath->text();
        if(fileName.isEmpty()||savePath.isEmpty()){
            ui->tips->setText(tr("Tips: INVALID PARAMETER VALUE"));
            return;
        }

        else{
            QFileInfo newFileInfo(savePath+QDir::separator()+fileName+".space");
            QFile newFile(newFileInfo.filePath());
            QDir saveDir(savePath);


//            QFileInfo info(newFile);
//            qDebug()<<info.fileName();
//            qDebug()<<info.path();
//            qDebug()<<info.filePath();
//            qDebug()<<info.absoluteFilePath();
//            qDebug()<<info.absolutePath();
//            qDebug()<<info.absoluteDir();
//            qDebug()<<saveDir.relativeFilePath("../empty.space");



            if(!newFile.exists()){
                if(!saveDir.mkpath(saveDir.path())){
                    ui->tips->setText(tr("Tips: mkdir failed!"));
                    return;
                }

                if(newFile.open(QFile::WriteOnly)){
                    if(extensionName==".space"){
                        QJsonDocument jsonDoc;
                        QJsonObject rootJsonObject;
                        QJsonObject layoutJsonObject;
                        QJsonArray mediaJsonArray;

                        layoutJsonObject.insert("rols",QJsonValue(2));
                        layoutJsonObject.insert("cols",QJsonValue(2));

                        rootJsonObject.insert("name",QJsonValue(fileName));
                        rootJsonObject.insert("layoutrols",layoutJsonObject);
                        rootJsonObject.insert("medias",mediaJsonArray);

                        jsonDoc.setObject(rootJsonObject);
                        newFile.write(jsonDoc.toJson());
                    }
                    else if(extensionName==".playlist"){
                        QJsonDocument jsonDoc;
                        QJsonObject rootJsonObject;
                        QJsonArray playlistJsonArray;

                        rootJsonObject.insert("name",QJsonValue(fileName));
                        rootJsonObject.insert("playlist",playlistJsonArray);

                        jsonDoc.setObject(rootJsonObject);
                        newFile.write(jsonDoc.toJson());
                    }

                    newFile.close();
                    emit fileCreateComplete(newFileInfo);
                    this->accept();
                }
                else{
                    ui->tips->setText(tr("Tips: open file failed!"));
                    return;
                }
            }
            else{
                ui->tips->setText(tr("Tips: file already exists!"));
                return;
            }
        }

    });


}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}
