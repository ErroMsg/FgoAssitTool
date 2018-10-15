#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cvinclude.h"

class QGraphicsView;
class QGraphicsScene;
class QLabel;
class QResizeEvent;
class QGraphicsItem;
class FgoDisplayerWidget;
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

private slots:
    void Slot_ButtonTest();
    void Slot_ButtonTest2();
    void Slot_ButtonTest3();
    void Slot_UpdateStatusBar(QString strInfo);
signals:
    void Signal_ChangeStatus(QString);
private:
    Ui::MainWindow *ui;

    QLabel *m_pStatusLabel;
    QGraphicsScene *m_pScene;
    QGraphicsItem *m_pCheckImg;

    FgoDisplayerWidget *m_pMainDisplayer;
};

#endif // MAINWINDOW_H
