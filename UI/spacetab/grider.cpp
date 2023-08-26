#include "grider.h"
#include "spacewidget.h"
#include "spacewidgetgriddesigndialog.h"

#include <QCloseEvent>
#include <QContextMenuEvent>
#include <QMenu>

Grider::Grider(QWidget *parent)
    : QWidget{parent}
{
    gridLayout = new QGridLayout;
    setLayout(gridLayout);
    gridLayout->setSpacing(10);
    gridLayout->setContentsMargins(0,0,0,0);

    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window,QColor(0,0,255));
    setPalette(palette);


    insertGridLayoutAction = new QAction(tr("Insert GridLayout"),this);
    connect(insertGridLayoutAction,&QAction::triggered,this,&Grider::slotInsertGridLayout);

}

void Grider::slotInsertGridLayout()
{


    for(int i = 0;i<gridLayout->rowCount();++i){
        for(int j = 0;j<gridLayout->columnCount();++j){
            QRect rect = gridLayout->cellRect(i,j);
            if(rect.contains(point)){
                SpaceWidgetGridDesignDialog *spaceWidgetGridDesignDialog = new SpaceWidgetGridDesignDialog(this);
                connect(spaceWidgetGridDesignDialog,&SpaceWidgetGridDesignDialog::designComplete,this,[=](int rols,int cols){
                    Grider *grider = new Grider;
                    grider->addWidget(rols,cols);
                    gridLayout->addWidget(grider,i,j);

                });

                spaceWidgetGridDesignDialog->exec();
                spaceWidgetGridDesignDialog->deleteLater();
                break;
            }
        }
    }







}

void Grider::addWidget(int rols, int cols)
{
    for (int i = 0; i < rols; ++i) {
        for (int j = 0; j < cols; ++j) {
            SpaceWidget *spaceWidget = new SpaceWidget;
            gridLayout->addWidget(spaceWidget,i,j);
        }
    }
}

void Grider::addWidget(QWidget *widget, int rols, int cols)
{
    for (int i = 0; i < rols; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(i==0&&j==0){
                gridLayout->addWidget(widget,i,j);
            }
            else{
                SpaceWidget *spaceWidget = new SpaceWidget;
                gridLayout->addWidget(spaceWidget,i,j);
            }
        }
    }
}

QGridLayout *Grider::getGridLayout()
{
    return static_cast<QGridLayout *>(this->layout());
}

int Grider::indexOf(QWidget *widget)
{
    return gridLayout->indexOf(widget);
}


void Grider::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(insertGridLayoutAction);
    menu.exec(QCursor::pos());
}


void Grider::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton){
        point = event->pos();
    }
}


void Grider::mouseReleaseEvent(QMouseEvent *event)
{
}

void Grider::mouseMoveEvent(QMouseEvent *event)
{
}
