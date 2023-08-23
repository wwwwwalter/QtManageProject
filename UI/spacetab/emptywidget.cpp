#include "emptywidget.h"

#include <QContextMenuEvent>
#include <QMenu>
#include <QPalette>
#include <QSplitter>
#include <QVBoxLayout>

EmptyWidget::EmptyWidget(QWidget *parent)
    : QWidget{parent}
{
    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window,QColor(rand() % 256, rand() % 256, rand() % 256));
    setPalette(palette);
    setObjectName(tr("empty-widget"));



    openFileAction = new QAction(tr("Open File"),this);
    insertWidgetOnTheTopAction = new QAction(tr("Insert Widget On The Top"),this);
    insertWidgetOnTheLeftAction = new QAction(tr("Insert Widget On The Left"),this);
    insertWidgetOnTheRightAction = new QAction(tr("Insert Widget On The Right"),this);
    insertWidgetOnTheBottomAction = new QAction(tr("Insert Widget On The Bottom"),this);

    connect(insertWidgetOnTheTopAction,&QAction::triggered,this,&EmptyWidget::slotInsertWidgetOnTheTop);
    connect(insertWidgetOnTheLeftAction,&QAction::triggered,this,&EmptyWidget::slotInsertWidgetOnTheLeft);
    connect(insertWidgetOnTheRightAction,&QAction::triggered,this,&EmptyWidget::slotInsertWidgetOnTheRight);
    connect(insertWidgetOnTheBottomAction,&QAction::triggered,this,&EmptyWidget::slotInsertWidgetOnTheBottom);
}

void EmptyWidget::slotInsertGridLayout()
{

}

void EmptyWidget::slotInsertHorizontalSplitter()
{
    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->setContentsMargins(0,0,0,0);
    setLayout(vboxLayout);
    QSplitter *splitter =new QSplitter(Qt::Horizontal);
    splitter->setHandleWidth(1);
    vboxLayout->addWidget(splitter);
    EmptyWidget *leftSpace = new EmptyWidget;
    EmptyWidget *rightSpace = new EmptyWidget;
    splitter->addWidget(leftSpace);
    splitter->addWidget(rightSpace);


}

void EmptyWidget::slotInsertVerticalSplitter()
{
    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->setContentsMargins(0,0,0,0);
    setLayout(vboxLayout);
    QSplitter *splitter =new QSplitter(Qt::Vertical);
    splitter->setHandleWidth(1);
    vboxLayout->addWidget(splitter);
    EmptyWidget *topSpace = new EmptyWidget;
    EmptyWidget *bottomSpace = new EmptyWidget;
    splitter->addWidget(topSpace);
    splitter->addWidget(bottomSpace);
}

void EmptyWidget::slotInsertWidgetOnTheLeft()
{
    QSplitter *parentSplitter = static_cast<QSplitter *>(this->parentWidget());
    int index = parentSplitter->indexOf(this);


    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->setContentsMargins(0,0,0,0);
    splitter->setHandleWidth(1);
    parentSplitter->replaceWidget(index,splitter);



    EmptyWidget *leftWidget = new EmptyWidget;
    splitter->insertWidget(0, leftWidget);
    splitter->insertWidget(1,this);
}

void EmptyWidget::slotInsertWidgetOnTheRight()
{

    QSplitter *parentSplitter = static_cast<QSplitter *>(this->parentWidget());
    int index = parentSplitter->indexOf(this);


    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->setContentsMargins(0,0,0,0);
    splitter->setHandleWidth(1);
    parentSplitter->replaceWidget(index,splitter);





    EmptyWidget *rightWidget = new EmptyWidget;
    splitter->insertWidget(0, this);
    splitter->insertWidget(1,rightWidget);










}

void EmptyWidget::slotInsertWidgetOnTheTop()
{
    QSplitter *parentSplitter = static_cast<QSplitter *>(this->parentWidget());
    int index = parentSplitter->indexOf(this);


    QSplitter *splitter = new QSplitter(Qt::Vertical);
    splitter->setContentsMargins(0,0,0,0);
    splitter->setHandleWidth(1);
    parentSplitter->replaceWidget(index,splitter);



    EmptyWidget *topWidget = new EmptyWidget;
    splitter->insertWidget(0, topWidget);
    splitter->insertWidget(1,this);

}

void EmptyWidget::slotInsertWidgetOnTheBottom()
{
    QSplitter *parentSplitter = static_cast<QSplitter *>(this->parentWidget());
    int index = parentSplitter->indexOf(this);


    QSplitter *splitter = new QSplitter(Qt::Vertical);
    splitter->setContentsMargins(0,0,0,0);
    splitter->setHandleWidth(1);
    parentSplitter->replaceWidget(index,splitter);



    EmptyWidget *bottomWidget = new EmptyWidget;
    splitter->insertWidget(0, this);
    splitter->insertWidget(1,bottomWidget);
}


void EmptyWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(openFileAction);
    menu.addAction(insertWidgetOnTheTopAction);
    menu.addAction(insertWidgetOnTheLeftAction);
    menu.addAction(insertWidgetOnTheRightAction);
    menu.addAction(insertWidgetOnTheBottomAction);
    menu.exec(QCursor::pos());
    event->accept();
}
