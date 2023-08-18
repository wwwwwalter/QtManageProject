#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

#include <QCloseEvent>
#include <QFileDialog>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
    setMinimumWidth(880);
    setWindowTitle(tr("Create new project"));


    ui->titlelabel->setFont(QFont(ui->titlelabel->font().family(),20,-1));


    //listview
    ui->widget_2->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    model = new QStandardItemModel;
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->listView->setStyleSheet(":/qss/listview.qss");

    ui->listView->setIconSize(QSize(30,30));

//    QString stylesheet = "";
//    stylesheet += "QListView::item:alternate {background-image: transparent; background-color: transparent;}";
//    stylesheet += "QListView::item:selected {background-image: transparent; background-color: transparent;padding: 0px;color: black;}";
//    stylesheet += "QListView::item:selected:active{background-image: transparent;background-color: transparent; color: black;}";
//    stylesheet += "QListView::item:selected:!active{background-image: transparent;background-color: transparent;color: black;}";
//    ui->listView->setStyleSheet(stylesheet);

    //add plugins to listview and stackedwidget
    FileForm *fileForm = new FileForm;
    VideoForm *videoForm = new VideoForm;
    AudioForm *audioForm = new AudioForm;

    model->appendRow(new QStandardItem(fileForm->getPluginIcon(),fileForm->getPluginName()));
    model->appendRow(new QStandardItem(videoForm->getPluginIcon(),videoForm->getPluginName()));
    model->appendRow(new QStandardItem(audioForm->getPluginIcon(),audioForm->getPluginName()));

    //stackedWidet
    while(ui->stackedWidget->currentWidget()){
        ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());
    }


    ui->stackedWidget->addWidget(fileForm);
    ui->stackedWidget->addWidget(videoForm);
    ui->stackedWidget->addWidget(audioForm);

    connect(ui->listView,&QListView::pressed,ui->stackedWidget,[&](const QModelIndex &index){
        ui->stackedWidget->setCurrentIndex(index.row());
    });



    //OK
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,[=]{
        //QWidget to AbstractPlug class
        //call virtural function
        QFileInfo projectConfigFileInfo =  static_cast<AbstrackPlugin*>(ui->stackedWidget->currentWidget())->doCreateProject();

        if(!projectConfigFileInfo.fileName().isEmpty()){
            emit projectCreateComplete(projectConfigFileInfo);
            this->accept();
        }
    });


    //Cancel
    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,[=]{
        this->reject();
    });










}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

QDir NewProjectDialog::getProjectDir()
{
    return projectDir;
}



