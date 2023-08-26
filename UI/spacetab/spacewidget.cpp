#include "grider.h"
#include "spacewidget.h"
#include "spacewidgetgriddesigndialog.h"

#include <QContextMenuEvent>
#include <QMenu>
#include <QPalette>
#include <QSplitter>
#include <QVBoxLayout>

SpaceWidget::SpaceWidget(QWidget *parent)
    : QWidget{parent}
{
    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window,QColor(rand() % 256, rand() % 256, rand() % 256));
    setPalette(palette);
    setObjectName(tr("empty-widget"));



    openFileAction = new QAction(tr("Open File"),this);
    insertGridLayoutAction = new QAction(tr("Insert GridLayout"),this);
    insertWidgetOnTheTopAction = new QAction(tr("Insert Widget On The Top"),this);
    insertWidgetOnTheLeftAction = new QAction(tr("Insert Widget On The Left"),this);
    insertWidgetOnTheRightAction = new QAction(tr("Insert Widget On The Right"),this);
    insertWidgetOnTheBottomAction = new QAction(tr("Insert Widget On The Bottom"),this);
    deleteThisWidgetAction = new QAction(tr("Delete This widget"),this);

    connect(openFileAction,&QAction::triggered,this,&SpaceWidget::slotOpenFile);
    connect(insertGridLayoutAction,&QAction::triggered,this,&SpaceWidget::slotInsertGridLayout);
    connect(insertWidgetOnTheTopAction,&QAction::triggered,this,&SpaceWidget::slotInsertWidgetOnTheTop);
    connect(insertWidgetOnTheLeftAction,&QAction::triggered,this,&SpaceWidget::slotInsertWidgetOnTheLeft);
    connect(insertWidgetOnTheRightAction,&QAction::triggered,this,&SpaceWidget::slotInsertWidgetOnTheRight);
    connect(insertWidgetOnTheBottomAction,&QAction::triggered,this,&SpaceWidget::slotInsertWidgetOnTheBottom);
    connect(deleteThisWidgetAction,&QAction::triggered,this,&SpaceWidget::slotDeleteThisWidgetAction);
}

void SpaceWidget::slotOpenFile()
{

}

void SpaceWidget::slotInsertGridLayout()
{
    Grider *parentGrider = static_cast<Grider *>(this->parentWidget());
    int index = parentGrider->indexOf(this);
    qDebug()<<index;

    SpaceWidgetGridDesignDialog *spaceWidgetGridDesignDialog = new SpaceWidgetGridDesignDialog(this);
    connect(spaceWidgetGridDesignDialog,&SpaceWidgetGridDesignDialog::designComplete,this,[=](int rols,int cols){
        Grider *grider = new Grider;
        parentGrider->getGridLayout()->replaceWidget(this,grider);
        grider->addWidget(this,rols,cols);



    });


    spaceWidgetGridDesignDialog->exec();
    spaceWidgetGridDesignDialog->deleteLater();
}

void SpaceWidget::slotInsertWidgetOnTheLeft()
{
    QSplitter *parentSplitter = static_cast<QSplitter *>(this->parentWidget());
    int index = parentSplitter->indexOf(this);

    if(parentSplitter->orientation()==Qt::Horizontal){
        parentSplitter->insertWidget(index,new SpaceWidget);
    }
    else{
        QSplitter *splitter = new QSplitter(Qt::Horizontal);
        splitter->setContentsMargins(0,0,0,0);
        splitter->setHandleWidth(1);
        parentSplitter->replaceWidget(index,splitter);



        SpaceWidget *leftWidget = new SpaceWidget;
        splitter->insertWidget(0, leftWidget);
        splitter->insertWidget(1,this);
    }


}

void SpaceWidget::slotInsertWidgetOnTheRight()
{

    QSplitter *parentSplitter = static_cast<QSplitter *>(this->parentWidget());
    int index = parentSplitter->indexOf(this);

    if(parentSplitter->orientation()==Qt::Horizontal){
        parentSplitter->insertWidget(index+1,new SpaceWidget);
    }
    else{
        QSplitter *splitter = new QSplitter(Qt::Horizontal);
        splitter->setContentsMargins(0,0,0,0);
        splitter->setHandleWidth(1);
        parentSplitter->replaceWidget(index,splitter);





        SpaceWidget *rightWidget = new SpaceWidget;
        splitter->insertWidget(0, this);
        splitter->insertWidget(1,rightWidget);
    }

}

void SpaceWidget::slotInsertWidgetOnTheTop()
{
    QSplitter *parentSplitter = static_cast<QSplitter *>(this->parentWidget());
    int index = parentSplitter->indexOf(this);

    if(parentSplitter->orientation()==Qt::Vertical){
        qDebug()<<"old";
        parentSplitter->insertWidget(index,new SpaceWidget);
    }
    else{
        qDebug()<<"new";
        QSplitter *splitter = new QSplitter(Qt::Vertical);
        splitter->setContentsMargins(0,0,0,0);
        splitter->setHandleWidth(1);
        parentSplitter->replaceWidget(index,splitter);



        SpaceWidget *topWidget = new SpaceWidget;
        splitter->insertWidget(0, topWidget);
        splitter->insertWidget(1,this);
    }




}

void SpaceWidget::slotInsertWidgetOnTheBottom()
{
    QSplitter *parentSplitter = static_cast<QSplitter *>(this->parentWidget());
    int index = parentSplitter->indexOf(this);

    if(parentSplitter->orientation()==Qt::Vertical){
        parentSplitter->insertWidget(index+1,new SpaceWidget);
    }
    else{
        QSplitter *splitter = new QSplitter(Qt::Vertical);
        splitter->setContentsMargins(0,0,0,0);
        splitter->setHandleWidth(1);
        parentSplitter->replaceWidget(index,splitter);



        SpaceWidget *bottomWidget = new SpaceWidget;
        splitter->insertWidget(0, this);
        splitter->insertWidget(1,bottomWidget);
    }



}

void SpaceWidget::slotDeleteThisWidgetAction() {
    if (this->parentWidget()->inherits("QSplitter")) {

        QSplitter *parentSplitter =
            static_cast<QSplitter *>(this->parentWidget());
        int thisIndex = parentSplitter->indexOf(this);
        this->deleteLater();

        // if this widget is the second to last,take the last one to
        // grandParentSplitter
        if (parentSplitter->count() == 2) {
          // if parentSplitter is the lowest level splitter
          if (!parentSplitter->parentWidget()->inherits("QSplitter")) {
            // do nothing
            qDebug() << "do nothing";
          } else {
            QSplitter *grandParentSplitter =
                static_cast<QSplitter *>(parentSplitter->parentWidget());
            QWidget *lastOne = parentSplitter->widget(!thisIndex);
            int parentIndex = grandParentSplitter->indexOf(parentSplitter);
            grandParentSplitter->replaceWidget(parentIndex, lastOne);
            parentSplitter->deleteLater();
            qDebug() << "take the last one to grandParentSplitter";
          }

        }

        // if this widget is the last one,delete parent splitter
        else if (parentSplitter->count() == 1) {
          qDebug() << "delete parent";
          parentSplitter->deleteLater();
        }
    }
    else if(this->parentWidget()->inherits("Grider")){
        qDebug()<<"Grider";
        Grider *parentGrider = static_cast<Grider *>(this->parentWidget());
        int index = parentGrider->indexOf(this);

        int rol;
        int col;
        int rolSpan;
        int colSpan;
        parentGrider->getGridLayout()->getItemPosition(index,&rol,&col,&rolSpan,&colSpan);
        qDebug()<<rol<<col<<rolSpan<<colSpan;

        QLayoutItem* localTakeAt = parentGrider->getGridLayout()->takeAt(index);
        localTakeAt->widget()->deleteLater();
        //delete localTakeAt;
        qDebug()<<index;




    }
}

void SpaceWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(openFileAction);
    menu.addAction(insertGridLayoutAction);
    menu.addAction(insertWidgetOnTheTopAction);
    menu.addAction(insertWidgetOnTheLeftAction);
    menu.addAction(insertWidgetOnTheRightAction);
    menu.addAction(insertWidgetOnTheBottomAction);
    menu.addAction(deleteThisWidgetAction);
    menu.exec(QCursor::pos());
    event->accept();
}
