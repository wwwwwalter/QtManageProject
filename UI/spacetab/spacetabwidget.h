#ifndef SPACETABWIDGET_H
#define SPACETABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QTabBar>
#include "emptyspace.h"
#include "videospace.h"
#include "audiospace.h"
#include "playlist.h"
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


};

#endif // SPACETABWIDGET_H
