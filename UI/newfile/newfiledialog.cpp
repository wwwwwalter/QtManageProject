#include "newfiledialog.h"
#include "ui_newfiledialog.h"

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

    model = new QStandardItemModel;
    ui->listView->setModel(model);

    QStandardItem *EmptyFileItem = new QStandardItem(QIcon(":images/folder_open.svb"),tr("Empty File"));
    QStandardItem *VideoSpaceItem = new QStandardItem(QIcon(":images/folder_open.svg"),tr("Video Space"));
    QStandardItem *AudioSpaceItem = new QStandardItem(QIcon(":images/folder_open.svg"),tr("Audio Space"));
    model->appendRow(EmptyFileItem);
    model->appendRow(VideoSpaceItem);
    model->appendRow(AudioSpaceItem);

}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}
