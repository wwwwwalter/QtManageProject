#include "spacewidget.h"
#include "spacefile.h"
#include "ui_spacefile.h"
#include "spacewidgetgriddesigndialog.h"

#include <QContextMenuEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QObject>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QVideoWidget>
#include "grider.h"



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
    SpaceWidgetGridDesignDialog *spaceWidgetGridDesignDialog = new SpaceWidgetGridDesignDialog(this);
    connect(spaceWidgetGridDesignDialog,&SpaceWidgetGridDesignDialog::designComplete,this,[=](int rols,int cols){
        Grider *grider = new Grider;
        vboxLayout->addWidget(grider);
        grider->addWidget(rols,cols);


    });


    spaceWidgetGridDesignDialog->exec();
    spaceWidgetGridDesignDialog->deleteLater();
}

void SpaceFile::slotInsertHorizontalSplitter()
{
    QSplitter *splitter =new QSplitter(Qt::Horizontal);
    splitter->setHandleWidth(1);
    splitter->setContentsMargins(0,0,0,0);
    vboxLayout->addWidget(splitter);
    SpaceWidget *leftSpace = new SpaceWidget;
    SpaceWidget *rightSpace = new SpaceWidget;
    splitter->addWidget(leftSpace);
    splitter->addWidget(rightSpace);


}

void SpaceFile::slotInsertVerticalSplitter()
{
    QSplitter *splitter =new QSplitter(Qt::Vertical);
    splitter->setHandleWidth(1);
    splitter->setContentsMargins(0,0,0,0);
    vboxLayout->addWidget(splitter);
    SpaceWidget *topSpace = new SpaceWidget;
    SpaceWidget *bottomSpace = new SpaceWidget;
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


void SpaceFile::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        topLeft = event->pos();
    }


}

void SpaceFile::mouseMoveEvent(QMouseEvent *event)
{
    bottomRight = event->pos();


    update();

}

void SpaceFile::mouseReleaseEvent(QMouseEvent *event)
{



    if(event->button()==Qt::LeftButton){
        bottomRight = event->pos();
        SpaceWidget *spaceWidget = new SpaceWidget(this);
        spaceWidget->setGeometry(QRect(topLeft,bottomRight));
        spaceWidget->show();
    }



}




void SpaceFile::paintEvent(QPaintEvent *event)
{

    if(topLeft!=bottomRight){
        QPainter painter(this);
        painter.setPen(Qt::red);
        QRect rect(topLeft,bottomRight);
        painter.drawRect(rect);
    }


    int static  count = 0;
    qDebug()<<"paintEvent"<<count++;
    event->accept();


}
