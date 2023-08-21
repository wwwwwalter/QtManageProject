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
    QItemSelectionModel *projectSelectModel;




    //第一等级函数
private slots:
    void slotAutoHideDockTitleBar(bool checked);
    void slotNewProject();
    void slotOpenProject();
    void slotCloseProject();
    void closeProjectByProjectConfigFileInfo(QFileInfo projectConfigFileInfo);
    void slotNewFile();




    //第二等级函数
private:
    void getDirContents(QDir dir,QStandardItem *parentItem);
    void parseProjectConfigFile(QFileInfo projectConfigFileInfo);




private:
    //Icon
    QIcon logoIcon;
    QIcon folderIcon;
    QIcon spaceIcon;
    QIcon playlistIcon;
    QIcon configFileIcon;



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
    QMenu *viewMenu;

    QAction *autoHideDockTitleBar;



    QAction *saveProjectAction;
    QAction *saveAsProjectAction;
    QAction *renameProjectAction;

    QAction *newProjectAction;
    QAction *deleteProjectAction;
    QAction *closeProjectAction;
    QAction *activeProjectAction;
    QAction *openProjectAction;

    QAction *openFileAction;
    QAction *newFileAction;
    QAction *addExistsFileAction;
    QAction *renameFileAction;
    QAction *removeFileAction;




    QAction *saveFileAction;
    QAction *saveAsFileAction;
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



private:
    Ui::MainWindow *ui;

signals:
    void openSpaceFile(QFileInfo spaceFileInfo);
    void closeSpaceFile(QFileInfo spaceFileInfo);



};

#endif // MAINWINDOW_H
