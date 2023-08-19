#include "audiospace.h"
#include "ui_audiospace.h"

AudioSpace::AudioSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioSpace)
{
    ui->setupUi(this);
}

AudioSpace::~AudioSpace()
{
    delete ui;
}
