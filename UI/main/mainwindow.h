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

    void slotOpenFile();
    void slotNewFile();
    void slotAddExistingFile();
    void slotSortFiles();
    void slotRenameFile();
    void slotSaveFile();
    void slotSaveFileAs();
    void slotRemoveFile();

    void slotNewProject();
    void slotOpenProject();
    void slotRenameProject();
    void slotRefreshProject();
    void slotSaveProject();
    void slotCloseProject();
    void closeProjectByProjectConfigFileInfo(QFileInfo projectConfigFileInfo);






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



    QAction *openFileAction;
    QAction *newFileAction;
    QAction *addExistingFileAction;
    QAction *sortFilesAction;
    QAction *renameFileAction;
    QAction *saveFileAction;
    QAction *saveFileAsAction;
    QAction *removeFileAction;



    QAction *openProjectAction;
    QAction *newProjectAction;
    QAction *renameProjectAction;
    QAction *refreshProjectTreeAction;
    QAction *saveProjectAction;
    QAction *closeProjectAction;












    QToolBar *fileToolBar;
    QToolBar *projectToolBar;




private:
    Ui::MainWindow *ui;

signals:
    void openSpaceFile(QFileInfo spaceFileInfo);
    void closeSpaceFile(QFileInfo spaceFileInfo);



};

#endif // MAINWINDOW_H
