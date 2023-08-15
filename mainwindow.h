#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QMainWindow>
#include <QToolBar>
#include <QTreeView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



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

private slots:
    void slotNewProject();
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
    QTreeView *projectTreeView;
    QFileSystemModel *fileSystemModel;
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
    QDir projectDir;
    QString currentProjectName;
    QString currentFileName;
    bool isProjectOpen;
};

#endif
