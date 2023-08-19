#include "videospace.h"
#include "ui_videospace.h"

VideoSpace::VideoSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoSpace)
{
    ui->setupUi(this);
}

VideoSpace::~VideoSpace()
{
    delete ui;
}
