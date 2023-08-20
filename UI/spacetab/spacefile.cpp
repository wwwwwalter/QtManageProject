#include "spacefile.h"
#include "ui_spacefile.h"

SpaceFile::SpaceFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpaceFile)
{
    ui->setupUi(this);
}

SpaceFile::~SpaceFile()
{
    qDebug()<<"~SpaceFile";
    delete ui;
}
