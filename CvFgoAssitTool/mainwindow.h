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
class FgoResultDisplayer;
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
    void initToolBar();
    void initStatusBar();
    void initSetting();

private slots:
    void slot_AddSource();
    void slot_AddTemplate();
    void slot_TemplateMat();
    void Slot_ButtonTest(); //test use port
    void Slot_UpdateStatusBar(QString strInfo);
    void slot_MessageBox(QString strinfo);

signals:
    void Signal_ChangeStatus(QString);
private:
    Ui::MainWindow *ui;

    QLabel *m_pStatusLabel;
    FgoDisplayerWidget *m_pSourceDisplayer;
    FgoDisplayerWidget *m_pTemplateDisplayer;
    FgoResultDisplayer *m_pResultDisplayer;
};

#endif // MAINWINDOW_H
