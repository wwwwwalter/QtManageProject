#ifndef SPACEFILE_H
#define SPACEFILE_H

#include <QWidget>
#include <QAction>
#include <QVBoxLayout>

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
};

#endif // SPACEFILE_H
