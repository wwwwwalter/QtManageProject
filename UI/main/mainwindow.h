#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QFileSystemWatcher>
#include <QMainWindow>
#include <QToolBar>
#include <QTreeView>
#include <QStandardItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupUi();



private slots:
    //    void slotNewProject();
    //    void slotNewFile();
    //    void slotOpenProject();
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
    //    void slotRefreshProjectTree();
    //    void slotUpdateProjectTree();

private:
    //fileSystemModel
    QDir fileSystemRootDir;
    QFileSystemModel *fileSystemModel;



    //projectModel
    QStandardItemModel *projectModel;
    QModelIndex activeProjectModelIndex;
    QModelIndex selectedItemModelIndex;


    //第一等级函数
private slots:
    void slotNewProject();
    void slotOpenProject();
    void slotCloseProject();
    void slotActiveProject();
    void slotNewFile();



    //第二等级函数
private:
    void addProjectToProjectTree(QDir projectDir);
    void getDirContents(QDir dir,QStandardItem *parentItem);


private:
    //Icon
    QIcon folderIcon;



private:


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

    QAction *saveProjectAction;
    QAction *saveAsProjectAction;
    QAction *renameProjectAction;
    QAction *deleteProjectAction;
    QAction *closeProjectAction;
    QAction *activeProjectAction;
    QAction *openProjectAction;

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



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
