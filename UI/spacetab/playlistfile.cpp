#include "playlistfile.h"
#include "ui_playlistfile.h"

PlayListFile::PlayListFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayListFile)
{
    ui->setupUi(this);
}

PlayListFile::~PlayListFile()
{
    qDebug()<<"~PlayListFile";
    delete ui;
}
