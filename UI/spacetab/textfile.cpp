#include "textfile.h"
#include "ui_textfile.h"

TextFile::TextFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextFile)
{
    ui->setupUi(this);
}

TextFile::~TextFile()
{
    delete ui;
}
