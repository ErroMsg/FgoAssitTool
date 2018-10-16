#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../CvFgoUiSys/fgographicsview.h"
#include "../CvFgoUiSys/fgoresultdisplayer.h"
#include "cvmatchhelper.h"
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
#include <QMessageBox>
#include <QSplitter>
#include <QAction>
#include <QList>
#include <QFileInfo>
#include <QDebug>

#include "../CvFgoUiSys/fgodisplayerwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pStatusLabel(nullptr),
    m_pSourceDisplayer(nullptr),
    m_pTemplateDisplayer(nullptr),
    m_pResultDisplayer(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Fgo Assist");

    initUi();
    initToolBar();
    initStatusBar();

    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    //ImageViewLayout
    m_pSourceDisplayer = new FgoDisplayerWidget("Source");
    m_pTemplateDisplayer = new FgoDisplayerWidget("Template");
    m_pResultDisplayer = new FgoResultDisplayer("Result");

    QSplitter *vsplitter = new QSplitter(Qt::Orientation::Vertical);
    vsplitter->addWidget(m_pSourceDisplayer);
    vsplitter->addWidget(m_pTemplateDisplayer);

    QSplitter *mainsplitter = new QSplitter(Qt::Orientation::Horizontal);
    mainsplitter->addWidget(vsplitter);
    mainsplitter->addWidget(m_pResultDisplayer);
    mainsplitter->setStretchFactor(0,1);
    mainsplitter->setStretchFactor(1,2);

    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->setMargin(5);
    pMainLayout->setSpacing(0);
    pMainLayout->addWidget(mainsplitter);
    centralWidget()->setLayout(pMainLayout);

    connect(m_pResultDisplayer->getGraphicsView(),SIGNAL(Signal_UpdateCoor(QString)),
            this,SIGNAL(Signal_ChangeStatus(QString)));
    connect(m_pSourceDisplayer->getGraphicsView(),SIGNAL(Signal_UpdateCoor(QString)),
            this,SIGNAL(Signal_ChangeStatus(QString)));
    connect(m_pTemplateDisplayer->getGraphicsView(),SIGNAL(Signal_UpdateCoor(QString)),
            this,SIGNAL(Signal_ChangeStatus(QString)));

}

void MainWindow::initToolBar()
{
    QAction *pActAddSource = new QAction("Add Source");
    QAction *pActAddTemplate = new QAction("Add Template");
    QAction *pActMat = new QAction("Mat");
    ui->mainToolBar->addAction(pActAddSource);
    ui->mainToolBar->addAction(pActAddTemplate);
    ui->mainToolBar->addAction(pActMat);
    connect(pActAddSource,SIGNAL(triggered(bool)),this,SLOT(slot_AddSource()));
    connect(pActAddTemplate,SIGNAL(triggered(bool)),this,SLOT(slot_AddTemplate()));
    connect(pActMat,SIGNAL(triggered(bool)),this,SLOT(slot_TemplateMat()));
}

void MainWindow::initStatusBar()
{
    //Status Bar
    m_pStatusLabel = new QLabel(this);
    m_pStatusLabel->setText("ImagePath is Empty");
    this->statusBar()->addPermanentWidget(m_pStatusLabel);
    connect(m_pSourceDisplayer->getGraphicsView(),SIGNAL(Signal_UpdateCoor(QString)),this,SLOT(Slot_UpdateStatusBar(QString)));
    connect(m_pTemplateDisplayer->getGraphicsView(),SIGNAL(Signal_UpdateCoor(QString)),this,SLOT(Slot_UpdateStatusBar(QString)));
    connect(m_pResultDisplayer->getGraphicsView(),SIGNAL(Signal_UpdateCoor(QString)),this,SLOT(Slot_UpdateStatusBar(QString)));
}

void MainWindow::slot_AddSource()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    if (fileName.isEmpty())
    {
        return;
    }

    m_pSourceDisplayer->postImage(fileName);
    m_pResultDisplayer->postImage(fileName);
    emit Signal_ChangeStatus(QString("Source ImagePath = " + fileName));
}

void MainWindow::slot_AddTemplate()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    if (fileName.isEmpty())
    {
        return;
    }

    m_pTemplateDisplayer->postImage(fileName);
    emit Signal_ChangeStatus(QString("Template ImagePath = " + fileName));
}

void MainWindow::slot_TemplateMat()
{
    QString imagepath = m_pSourceDisplayer->getPostImagePath();
    QString templateFile = m_pTemplateDisplayer->getPostImagePath();

    QFileInfo fi(imagepath);
    QFileInfo ft(templateFile);
    if(!fi.isFile() || !ft.isFile())
    {
        slot_MessageBox("Add source image and template image!");
        return;
    }

    QImage source(imagepath);
    QImage temp(templateFile);
    if(temp.width() >= source.width() || temp.height()>= source.height())
    {
        slot_MessageBox("template image size can not larger than source file");
        return;
    }

    CvMatchHelper helper;
    cvResult result = helper.MatchTemplate(imagepath,templateFile);
    //Post result:
    m_pResultDisplayer->postMatResult(QPoint(result.resultRect.x,result.resultRect.y),
                                      result.resultRect.width,result.resultRect.height);
}


void MainWindow::Slot_ButtonTest()
{

}


void MainWindow::Slot_UpdateStatusBar(QString strInfo)
{
    m_pStatusLabel->setText(strInfo);
}

void MainWindow::slot_MessageBox(QString strinfo)
{
    QMessageBox msgBox;
    msgBox.setText(strinfo);
    msgBox.exec();
    return;
}
