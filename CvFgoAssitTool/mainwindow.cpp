#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fgographicsview.h"
#include <QLayout>
#include <QSpacerItem>
#include <QToolButton>
#include <QLabel>
#include <QFileDialog>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QResizeEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pImgView(nullptr),
    m_pScene(nullptr),
    m_pStatusLabel(nullptr)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    setWindowTitle("Fgo Assist");
    initUi();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    //ButtonLayout
    QGridLayout *pButtonLayout = new QGridLayout;
    QToolButton *btTest = new QToolButton(this);
    btTest->setText("Add Pic");

    QToolButton *bt1 = new QToolButton(this);
    bt1->setText("Add Pic moveable");

    QToolButton *bt2 = new QToolButton(this);
    bt2->setText("Test func2");

    QToolButton *bt3 = new QToolButton(this);
    bt3->setText("Test func3");

    QSpacerItem *pSpacerTop = new QSpacerItem(0,5,QSizePolicy::Fixed,QSizePolicy::Fixed);
    QSpacerItem *pSpacerBottom = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding);

    pButtonLayout->addItem(pSpacerTop,0,0);
    pButtonLayout->addWidget(btTest,1,0);
    pButtonLayout->addWidget(bt1,2,0);
    pButtonLayout->addWidget(bt2,3,0);
    pButtonLayout->addWidget(bt3,4,0);
    pButtonLayout->addItem(pSpacerBottom,5,0);

    //ImageViewLayout
    QGridLayout *pImageLayout = new QGridLayout;
    m_pScene = new QGraphicsScene(this);
    m_pImgView = new FgoGraphicsView(this);
    m_pImgView->setScene(m_pScene);

    pImageLayout->addWidget(m_pImgView);

    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->addLayout(pImageLayout);
    pMainLayout->addLayout(pButtonLayout);
    centralWidget()->setLayout(pMainLayout);

    //Status Bar
    m_pStatusLabel = new QLabel(this);
    m_pStatusLabel->setText("ImagePath is Empty");
    this->statusBar()->addPermanentWidget(m_pStatusLabel);

    connect(btTest,SIGNAL(clicked(bool)),this,SLOT(Slot_ButtonTest()));
    connect(bt1,SIGNAL(clicked(bool)),this,SLOT(Slot_ButtonTest2()));
    connect(this,SIGNAL(Signal_ChangeStatus(QString)),this,SLOT(Slot_UpdateStatusBar(QString)));
    connect(m_pImgView,SIGNAL(Signal_UpdateCoor(QString)),this,SIGNAL(Signal_ChangeStatus(QString)));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"GraphicView:"<<m_pImgView->size();
    //m_pImgView->setSceneRect(-m_pImgView->width(),-m_pImgView->height(),m_pImgView->width(),m_pImgView->height());
}

void MainWindow::Slot_ButtonTest()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    if (fileName.isEmpty())
    {
        return;
    }

    qDebug()<<"Slot_ButtonTest called, fileName = "<<fileName;

    QGraphicsItem *pItem = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(fileName)));
    pItem->setPos(0,0);
    m_pScene->addItem(pItem);
    emit Signal_ChangeStatus(QString("ImagePath = " + fileName));
}

void MainWindow::Slot_ButtonTest2()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    if (fileName.isEmpty())
    {
        return;
    }

    qDebug()<<"Slot_ButtonTest called, fileName = "<<fileName;

    QGraphicsItem *pItem = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(fileName)));
    pItem->setPos(0,0);
    pItem->setFlags(QGraphicsItem::ItemIsMovable);
    pItem->setOpacity(0.5);
    m_pScene->addItem(pItem);
    emit Signal_ChangeStatus(QString("ImagePath = " + fileName));
}

void MainWindow::Slot_UpdateStatusBar(QString strInfo)
{
    m_pStatusLabel->setText(strInfo);
}
