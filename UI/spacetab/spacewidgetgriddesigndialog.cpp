#include "spacewidgetgriddesigndialog.h"
#include "ui_spacewidgetgriddesigndialog.h"
#include <QTableView>

SpaceWidgetGridDesignDialog::SpaceWidgetGridDesignDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpaceWidgetGridDesignDialog)
{
    ui->setupUi(this);




    connect(ui->buttonBox,&QDialogButtonBox::clicked,this,[=](QAbstractButton *button){
        if(ui->buttonBox->buttonRole(button)==QDialogButtonBox::ApplyRole){
            int rols = ui->tableView->selectedRowNum;
            int cols = ui->tableView->selectedColNum;
            qDebug()<<rols<<":"<<cols;




        }
        else if(ui->buttonBox->buttonRole(button)==QDialogButtonBox::AcceptRole)
        {

            this->accept();
        }
        else if(ui->buttonBox->buttonRole(button)==QDialogButtonBox::RejectRole){

            this->reject();
        }

    });



}

SpaceWidgetGridDesignDialog::~SpaceWidgetGridDesignDialog()
{
    delete ui;
}
