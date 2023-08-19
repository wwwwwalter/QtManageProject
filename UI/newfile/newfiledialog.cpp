#include "newfiledialog.h"
#include "ui_newfiledialog.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QString>

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

    emptyFileIcon.addPixmap(QPixmap(":/images/green/file-addition.svg"));
    videoSpaceIcon.addPixmap(QPixmap(":/images/green/layout-four.svg"));
    audioSpaceIcon.addPixmap(QPixmap(":/images/green/layout-four.svg"));
    playListIcon.addPixmap(QPixmap(":/images/green/view-list.svg"));

    ui->savePath->setText("C:/Users/study/Desktop/testfile");

    model = new QStandardItemModel;
    ui->listView->setModel(model);
    selectionModel = new QItemSelectionModel;
    selectionModel->setModel(model);
    ui->listView->setSelectionModel(selectionModel);

    QStandardItem *emptySpaceItem = new QStandardItem(videoSpaceIcon,tr("Empty Space"));
    emptySpaceItem->setData(".space",Qt::UserRole+1);
    QStandardItem *videoSpaceItem = new QStandardItem(videoSpaceIcon,tr("Video Space"));
    videoSpaceItem->setData(".space",Qt::UserRole+1);
    QStandardItem *audioSpaceItem = new QStandardItem(audioSpaceIcon,tr("Audio Space"));
    audioSpaceItem->setData(".space",Qt::UserRole+1);
    QStandardItem *playlistItem = new QStandardItem(playListIcon,tr("Play list"));
    playlistItem->setData(".playlist",Qt::UserRole+1);
    QStandardItem *textFileItem = new QStandardItem(audioSpaceIcon,tr("Text File"));
    textFileItem->setData(".txt",Qt::UserRole+1);
    model->appendRow(emptySpaceItem);
    model->appendRow(videoSpaceItem);
    model->appendRow(audioSpaceItem);
    model->appendRow(playlistItem);
    model->appendRow(textFileItem);


    connect(selectionModel,&QItemSelectionModel::selectionChanged,this,[=](const QItemSelection &selected, const QItemSelection &deselected){

    });

    connect(selectionModel,&QItemSelectionModel::currentChanged,this,[=](const QModelIndex &current, const QModelIndex &previous){
        ui->stackedWidget->setCurrentIndex(current.row());
        extensionName = current.data(Qt::UserRole+1).toString();
        qDebug()<<current.row();
    });

    connect(ui->listView,&QListView::clicked,this,[=](const QModelIndex &index){

    });




    ui->listView->setCurrentIndex(emptySpaceItem->index());













    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,[=]{
        fileName = ui->fileName->text();
        savePath = ui->savePath->text();
        if(fileName.isEmpty()||savePath.isEmpty()){
            ui->tips->setText(tr("Tips: INVALID PARAMETER VALUE"));
            return;
        }
        else{
            if(extensionName==".space"){
                QFileInfo newFileInfo; newFileInfo = QFileInfo(savePath+QDir::separator()+fileName+".space");
                QFile newFile(newFileInfo.filePath());
                QDir saveDir(savePath);

                if(!newFile.exists()){
                    if(!saveDir.mkpath(saveDir.path())){
                        ui->tips->clear();
                        ui->tips->setText(tr("Tips: mkdir failed!"));
                        return;
                    }

                    if(newFile.open(QFile::WriteOnly)){
                        QJsonDocument jsonDoc;
                        QJsonObject rootJsonObject;
                        QJsonObject layoutJsonObject;
                        QJsonArray mediaJsonArray;

                        layoutJsonObject.insert("rols",QJsonValue(2));
                        layoutJsonObject.insert("cols",QJsonValue(2));

                        rootJsonObject.insert("name",QJsonValue(fileName));
                        rootJsonObject.insert("layout",layoutJsonObject);
                        rootJsonObject.insert("medias",mediaJsonArray);

                        jsonDoc.setObject(rootJsonObject);
                        newFile.write(jsonDoc.toJson());


                        newFile.close();
                        emit fileCreateComplete(newFileInfo);
                        this->accept();
                    }
                }
                else{
                    ui->tips->clear();
                    ui->tips->setText(tr("Tips: file already exists!"));
                    return;
                }
            }
            else if(extensionName==".playlist"){
                QFileInfo newFileInfo; newFileInfo = QFileInfo(savePath+QDir::separator()+fileName+".playlist");
                QFile newFile(newFileInfo.filePath());
                QDir saveDir(savePath);

                if(!newFile.exists()){
                    if(!saveDir.mkpath(saveDir.path())){
                        ui->tips->setText(tr("Tips: mkdir failed!"));
                        return;
                    }

                    if(newFile.open(QFile::WriteOnly)){
                        QJsonDocument jsonDoc;
                        QJsonObject rootJsonObject;
                        QJsonArray playlistJsonArray;

                        rootJsonObject.insert("name",QJsonValue(fileName));
                        rootJsonObject.insert("playlist",playlistJsonArray);

                        jsonDoc.setObject(rootJsonObject);
                        newFile.write(jsonDoc.toJson());

                        newFile.close();
                        emit fileCreateComplete(newFileInfo);
                        this->accept();
                    }
                }
                else{
                    ui->tips->clear();
                    ui->tips->setText(tr("Tips: file already exists!"));
                    return;
                }
            }else{
                //empty
            }

        }

    });


}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}
