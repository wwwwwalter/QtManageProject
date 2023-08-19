#include "spacetabwidget.h"

SpaceTabWidget::SpaceTabWidget(QWidget *parent)
    : QTabWidget{parent}
{
    setTabPosition(QTabWidget::North);
    setTabShape(QTabWidget::Rounded);
    setTabsClosable(true);
    setMovable(true);
    setTabBarAutoHide(false);
    setUsesScrollButtons(true);
    setStyleSheet("QTabBar::tab{width:200}");
    tabBar()->setElideMode(Qt::ElideMiddle);





    connect(this,&SpaceTabWidget::tabCloseRequested,this,[=](int index){
        QWidget *willDeleteTab = widget(index);
        removeTab(index);
        willDeleteTab->deleteLater();




        if(count()==0){
            emit noTab();
        }

    });


    connect(this,&SpaceTabWidget::currentChanged,this,[=](int index){
        QFileInfo fileInfo(widget(index)->whatsThis());
        emit currentTabChanged(fileInfo);

    });

}

void SpaceTabWidget::openSpaceFile(QFileInfo fileInfo)
{



    for(int i = 0;i<count();++i){
        if(widget(i)->whatsThis()==fileInfo.absoluteFilePath()){
            setCurrentIndex(i);
            return;
        }
    }





    EmptySpace *emptySpace = new EmptySpace;
    emptySpace->setWhatsThis(fileInfo.absoluteFilePath());
    addTab(emptySpace,QIcon(":/images/green/insert-table.svg"),fileInfo.fileName());
    setCurrentWidget(emptySpace);
    setTabToolTip(currentIndex(),fileInfo.absoluteFilePath());







    if(count()==1){
        emit hasTab();
    }
}

