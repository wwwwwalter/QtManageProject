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


    //find already opened file,then setCurrent.
    for(int i = 0;i<count();++i){
        if(widget(i)->whatsThis()==fileInfo.absoluteFilePath()){
            setCurrentIndex(i);
            return;
        }
    }


    //open file
    QString fileSuffix = fileInfo.suffix();

    if(fileSuffix=="space"){
        SpaceFile *spaceFile = new SpaceFile;
        spaceFile->setWhatsThis(fileInfo.absoluteFilePath());
        addTab(spaceFile,QIcon(),fileInfo.fileName());
        setCurrentWidget(spaceFile);
        setTabToolTip(currentIndex(),fileInfo.absoluteFilePath());
    }
    else if(fileSuffix=="playlist"){
        PlayListFile *playListFile = new PlayListFile;
        playListFile->setWhatsThis(fileInfo.absoluteFilePath());
        addTab(playListFile,QIcon(),fileInfo.fileName());
        setCurrentWidget(playListFile);
        setTabToolTip(currentIndex(),fileInfo.absoluteFilePath());
    }
    else if(fileSuffix=="xplayer"||fileSuffix=="json"||fileSuffix=="txt"){
        TextFile *textFile = new TextFile(fileInfo);
        textFile->setWhatsThis(fileInfo.absoluteFilePath());
        addTab(textFile,QIcon(),fileInfo.fileName());
        setCurrentWidget(textFile);
        setTabToolTip(currentIndex(),fileInfo.absoluteFilePath());

    }
    else{
        TextFile *textFile = new TextFile(fileInfo);
        textFile->setWhatsThis(fileInfo.absoluteFilePath());
        addTab(textFile,QIcon(),fileInfo.fileName());
        setCurrentWidget(textFile);
        setTabToolTip(currentIndex(),fileInfo.absoluteFilePath());
    }









    if(count()==1){
        emit hasTab();
    }
}



void SpaceTabWidget::tabRemoved(int index)
{
    qDebug()<<index<<"be removed";
}
