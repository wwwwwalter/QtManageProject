#include "removefiledialog.h"
#include "ui_removefiledialog.h"

RemoveFileDialog::RemoveFileDialog(const QFileInfo &fileInfo,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveFileDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Remove File"));

    ui->fileAbsolutePath ->setText(fileInfo.absoluteFilePath());



    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,[=]{
        //delete file physically and permanently
        if(ui->checkBox->isChecked()){
            QFile file(fileInfo.absoluteFilePath());
            file.remove();
            emit removePermanently(true);
            this->accept();

        }
        else{
            emit removePermanently(false);
            this->accept();
        }
    });

    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,[=]{
        this->reject();
    });


}

RemoveFileDialog::~RemoveFileDialog()
{
    delete ui;
}
