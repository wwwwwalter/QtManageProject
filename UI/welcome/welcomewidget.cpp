#include "welcomewidget.h"
#include "ui_welcomewidget.h"

#include <QFile>
#include <QLabel>
#include <QVBoxLayout>

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    QVBoxLayout *vboxlayout = new QVBoxLayout;
    setLayout(vboxlayout);

    QLabel *picLabel = new QLabel;
    QLabel *shortcutLabel = new QLabel;
    vboxlayout->addWidget(picLabel);
    vboxlayout->addWidget(shortcutLabel);

    picLabel->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    picLabel->setPixmap(QPixmap(":/images/grey/homepage_logo.png"));

    shortcutLabel->setAlignment(Qt::AlignHCenter);
    shortcutLabel->setTextFormat(Qt::MarkdownText);
    QFont font = this->font();
    //font.setPixelSize(15);
    font.setPointSize(15);
    shortcutLabel->setFont(font);
    QFile file(":/markdowm/homepage.md");
    if(file.open(QFile::ReadOnly)){
        shortcutLabel->setText(QString::fromLocal8Bit(file.readAll()));
        file.close();
    }
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}
