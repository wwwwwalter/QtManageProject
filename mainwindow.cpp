#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // 创建菜单栏和子菜单
    fileMenu = new QMenu("文件", this);
    projectMenu = new QMenu("项目", this);
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(projectMenu);

    // 创建新项目的 QAction
    newProjectAction = new QAction("新建项目", this);
    newProjectAction->setShortcut(QKeySequence("Ctrl+N"));


    // 创建新文件的 QAction
    newFileAction = new QAction("新建文件", this);
    newFileAction->setShortcut(QKeySequence("Ctrl+Shift+N"));


    // 创建打开项目的 QAction
    openProjectAction = new QAction("打开项目", this);
    openProjectAction->setShortcut(QKeySequence("Ctrl+O"));


    // 创建保存项目的 QAction
    saveProjectAction = new QAction("保存项目", this);
    saveProjectAction->setShortcut(QKeySequence("Ctrl+S"));


    // 创建保存项目为新文件的 QAction
    saveAsProjectAction = new QAction("保存为新项目", this);
    saveAsProjectAction->setShortcut(QKeySequence("Ctrl+Shift+S"));


    // 创建重命名项目的 QAction
    renameProjectAction = new QAction("重命名项目", this);
    renameProjectAction->setShortcut(QKeySequence("Ctrl+R"));


    // 创建删除项目的 QAction
    deleteProjectAction = new QAction("删除项目", this);
    deleteProjectAction->setShortcut(QKeySequence("Ctrl+D"));


    // 创建打开文件的 QAction
    openFileAction = new QAction("打开文件", this);
    openFileAction->setShortcut(QKeySequence("Ctrl+O"));


    // 创建保存文件的 QAction
    saveFileAction = new QAction("保存文件", this);
    saveFileAction->setShortcut(QKeySequence("Ctrl+S"));


    // 创建保存文件为新文件的 QAction
    saveAsFileAction = new QAction("保存为新文件", this);
    saveAsFileAction->setShortcut(QKeySequence("Ctrl+Shift+S"));


    // 创建重命名文件的 QAction
    renameFileAction = new QAction("重命名文件", this);
    renameFileAction->setShortcut(QKeySequence("Ctrl+R"));


    // 创建删除文件的 QAction
    deleteFileAction = new QAction("删除文件", this);
    deleteFileAction->setShortcut(QKeySequence("Ctrl+D"));


    // 创建添加文件到项目的 QAction
    addFileToProjectAction = new QAction("添加文件到项目", this);
    addFileToProjectAction->setShortcut(QKeySequence("Ctrl+A"));


    // 创建从项目中移除文件的 QAction
    removeFileFromProjectAction = new QAction("从项目中移除文件", this);
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



    fileMenu = menuBar()->addMenu("文件");
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveAsFileAction);
    fileMenu->addAction(renameFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(addFileToProjectAction);
    fileMenu->addAction(removeFileFromProjectAction);
    fileMenu->addSeparator();
    fileMenu->addAction(viewProjectFilesAction);
    fileMenu->addSeparator();
    fileMenu->addAction(sortFilesAction);
    fileMenu->addSeparator();
    fileMenu->addAction(refreshProjectTreeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(updateProjectTreeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(deleteFileAction);

    projectMenu = menuBar()->addMenu("项目");
    projectMenu->addAction(newProjectAction);
    projectMenu->addAction(openProjectAction);
    projectMenu->addAction(saveProjectAction);
    projectMenu->addAction(saveAsProjectAction);
    projectMenu->addAction(renameProjectAction);
    projectMenu->addSeparator();
    projectMenu->addAction(deleteProjectAction);

    connect(newProjectAction, &QAction::triggered, this, &MainWindow::slotNewProject);
//    connect(newFileAction, &QAction::triggered, this, &MainWindow::slotNewFile);
//    connect(openProjectAction, &QAction::triggered, this, &MainWindow::slotOpenProject);
//    connect(saveProjectAction, &QAction::triggered, this, &MainWindow::slotSaveProject);
//    connect(saveAsProjectAction, &QAction::triggered, this, &MainWindow::slotSaveAsProject);
//    connect(renameProjectAction, &QAction::triggered, this, &MainWindow::slotRenameProject);
//    connect(deleteProjectAction, &QAction::triggered, this, &MainWindow::slotDeleteProject);
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

    // 初始化工具栏
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
    statusBar()->showMessage("欢迎使用 Qt Creator！");

    // 初始化项目目录
    projectDir = QDir::homePath();
    qDebug()<<projectDir.path();
    currentProjectName = "";
    isProjectOpen = false;




    //widget
    QWidget *w = new QWidget;
    setCentralWidget(w);
    QVBoxLayout *vboxlayout = new QVBoxLayout;
    w->setLayout(vboxlayout);





    // 初始化项目树视图
    projectTreeView = new QTreeView;
    fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath(QDir::homePath());
    projectTreeView->setModel(fileSystemModel);
    projectTreeView->setRootIndex(fileSystemModel->index(QDir::homePath()));
    //setCentralWidget(projectTreeView);

    projectTreeView->setColumnWidth(0,300);

    vboxlayout->addWidget(projectTreeView);




    //projectTreeView->setHorizontalHeaderLabels(QStringList() << "文件夹" << "文件名");
    //projectTreeView->setColumnWidth(0, 200);
    //projectTreeView->setColumnWidth(1, 200);
    setCentralWidget(projectTreeView);

    // 初始化文件树视图
    fileTreeView = new QTreeView(this);
    fileTreeView->setModel(fileSystemModel);
    fileTreeView->setRootIndex(fileSystemModel->index(QDir::homePath()));
    //fileTreeView->setHorizontalHeaderLabels(QStringList() << "文件夹" << "文件名");
    //fileTreeView->setColumnWidth(0, 200);
    //fileTreeView->setColumnWidth(1, 200);
    //setCentralWidget(fileTreeView);





//    connect(fileTreeView, &QTreeView::clicked, this, &MainWindow::slotOpenFile);
//    connect(fileTreeView, &QTreeView::doubleClicked, this, &MainWindow::slotOpenFile);






}

MainWindow::~MainWindow()
{
}

void MainWindow::slotNewProject()
{
    // 新建项目
    currentProjectName = QFileDialog::getSaveFileName(this, "新建项目", projectDir.path(), "Qt 项目(*.qpr)");
    if (!currentProjectName.isEmpty()) {
        // 创建项目文件
        QFile projectFile(currentProjectName);
        if (projectFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&projectFile);
            stream << "Qt 项目\n";
            projectFile.close();
            // 更新项目树视图
            //refreshProjectTree();
        } else {
            QMessageBox::critical(this, "错误", "无法创建项目文件");
        }
    }
}

