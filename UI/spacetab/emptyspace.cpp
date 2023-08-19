#include "emptyspace.h"
#include "ui_emptyspace.h"

EmptySpace::EmptySpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmptySpace)
{
    ui->setupUi(this);
}

EmptySpace::~EmptySpace()
{
    qDebug()<<"~EmptySpace";
    delete ui;
}
