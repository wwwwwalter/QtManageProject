#ifndef SPACEFILE_H
#define SPACEFILE_H

#include <QWidget>
#include <QAction>
#include <QVBoxLayout>
#include <QPainter>

namespace Ui {
class SpaceFile;
}

class SpaceFile : public QWidget
{
    Q_OBJECT

public:
    explicit SpaceFile(QWidget *parent = nullptr);
    ~SpaceFile();

private:
    Ui::SpaceFile *ui;
    QVBoxLayout *vboxLayout;




    QAction *insertGridLayoutAction;
    QAction *insertHorizontalSplitterAction;
    QAction *insertVerticalSplitterAction;

private slots:
    void slotInsertGridLayout();
    void slotInsertHorizontalSplitter();
    void slotInsertVerticalSplitter();

    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

    // QWidget interface
protected:
    QPoint topLeft;
    QPoint bottomRight;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
};

#endif // SPACEFILE_H
