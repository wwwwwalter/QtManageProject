#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QFileSystemWatcher>
#include <QMainWindow>
#include <QToolBar>
#include <QTreeView>
#include "UI/newproject/newprojectdialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupUi();



private:
    void newProject();
    void newFile();
    void openProject();
    void saveProject();
    void saveAsProject();
    void renameProject();
    void deleteProject();
    void openFile();
    void saveFile();
    void saveAsFile();
    void renameFile();
    void deleteFile();
    void addFileToProject();
    void removeFileFromProject();
    void viewProjectFiles();
    void sortFiles();
    void refreshProjectTree();
    void updateProjectTree();
    void addProjectToProjectTree(QDir projectDir);
    void getDirContents(QDir dir,QStandardItem *parentItem);


private slots:
    void slotNewProject();
    void slotNewFile();
    void slotOpenProject();
//    void slotSaveProject();
//    void slotSaveAsProject();
//    void slotRenameProject();
//    void slotDeleteProject();
//    void slotOpenFile();
//    void slotSaveFile();
//    void slotSaveAsFile();
//    void slotRenameFile();
//    void slotDeleteFile();
//    void slotAddFileToProject();
//    void slotRemoveFileFromProject();
//    void slotViewProjectFiles();
//    void slotSortFiles();
    void slotRefreshProjectTree();
//    void slotUpdateProjectTree();

private:
    QTreeView *fileSystemTreeView;
    QFileSystemModel *fileSystemModel;
    QFileSystemWatcher *fileSystemWatcher;
    QDir fileSystemDir;

    QTreeView *projectTreeView;
    QStandardItemModel *projectModel;
    QDir projectDir;


    QTreeView *fileTreeView;
    QLineEdit *projectNameEdit;
    QLineEdit *fileNameEdit;
    QFileDialog *openFileDialog;
    QFileDialog *saveFileDialog;
    QFileDialog *saveAsFileDialog;
    QFileDialog *fileDialog;
    QMenu *fileMenu;
    QMenu *projectMenu;
    QAction *newProjectAction;
    QAction *newFileAction;
    QAction *openProjectAction;
    QAction *saveProjectAction;
    QAction *saveAsProjectAction;
    QAction *renameProjectAction;
    QAction *deleteProjectAction;
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *saveAsFileAction;
    QAction *renameFileAction;
    QAction *deleteFileAction;
    QAction *addFileToProjectAction;
    QAction *removeFileFromProjectAction;
    QAction *viewProjectFilesAction;
    QAction *sortFilesAction;
    QAction *refreshProjectTreeAction;
    QAction *updateProjectTreeAction;
    QToolBar *fileToolBar;
    QToolBar *projectToolBar;
    QString currentProjectName;
    QString currentFileName;
    bool isProjectOpen;

    QDir currentProjectDir;
    void setCurrentProjectDir(QDir projectDir);


};

#endif
