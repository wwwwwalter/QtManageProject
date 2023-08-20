#include "textfile.h"
#include "ui_textfile.h"

TextFile::TextFile(QFileInfo fileInfo, QWidget *parent) :
    AbstractFile(parent),ui(new Ui::TextFile),privateFileInfo(fileInfo)

{

    ui->setupUi(this);
    //font
    QFont font = ui->textEdit->font();
    font.setPointSize(11);
    ui->textEdit->setFont(font);


    openFile(privateFileInfo);




}

TextFile::~TextFile()
{
    qDebug()<<"~TextFile";
    delete ui;
}



void TextFile::openFile(QFileInfo fileInfo)
{
    QFile file(fileInfo.absoluteFilePath());
    if(file.open(QFile::ReadOnly)){
        QByteArray data = file.readAll();
        QString fileContent = QString::fromLocal8Bit(data);
        ui->textEdit->setText(fileContent);

        file.close();
    }
}

void TextFile::closeFile(QFileInfo fileInfo)
{
}

void TextFile::saveFile(QFileInfo fileInfo)
{
    QFile file(privateFileInfo.absoluteFilePath());
    if(file.open(QFile::WriteOnly)){
        QString fileContent = ui->textEdit->toPlainText();
        QByteArray data = fileContent.toLocal8Bit();
        file.write(data);

        file.close();
    }
}

void TextFile::saveFileAs(QFileInfo sourceFileInfo, QFileInfo destFileInfo)
{
    QFile file(destFileInfo.absoluteFilePath());
    if(file.open(QFile::WriteOnly)){
        QString fileContent = ui->textEdit->toPlainText();
        QByteArray data = fileContent.toLocal8Bit();
        file.write(data);

        file.close();
    }
}
