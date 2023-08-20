#ifndef SPACETABWIDGET_H
#define SPACETABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QTabBar>
#include "spacefile.h"
#include "playlistfile.h"
#include "textfile.h"
#include <QFileInfo>
#include <QFileInfoList>


class SpaceTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit SpaceTabWidget(QWidget *parent = nullptr);

    QFileInfoList fileInfoList;



public slots:
    void openSpaceFile(QFileInfo fileInfo);

signals:
    void hasTab();
    void noTab();
    void currentTabChanged(QFileInfo fileInfo);



    // QTabWidget interface
protected:
    virtual void tabRemoved(int index);
};

#endif // SPACETABWIDGET_H
