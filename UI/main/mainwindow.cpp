#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QStyleFactory>
#include <UI/newproject/newprojectdialog.h>
#include <UI/newfile/newfiledialog.h>
#include <UI/removefile/removefiledialog.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTabWidget>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //UI
    ui->setupUi(this);
    setupUi();
    //setGeometry(1300,100,400,800);
    setWindowTitle(tr("XPlayer Station"));
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    ui->stackedWidget->setCurrentWidget(ui->welcomePage);



    logoIcon.addPixmap(QPixmap(":/images/green/playback-progress.svg"));
    folderIcon.addPixmap(QPixmap(":/images/green/folder-open.svg"),QIcon::Normal,QIcon::On);
    folderIcon.addPixmap(QPixmap(":/images/green/folder-close.svg"),QIcon::Normal,QIcon::Off);
    spaceIcon.addPixmap(QPixmap(":/images/green/insert-table.svg"));
    playlistIcon.addPixmap(QPixmap(":/images/green/music-list.svg"));
    configFileIcon.addPixmap(QPixmap(":/images/green/file-code-one.svg"));

    setWindowIcon(logoIcon);


    // init File system model
//    fileSystemRootDir = QDir::homePath();
//    fileSystemModel = new QFileSystemModel;
//    fileSystemModel->setRootPath(fileSystemRootDir.path());
//    ui->fileSystemTreeView->setModel(fileSystemModel);
//    ui->fileSystemTreeView->setRootIndex(fileSystemModel->index(fileSystemRootDir.path()));
//    ui->fileSystemTreeView->setColumnWidth(0, 200);


    // init project model
    projectModel = new QStandardItemModel;
    projectSelectModel = new QItemSelectionModel(projectModel);
    ui->projectTreeView->setModel(projectModel);
    ui->projectTreeView->setSelectionModel(projectSelectModel);
    ui->projectTreeView->header()->hide();
    ui->projectTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->projectTreeView,&QTreeView::customContextMenuRequested,this,[=](const QPoint &pos){
        ui->projectTreeView->currentIndex() = ui->projectTreeView->indexAt(pos);


        QMenu projectTreeViewMenu(ui->projectTreeView);
        projectTreeViewMenu.addAction(openFileAction);
        projectTreeViewMenu.addAction(newFileAction);
        projectTreeViewMenu.addAction(addExistingFileAction);
        projectTreeViewMenu.addAction(renameFileAction);
        projectTreeViewMenu.addAction(removeFileAction);
        projectTreeViewMenu.addSeparator();
        projectTreeViewMenu.addAction(closeProjectAction);
        projectTreeViewMenu.exec(QCursor::pos());
    });


    connect(projectSelectModel,&QItemSelectionModel::currentChanged,this,[=](const QModelIndex &current, const QModelIndex &previous){

    });


    connect(ui->projectTreeView,&QTreeView::clicked,this,[=](const QModelIndex &index){

    });






    connect(ui->spaceTabPage,&SpaceTabWidget::hasTab,this,[=]{
        ui->stackedWidget->setCurrentWidget(ui->spaceTabPage);
    });
    connect(ui->spaceTabPage,&SpaceTabWidget::noTab,this,[=]{
        ui->stackedWidget->setCurrentWidget(ui->welcomePage);
    });
    connect(ui->spaceTabPage,&SpaceTabWidget::clickedTabBar,this,[=](QFileInfo fileInfo){
        qDebug()<<"clicked:"<<fileInfo;

        if(fileInfo.suffix()=="xplayer"){
            QStandardItem *rootItem =  projectModel->invisibleRootItem();
            for(int i = 0;i<rootItem->rowCount();++i){
                QStandardItem *projectItem = rootItem->child(i);
                for(int i = 0;i<projectItem->rowCount();++i){
                    QStandardItem *elemItem = projectItem->child(i);
                    if(elemItem->data(Qt::UserRole+2).toString()==fileInfo.absoluteFilePath()){
                        ui->projectTreeView->setCurrentIndex(elemItem->index());
                        ui->projectTreeView->expand(projectItem->index());
                        break;
                    }
                }
            }
        }
        else{
            QStandardItem *rootItem =  projectModel->invisibleRootItem();
            for(int i = 0;i<rootItem->rowCount();++i){
                QStandardItem *projectItem = rootItem->child(i);
                for(int i = 0;i<projectItem->rowCount();++i){
                    QStandardItem *elemItem = projectItem->child(i);
                    for(int i = 0;i<elemItem->rowCount();++i){
                        QStandardItem *fileItem = elemItem->child(i);
                        if(fileItem->data(Qt::UserRole+2).toString()==fileInfo.absoluteFilePath()){
                            ui->projectTreeView->setCurrentIndex(fileItem->index());
                            ui->projectTreeView->expand(elemItem->index());
                            ui->projectTreeView->expand(projectItem->index());
                            break;
                        }
                    }
                }
            }
        }



        return;
    });

    connect(this,&MainWindow::openSpaceFile,ui->spaceTabPage,&SpaceTabWidget::openSpaceFile);
    connect(this,&MainWindow::closeSpaceFile,ui->spaceTabPage,&SpaceTabWidget::closeSpaceFile);


    connect(ui->projectTreeView,&QTreeView::doubleClicked,this,[=](const QModelIndex &index){
        qDebug()<<index.data(Qt::UserRole+1)<<index.data(Qt::UserRole+2);

        if(index.data(Qt::UserRole+1).toString()=="file"){
            QFileInfo spaceFileInfo(index.data(Qt::UserRole+2).toString());
            QStandardItem *spaceFileItem = projectModel->itemFromIndex(index);
            spaceFileItem->setData("open",Qt::UserRole+3);
            emit openSpaceFile(spaceFileInfo);
        }
    });
}





void MainWindow::getDirContents(QDir dir,QStandardItem *parentItem)
{

    QFileInfoList fileInfoList = dir.entryInfoList(QDir::AllDirs|QDir::Files|QDir::NoDotAndDotDot,QDir::DirsFirst|QDir::Reversed);


    for (const QFileInfo &fileInfo:fileInfoList) {
        if(fileInfo.isDir()){
            //QStandardItem *dirItem = new QStandardItem(QIcon(this->style()->standardIcon(QStyle::SP_DirIcon)),fileInfo.fileName());
            QStandardItem *dirItem = new QStandardItem(folderIcon,fileInfo.fileName());
            dirItem->setData(QString("folder"),Qt::UserRole+1);
            parentItem->appendRow(dirItem);
            QDir dir(fileInfo.filePath());
            getDirContents(dir,dirItem);
        }
        else{
            QStandardItem *fileItem = new QStandardItem(QIcon(this->style()->standardIcon(QStyle::SP_FileIcon)),fileInfo.fileName());
            fileItem->setData(QString("file"),Qt::UserRole+1);
            parentItem->appendRow(fileItem);
        }
    }
}


void MainWindow::parseProjectConfigFile(QFileInfo projectConfigFileInfo)
{

    //check dup projectConfigFile project
    QStandardItem *rootItem = projectModel->invisibleRootItem();
    for(int i = 0;i<rootItem->rowCount();++i){
        QStandardItem *projectFolderItem = rootItem->child(i);
        QString projectIdentity = projectFolderItem->data(Qt::UserRole+2).toString()+QDir::separator()+projectFolderItem->text()+".xplayer";
        if(projectIdentity == projectConfigFileInfo.absoluteFilePath()){
            //this project is already open,parse config jsonfile to insert new space file and new playlist file to the model.
            QFile projectConfigFile(projectConfigFileInfo.absoluteFilePath());
            if(projectConfigFile.open(QFile::ReadOnly)){
                QByteArray jsonData = projectConfigFile.readAll();
                QJsonParseError jsonError;
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&jsonError);
                if(jsonError.error==QJsonParseError::NoError && !jsonDoc.isNull()){
                    QJsonObject rootJsonObject = jsonDoc.object();
                    QJsonObject projectJsonObject = rootJsonObject.value("project").toObject();


                    QJsonArray spacesJsonArray = rootJsonObject.value("spaces").toArray();
                    QJsonArray playlistsJsonArray = rootJsonObject.value("playlists").toArray();


                    for(int i = 0;i<projectFolderItem->rowCount();++i){
                        QStandardItem *elementItem = projectFolderItem->child(i);
                        //space
                        if(elementItem->text()=="spaces"){
                            //step1:remove viewitem that is not in json
                            for(int i = 0;i<elementItem->rowCount();){
                                QStandardItem *fileItem = elementItem->child(i);
                                int j = 0;
                                for(j = 0;j<spacesJsonArray.count();++j){
                                    if(spacesJsonArray.at(j).toString()==fileItem->data(Qt::UserRole+2)){
                                        break;
                                    }
                                }
                                if(j==spacesJsonArray.count()){
                                    elementItem->removeRow(i);
                                }
                                else{
                                    i++;
                                }
                            }


                            //step2:add viewitem that is new in json
                            for (const QJsonValue &value: spacesJsonArray) {
                                int i = 0;
                                for(i = 0;i<elementItem->rowCount();++i){
                                    QStandardItem *fileItem = elementItem->child(i);
                                    if(fileItem->data(Qt::UserRole+2).toString()==value.toString()){
                                        break;
                                    }
                                }
                                if(i==elementItem->rowCount()){
                                    QFileInfo spaceFileInfo(value.toString());
                                    QStandardItem *spaceItem = new QStandardItem(spaceIcon,spaceFileInfo.fileName());
                                    spaceItem->setData("file",Qt::UserRole+1);
                                    spaceItem->setData(spaceFileInfo.absoluteFilePath(),Qt::UserRole+2);
                                    spaceItem->setData("close",Qt::UserRole+3);
                                    spaceItem->setToolTip(spaceFileInfo.absoluteFilePath());
                                    elementItem->appendRow(spaceItem);
                                }
                            }
                            ui->projectTreeView->expand(elementItem->index());
                        }
                        //playlists
                        if(elementItem->text()=="playlists"){
                            //step1:remove viewitem that is not in json
                            for(int i = 0;i<elementItem->rowCount();){
                                QStandardItem *fileItem = elementItem->child(i);
                                int j = 0;
                                for(j = 0;j<playlistsJsonArray.count();++j){
                                    if(playlistsJsonArray.at(j).toString()==fileItem->data(Qt::UserRole+2)){
                                        break;
                                    }
                                }
                                if(j==playlistsJsonArray.count()){
                                    elementItem->removeRow(i);
                                }
                                else{
                                    i++;
                                }
                            }


                            //step2:add viewitem that is new in json
                            for (const QJsonValue &value: playlistsJsonArray) {
                                int i = 0;
                                for(i = 0;i<elementItem->rowCount();++i){
                                    QStandardItem *fileItem = elementItem->child(i);
                                    if(fileItem->data(Qt::UserRole+2).toString()==value.toString()){
                                        break;
                                    }
                                }
                                if(i==elementItem->rowCount()){
                                    QFileInfo playListFileInfo(value.toString());
                                    QStandardItem *playListItem = new QStandardItem(playlistIcon,playListFileInfo.fileName());
                                    playListItem->setData("file",Qt::UserRole+1);
                                    playListItem->setData(playListFileInfo.absoluteFilePath(),Qt::UserRole+2);
                                    playListItem->setData("close",Qt::UserRole+3);
                                    playListItem->setToolTip(playListFileInfo.absoluteFilePath());
                                    elementItem->appendRow(playListItem);
                                }
                            }
                            ui->projectTreeView->expand(elementItem->index());
                        }
                    }
                }
                projectConfigFile.close();
            }

            ui->projectTreeView->expand(projectFolderItem->index());
            return;
        }
    }



    //open a project that has not been opened
    QFile projectConfigFile(projectConfigFileInfo.absoluteFilePath());
    if(projectConfigFile.open(QFile::ReadOnly)){
        QByteArray jsonData = projectConfigFile.readAll();
        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&jsonError);
        if(jsonError.error==QJsonParseError::NoError && !jsonDoc.isNull()){
            QJsonObject rootJsonObject = jsonDoc.object();
            QJsonObject projectJsonObject = rootJsonObject.value("project").toObject();
            QString projectName = projectConfigFileInfo.baseName();


            QJsonArray spacesJsonArray = rootJsonObject.value("spaces").toArray();
            QJsonArray playlistsJsonArray = rootJsonObject.value("playlists").toArray();






            //project
            QStandardItem *projectFolderItem = new QStandardItem(folderIcon,projectName);
            projectFolderItem->setData(QString("folder"),Qt::UserRole+1);
            projectFolderItem->setData(projectConfigFileInfo.absolutePath(),Qt::UserRole+2);
            projectFolderItem->setToolTip(projectConfigFileInfo.absolutePath());
            projectModel->appendRow(projectFolderItem);



            //configFile
            QStandardItem *configFileItem = new QStandardItem(configFileIcon,projectConfigFileInfo.fileName());
            configFileItem->setData("file",Qt::UserRole+1);
            configFileItem->setData(projectConfigFileInfo.absoluteFilePath(),Qt::UserRole+2);
            configFileItem->setData("close",Qt::UserRole+3);
            configFileItem->setToolTip(projectConfigFileInfo.absoluteFilePath());

            //spaces
            QStandardItem *spacesFolderItem = new QStandardItem(folderIcon,"spaces");
            spacesFolderItem->setData(QString("folder"),Qt::UserRole+1);
            spacesFolderItem->setData(projectConfigFileInfo.absolutePath(),Qt::UserRole+2);
            spacesFolderItem->setToolTip(projectConfigFileInfo.absolutePath());
            for (const QJsonValue &value: spacesJsonArray) {
                QFileInfo spaceFileInfo(value.toString());
                QStandardItem *spaceItem = new QStandardItem(spaceIcon,spaceFileInfo.fileName());
                spaceItem->setData("file",Qt::UserRole+1);
                spaceItem->setData(spaceFileInfo.absoluteFilePath(),Qt::UserRole+2);
                spaceItem->setData("close",Qt::UserRole+3);
                spaceItem->setToolTip(spaceFileInfo.absoluteFilePath());
                spacesFolderItem->appendRow(spaceItem);
            }


            //playlists
            QStandardItem *playlistsFolderItem = new QStandardItem(folderIcon,"playlists");
            playlistsFolderItem->setData(QString("folder"),Qt::UserRole+1);
            playlistsFolderItem->setData(projectConfigFileInfo.absolutePath(),Qt::UserRole+2);
            playlistsFolderItem->setToolTip(projectConfigFileInfo.absolutePath());
            for (const QJsonValue &value: playlistsJsonArray) {
                QFileInfo playListFileInfo(value.toString());
                QStandardItem *playListItem = new QStandardItem(playlistIcon,playListFileInfo.fileName());
                playListItem->setData("file",Qt::UserRole+1);
                playListItem->setData(playListFileInfo.absoluteFilePath(),Qt::UserRole+2);
                playListItem->setData("close",Qt::UserRole+3);
                playListItem->setToolTip(playListFileInfo.absoluteFilePath());
                playlistsFolderItem->appendRow(playListItem);
            }


            projectFolderItem->appendRow(spacesFolderItem);
            projectFolderItem->appendRow(playlistsFolderItem);
            projectFolderItem->appendRow(configFileItem);

            ui->projectTreeView->expand(projectFolderItem->index());
            ui->projectTreeView->expand(spacesFolderItem->index());
            ui->projectTreeView->expand(playlistsFolderItem->index());

            ui->projectTreeView->setCurrentIndex(projectFolderItem->index());



        }


        projectConfigFile.close();
    }
}





void MainWindow::slotNewProject()
{

    NewProjectDialog *newProjectDialog = new NewProjectDialog(this);
    connect(newProjectDialog,&NewProjectDialog::projectCreateComplete,this,[=](QFileInfo projectConfigFileInfo){
        parseProjectConfigFile(projectConfigFileInfo);
    });

    newProjectDialog->exec();
    newProjectDialog->deleteLater();




}

void MainWindow::slotOpenProject()
{
    QString projectConfigFilePath = QFileDialog::getOpenFileName(this,tr("Open Project"),QDir::homePath()+"/xplayerproject",tr("xplayer (*.xplayer)"));
    QFileInfo projectConfigFileInfo(projectConfigFilePath);
    if(!projectConfigFilePath.isEmpty()){
        parseProjectConfigFile(projectConfigFileInfo);
    }

}

void MainWindow::slotCloseProject()
{
    //up find project root folder
    QModelIndex modelIndex = ui->projectTreeView->currentIndex();
    while(modelIndex.parent().model()!=nullptr){
        modelIndex = modelIndex.parent();
    }

    //close all opened file of this project
    QStandardItem *projectItem = projectModel->itemFromIndex(modelIndex);
    for(int i = 0;i<projectItem->rowCount();++i){
        QStandardItem *elemItem = projectItem->child(i);
        if(elemItem->data(Qt::UserRole+1).toString()=="file"){
            if(elemItem->data(Qt::UserRole+3).toString()=="open"){
                emit closeSpaceFile(QFileInfo(elemItem->data(Qt::UserRole+2).toString()));
                //elemItem->setData("close",Qt::UserRole+3);
            }
        }
        else{
            for(int i = 0;i<elemItem->rowCount();++i){
                QStandardItem *fileItem = elemItem->child(i);
                if(fileItem->data(Qt::UserRole+3).toString()=="open"){
                    emit closeSpaceFile(QFileInfo(fileItem->data(Qt::UserRole+2).toString()));
                    //fileItem->setData("close",Qt::UserRole+3);
                }
            }
        }
    }

    //remove project view from projectTreeView
    projectModel->removeRow(modelIndex.row());

}

void MainWindow::closeProjectByProjectConfigFileInfo(QFileInfo projectConfigFileInfo){
    QStandardItem *rootItem =  projectModel->invisibleRootItem();
    for(int i = 0;i<rootItem->rowCount();++i){
        QStandardItem *projectItem = rootItem->child(i);
        for(int i = 0;i<projectItem->rowCount();++i){
            QStandardItem *elemItem = projectItem->child(i);
            if(elemItem->data(Qt::UserRole+2).toString()==projectConfigFileInfo.absoluteFilePath()){
                qDebug()<<projectItem->row();
                projectModel->removeRow(projectItem->row());
                break;
            }
        }
    }
};



void MainWindow::slotNewFile()
{

    //find project root folder
    QModelIndex modelIndex = ui->projectTreeView->currentIndex();
    while(modelIndex.parent().model()!=nullptr){
        modelIndex = modelIndex.parent();
    }

    //defaultSaveDir
    QDir defaultSaveDir(modelIndex.data(Qt::UserRole+2).toString());
    qDebug()<<defaultSaveDir.absolutePath();







    //new file Dialog
    NewFileDialog *newFileDialog = new NewFileDialog(defaultSaveDir,this);
    connect(newFileDialog,&NewFileDialog::fileCreateComplete,this,[=](QFileInfo newFileInfo){
        //find projectConfigFile
        QStandardItem *item = projectModel->itemFromIndex(modelIndex);
        QFileInfo projectConfigFileInfo;
        for(int i = 0;i<item->rowCount();++i){
            if(item->child(i)->text().contains(".xplayer")){
                projectConfigFileInfo.setFile(item->child(i)->data(Qt::UserRole+2).toString());
                break;
            }
        }

        //read project json file
        QFile projectConfigFile(projectConfigFileInfo.absoluteFilePath());
        if(projectConfigFile.open(QFile::ReadOnly)){
            QByteArray jsonData = projectConfigFile.readAll();
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&jsonError);
            if(jsonError.error==QJsonParseError::NoError&&!jsonDoc.isNull()){
                projectConfigFile.close();

                //update jsonDoc and write to jsonfile
                if(projectConfigFile.open(QFile::WriteOnly)){
                    QJsonObject rootJsonObject = jsonDoc.object();//new
                    if(newFileInfo.suffix()=="space"){
                        QJsonArray spacesJsonArray = rootJsonObject.value("spaces").toArray();
                        spacesJsonArray.append(QJsonValue(newFileInfo.filePath()));
                        rootJsonObject["spaces"] = spacesJsonArray;
                    }
                    else if(newFileInfo.suffix()=="playlist"){
                        QJsonArray playlistsJsonArray = rootJsonObject.value("playlists").toArray();
                        playlistsJsonArray.append(QJsonValue(newFileInfo.filePath()));
                        rootJsonObject["playlists"]=playlistsJsonArray;
                    }
                    jsonDoc.setObject(rootJsonObject);
                    projectConfigFile.write(jsonDoc.toJson());
                    projectConfigFile.close();
                }
            }
            projectConfigFile.close();
        }
        parseProjectConfigFile(projectConfigFileInfo);

    });



    newFileDialog->exec();
    newFileDialog->deleteLater();



}

void MainWindow::slotAddExistingFile()
{
    //find project root folder
    QModelIndex modelIndex = ui->projectTreeView->currentIndex();
    while(modelIndex.parent().model()!=nullptr){
        modelIndex = modelIndex.parent();
    }

    //choose existing files
    QStringList openFilesAbsoluteFilePath = QFileDialog::getOpenFileNames(this,"Add Existing File",QDir::homePath(),"space (*.space);;playlist (*.playlist)");
    for(const QString &absoluteFilePath : openFilesAbsoluteFilePath){
        QFileInfo newFileInfo(absoluteFilePath);

        //find projectConfigFile by projectfolder
        QStandardItem *item = projectModel->itemFromIndex(modelIndex);
        QFileInfo projectConfigFileInfo;
        for(int i = 0;i<item->rowCount();++i){
            if(item->child(i)->text().contains(".xplayer")){
                projectConfigFileInfo.setFile(item->child(i)->data(Qt::UserRole+2).toString());
                break;
            }
        }

        //read project json file
        QFile projectConfigFile(projectConfigFileInfo.absoluteFilePath());
        if(projectConfigFile.open(QFile::ReadOnly)){
            QByteArray jsonData = projectConfigFile.readAll();
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&jsonError);
            if(jsonError.error==QJsonParseError::NoError&&!jsonDoc.isNull()){
                projectConfigFile.close();

                //update jsonDoc and write to jsonfile
                if(projectConfigFile.open(QFile::WriteOnly)){
                    QJsonObject rootJsonObject = jsonDoc.object();//new
                    if(newFileInfo.suffix()=="space"){
                        QJsonArray spacesJsonArray = rootJsonObject.value("spaces").toArray();
                        //check if this spacefile is already in configFile
                        int i = 0;
                        for(i = 0;i<spacesJsonArray.count();++i){
                            QJsonValue value = spacesJsonArray.at(i);
                            if(value.toString()==newFileInfo.absoluteFilePath()){
                                break;
                            }
                        }
                        if(i==spacesJsonArray.count()){
                            spacesJsonArray.append(QJsonValue(newFileInfo.absoluteFilePath()));
                            rootJsonObject["spaces"] = spacesJsonArray;
                        }
                    }
                    else if(newFileInfo.suffix()=="playlist"){
                        QJsonArray playlistsJsonArray = rootJsonObject.value("playlists").toArray();
                        int i = 0;
                        for(i = 0;i<playlistsJsonArray.count();++i){
                            QJsonValue value = playlistsJsonArray.at(i);
                            if(value.toString()==newFileInfo.absoluteFilePath()){
                                break;
                            }
                        }
                        if(i==playlistsJsonArray.count()){
                            playlistsJsonArray.append(QJsonValue(newFileInfo.filePath()));
                            rootJsonObject["playlists"]=playlistsJsonArray;
                        }
                    }
                    jsonDoc.setObject(rootJsonObject);
                    projectConfigFile.write(jsonDoc.toJson());
                    projectConfigFile.close();
                }
            }
            projectConfigFile.close();
        }
        parseProjectConfigFile(projectConfigFileInfo);
    }

}

void MainWindow::slotRemoveFile()
{
    QModelIndex removedIndex = ui->projectTreeView->currentIndex();
    QFileInfo removedFileInfo(removedIndex.data(Qt::UserRole+2).toString());

    RemoveFileDialog *removeFileDialog = new RemoveFileDialog(removedFileInfo,this);
    connect(removeFileDialog,&RemoveFileDialog::removePermanently,this,[=](bool permanently){
        //find project root folder
        QModelIndex modelIndex = ui->projectTreeView->currentIndex();
        while(modelIndex.parent().model()!=nullptr){
            modelIndex = modelIndex.parent();
        }

        //find projectConfigFile
        QStandardItem *item = projectModel->itemFromIndex(modelIndex);
        QFileInfo projectConfigFileInfo;
        for(int i = 0;i<item->rowCount();++i){
            if(item->child(i)->text().contains(".xplayer")){
                projectConfigFileInfo.setFile(item->child(i)->data(Qt::UserRole+2).toString());
                break;
            }
        }

        //read project json file
        QFile projectConfigFile(projectConfigFileInfo.absoluteFilePath());
        if(projectConfigFile.open(QFile::ReadOnly)){
            QByteArray jsonData = projectConfigFile.readAll();
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&jsonError);
            if(jsonError.error==QJsonParseError::NoError&&!jsonDoc.isNull()){
                projectConfigFile.close();

                //update jsonDoc and write to jsonfile
                if(projectConfigFile.open(QFile::WriteOnly)){
                    QJsonObject rootJsonObject = jsonDoc.object();//new
                    if(removedFileInfo.suffix()=="space"){
                        QJsonArray spacesJsonArray = rootJsonObject.value("spaces").toArray();
                        for(int i = 0;i<spacesJsonArray.count();++i){
                            if(spacesJsonArray.at(i).toString()==removedFileInfo.absoluteFilePath()){
                                spacesJsonArray.removeAt(i);
                                break;
                            }
                        }
                        rootJsonObject["spaces"] = spacesJsonArray;
                    }
                    else if(removedFileInfo.suffix()=="playlist"){
                        QJsonArray playlistsJsonArray = rootJsonObject.value("playlists").toArray();
                        for(int i = 0;i<playlistsJsonArray.count();++i){
                            if(playlistsJsonArray.at(i).toString()==removedFileInfo.absoluteFilePath()){
                                playlistsJsonArray.removeAt(i);
                                break;
                            }
                        }
                        rootJsonObject["playlists"]=playlistsJsonArray;
                    }
                    jsonDoc.setObject(rootJsonObject);
                    projectConfigFile.write(jsonDoc.toJson());
                    projectConfigFile.close();
                }
            }
            projectConfigFile.close();
        }
        //if this file is delete from disk
        if(permanently){
            emit closeSpaceFile(removedFileInfo);
        }
        parseProjectConfigFile(projectConfigFileInfo);

    });

    connect(removeFileDialog,&QDialog::rejected,this,[=]{

    });




    removeFileDialog->exec();
    removeFileDialog->deleteLater();




//    QModelIndex deleteIndex = ui->projectTreeView->currentIndex();
//    projectModel->removeRow(deleteIndex.row(),deleteIndex.parent());
//    return;



//    //find project root folder
//    QModelIndex modelIndex = ui->projectTreeView->currentIndex();
//    while(modelIndex.parent().model()!=nullptr){
//        modelIndex = modelIndex.parent();
//    }



}







MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupUi()
{

    // auto hide dock titlebar QAction
    autoHideDockTitleBar = new QAction(tr("Automatically Hide View Title Bars"));
    autoHideDockTitleBar->setCheckable(true);


    // create new project QAction
    newProjectAction = new QAction(tr("New Project"), this);
    newProjectAction->setShortcut(QKeySequence("Ctrl+N"));





    // 创建保存项目的 QAction
    saveProjectAction = new QAction(tr("Save Project"), this);
    saveProjectAction->setShortcut(QKeySequence("Ctrl+S"));


    // 创建保存项目为新文件的 QAction
    saveAsProjectAction = new QAction(tr("Save Project As..."), this);
    saveAsProjectAction->setShortcut(QKeySequence("Ctrl+Shift+S"));


    // 创建重命名项目的 QAction
    renameProjectAction = new QAction(tr("Rename Project"), this);
    renameProjectAction->setShortcut(QKeySequence("Ctrl+R"));


    // 创建删除项目的 QAction
    deleteProjectAction = new QAction(tr("Delete Project"), this);
    deleteProjectAction->setShortcut(QKeySequence("Ctrl+D"));

    // close project QAction
    closeProjectAction = new QAction(tr("Close Project"),this);
    closeProjectAction->setShortcut(QKeySequence("Ctrl+C"));

    // active project QAction
    activeProjectAction = new QAction(tr("Active Project"),this);

    // open project QAction
    openProjectAction = new QAction(tr("Open Project"), this);
    openProjectAction->setShortcut(QKeySequence("Ctrl+O"));



    // open file QAction
    openFileAction = new QAction(tr("Open File"), this);
    openFileAction->setShortcut(QKeySequence("Ctrl+O"));

    // create new file QAction
    newFileAction = new QAction(tr("New File"), this);
    newFileAction->setShortcut(QKeySequence("Ctrl+Shift+N"));

    // add exsist file QAction
    addExistingFileAction = new QAction(tr("Add Existing File..."),this);

    // rename file QAction
    renameFileAction = new QAction(tr("Rename File"),this);


    // remove file QAction
    removeFileAction = new QAction(tr("Remove File"),this);



    // save file QAction
    saveFileAction = new QAction(tr("Save File"), this);
    saveFileAction->setShortcut(QKeySequence("Ctrl+S"));


    // 创建保存文件为新文件的 QAction
    saveAsFileAction = new QAction(tr("Save File As..."), this);
    saveAsFileAction->setShortcut(QKeySequence("Ctrl+Shift+S"));


    // 创建重命名文件的 QAction
    renameFileAction = new QAction(tr("Rename File"), this);
    renameFileAction->setShortcut(QKeySequence("Ctrl+R"));


    // 创建删除文件的 QAction
    deleteFileAction = new QAction(tr("Delete File"), this);
    deleteFileAction->setShortcut(QKeySequence("Ctrl+D"));


    // 创建添加文件到项目的 QAction
    addFileToProjectAction = new QAction(tr("Add Existing Files..."), this);
    addFileToProjectAction->setShortcut(QKeySequence("Ctrl+A"));


    // 创建从项目中移除文件的 QAction
    removeFileFromProjectAction = new QAction(tr("Remove File"), this);
    removeFileFromProjectAction->setShortcut(QKeySequence("Ctrl+R"));


    // 创建查看项目文件的 QAction
    viewProjectFilesAction = new QAction("查看项目文件", this);
    viewProjectFilesAction->setShortcut(QKeySequence("Ctrl+Shift+F"));


    // 创建文件排序的 QAction
    sortFilesAction = new QAction("文件排序", this);
    sortFilesAction->setShortcut(QKeySequence("Ctrl+Shift+O"));


    // 创建刷新项目树的 QAction
    refreshProjectTreeAction = new QAction("刷新项目树", this);
    refreshProjectTreeAction->setShortcut(QKeySequence("Ctrl+Shift+F5"));


    // 创建更新项目树的 QAction
    updateProjectTreeAction = new QAction("更新项目树", this);
    updateProjectTreeAction->setShortcut(QKeySequence("Ctrl+Shift+U"));





    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(addExistingFileAction);
    fileMenu->addAction(renameFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveAsFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(removeFileAction);

    projectMenu = menuBar()->addMenu(tr("Project"));
    projectMenu->addAction(newProjectAction);
    projectMenu->addAction(openProjectAction);
    projectMenu->addAction(renameProjectAction);
    projectMenu->addSeparator();
    projectMenu->addAction(saveProjectAction);
    projectMenu->addAction(saveAsProjectAction);
    projectMenu->addSeparator();
    projectMenu->addAction(closeProjectAction);




    viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->addAction(ui->projectListDockWidget->toggleViewAction());
    viewMenu->addAction(ui->mediaListDockWidget->toggleViewAction());
    viewMenu->addAction(ui->videoTrackDockWidget->toggleViewAction());
    viewMenu->addAction(ui->audioTrackDockWidget->toggleViewAction());
    viewMenu->addAction(ui->propertiesDockWidget->toggleViewAction());
    viewMenu->addAction(autoHideDockTitleBar);




    ui->propertiesDockWidget->setVisible(false);





    connect(autoHideDockTitleBar,&QAction::toggled,this,&MainWindow::slotAutoHideDockTitleBar);

    connect(newProjectAction, &QAction::triggered, this, &MainWindow::slotNewProject);
    connect(openProjectAction, &QAction::triggered, this, &MainWindow::slotOpenProject);
    connect(closeProjectAction,&QAction::triggered,this,&MainWindow::slotCloseProject);
    connect(newFileAction, &QAction::triggered, this, &MainWindow::slotNewFile);
    connect(addExistingFileAction,&QAction::triggered,this,&MainWindow::slotAddExistingFile);
    connect(removeFileAction,&QAction::triggered,this,&MainWindow::slotRemoveFile);


//    connect(saveProjectAction, &QAction::triggered, this, &MainWindow::slotSaveProject);
//    connect(saveAsProjectAction, &QAction::triggered, this, &MainWindow::slotSaveAsProject);
//    connect(renameProjectAction, &QAction::triggered, this, &MainWindow::slotRenameProject);


//    connect(openFileAction, &QAction::triggered, this, &MainWindow::slotOpenFile);
//    connect(saveFileAction, &QAction::triggered, this, &MainWindow::slotSaveFile);
//    connect(saveAsFileAction, &QAction::triggered, this, &MainWindow::slotSaveAsFile);
//    connect(renameFileAction, &QAction::triggered, this, &MainWindow::slotRenameFile);
//    connect(addFileToProjectAction, &QAction::triggered, this, &MainWindow::slotAddFileToProject);
//    connect(removeFileFromProjectAction, &QAction::triggered, this, &MainWindow::slotRemoveFileFromProject);
//    connect(viewProjectFilesAction, &QAction::triggered, this, &MainWindow::slotViewProjectFiles);
//    connect(sortFilesAction, &QAction::triggered, this, &MainWindow::slotSortFiles);
//    connect(refreshProjectTreeAction, &QAction::triggered, this, &MainWindow::slotRefreshProjectTree);
//    connect(updateProjectTreeAction, &QAction::triggered, this, &MainWindow::slotUpdateProjectTree);
//    connect(deleteFileAction, &QAction::triggered, this, &MainWindow::slotDeleteFile);

//    // 初始化工具栏
//    projectToolBar = addToolBar("项目");
//    projectToolBar->addAction(newProjectAction);
//    projectToolBar->addAction(newFileAction);
//    projectToolBar->addAction(openProjectAction);
//    projectToolBar->addAction(saveProjectAction);
//    projectToolBar->addAction(saveAsProjectAction);
//    projectToolBar->addAction(renameProjectAction);
//    projectToolBar->addAction(deleteProjectAction);
//    fileToolBar = addToolBar("文件");
//    fileToolBar->addAction(openFileAction);
//    fileToolBar->addAction(saveFileAction);
//    fileToolBar->addAction(saveAsFileAction);
//    fileToolBar->addAction(renameFileAction);
//    fileToolBar->addAction(deleteFileAction);
//    fileToolBar->addAction(addFileToProjectAction);
//    fileToolBar->addAction(removeFileFromProjectAction);
//    fileToolBar->addAction(viewProjectFilesAction);
//    fileToolBar->addAction(sortFilesAction);
//    fileToolBar->addAction(refreshProjectTreeAction);
//    fileToolBar->addAction(updateProjectTreeAction);

    // 初始化状态栏
    //statusBar()->showMessage("欢迎使用 Qt Creator！");
}

void MainWindow::slotAutoHideDockTitleBar(bool checked)
{
    if(checked){
        QWidget *newProjectListDockWidgetTitleBar = new QWidget;
        QWidget *newMediaListDockWidgetTitleBar = new QWidget;
        QWidget *newVideoTrackDockWidgetTitleBar = new QWidget;
        QWidget *newAudioTrackDockWidgetTitileBar = new QWidget;
        QWidget *newPropertiesDockWidgetTitleBar = new QWidget;
        ui->projectListDockWidget->setTitleBarWidget(newProjectListDockWidgetTitleBar);
        ui->mediaListDockWidget->setTitleBarWidget(newMediaListDockWidgetTitleBar);
        ui->videoTrackDockWidget->setTitleBarWidget(newVideoTrackDockWidgetTitleBar);
        ui->audioTrackDockWidget->setTitleBarWidget(newAudioTrackDockWidgetTitileBar);
        ui->propertiesDockWidget->setTitleBarWidget(newPropertiesDockWidgetTitleBar);
    }else{
        QWidget *tempProjectListDockWidgetTitleBar = ui->projectListDockWidget->titleBarWidget();
        QWidget *tempMediaListDockWidgetTitleBar = ui->mediaListDockWidget->titleBarWidget();
        QWidget *tempVideoTrackDockWidgetTitleBar = ui->videoTrackDockWidget->titleBarWidget();
        QWidget *tempAudioTrackDockWidgetTitleBar = ui->audioTrackDockWidget->titleBarWidget();
        QWidget *tempPropertiesDockWidgetTitleBar = ui->propertiesDockWidget->titleBarWidget();
        ui->projectListDockWidget->setTitleBarWidget(nullptr);
        ui->mediaListDockWidget->setTitleBarWidget(nullptr);
        ui->videoTrackDockWidget->setTitleBarWidget(nullptr);
        ui->audioTrackDockWidget->setTitleBarWidget(nullptr);
        ui->propertiesDockWidget->setTitleBarWidget(nullptr);
        tempProjectListDockWidgetTitleBar->deleteLater();
        tempMediaListDockWidgetTitleBar->deleteLater();
        tempVideoTrackDockWidgetTitleBar->deleteLater();
        tempAudioTrackDockWidgetTitleBar->deleteLater();
        tempPropertiesDockWidgetTitleBar->deleteLater();

    }
}



