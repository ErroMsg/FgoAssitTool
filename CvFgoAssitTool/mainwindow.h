#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cvinclude.h"

class QGraphicsView;
class QGraphicsScene;
class QLabel;
class QResizeEvent;
class FgoGraphicsView;
class QGraphicsItem;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initUi();
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void Slot_ButtonTest();
    void Slot_ButtonTest2();
    void Slot_UpdateStatusBar(QString strInfo);
signals:
    void Signal_ChangeStatus(QString);
private:
    Ui::MainWindow *ui;

    QLabel *m_pStatusLabel;
    FgoGraphicsView *m_pImgView;
    QGraphicsScene *m_pScene;
    QGraphicsItem *m_pCheckImg;
};

#endif // MAINWINDOW_H
