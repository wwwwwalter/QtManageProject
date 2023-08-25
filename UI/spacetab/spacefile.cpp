#include "emptywidget.h"
#include "spacefile.h"
#include "ui_spacefile.h"

#include <QContextMenuEvent>
#include <QMenu>
#include <QObject>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QVideoWidget>



SpaceFile::SpaceFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpaceFile)
{
    ui->setupUi(this);

    vboxLayout = new QVBoxLayout;
    vboxLayout->setContentsMargins(0,0,0,0);
    setLayout(vboxLayout);

    insertGridLayoutAction = new QAction(tr("Insert GridLayout"),this);
    insertHorizontalSplitterAction = new QAction(tr("Insert Horizontal Splitter"),this);
    insertVerticalSplitterAction = new QAction(tr("Insert Vertical Splitter"),this);

    connect(insertGridLayoutAction,&QAction::triggered,this,&SpaceFile::slotInsertGridLayout);
    connect(insertHorizontalSplitterAction,&QAction::triggered,this,&SpaceFile::slotInsertHorizontalSplitter);
    connect(insertVerticalSplitterAction,&QAction::triggered,this,&SpaceFile::slotInsertVerticalSplitter);








}

SpaceFile::~SpaceFile()
{
    qDebug()<<"~SpaceFile";
    delete ui;
}

void SpaceFile::slotInsertGridLayout()
{

}

void SpaceFile::slotInsertHorizontalSplitter()
{
    QSplitter *splitter =new QSplitter(Qt::Horizontal);
    splitter->setHandleWidth(1);
    splitter->setContentsMargins(0,0,0,0);
    vboxLayout->addWidget(splitter);
    EmptyWidget *leftSpace = new EmptyWidget;
    EmptyWidget *rightSpace = new EmptyWidget;
    splitter->addWidget(leftSpace);
    splitter->addWidget(rightSpace);


}

void SpaceFile::slotInsertVerticalSplitter()
{
    QSplitter *splitter =new QSplitter(Qt::Vertical);
    splitter->setHandleWidth(1);
    splitter->setContentsMargins(0,0,0,0);
    vboxLayout->addWidget(splitter);
    EmptyWidget *topSpace = new EmptyWidget;
    EmptyWidget *bottomSpace = new EmptyWidget;
    splitter->addWidget(topSpace);
    splitter->addWidget(bottomSpace);
}


void SpaceFile::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(insertGridLayoutAction);
    menu.addAction(insertHorizontalSplitterAction);
    menu.addAction(insertVerticalSplitterAction);
    menu.exec(QCursor::pos());
    event->accept();
}
