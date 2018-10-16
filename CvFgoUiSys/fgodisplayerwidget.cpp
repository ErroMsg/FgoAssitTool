#include "fgodisplayerwidget.h"
#include <QGraphicsView>
#include <QLabel>
#include <QToolButton>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "fgographicsview.h"
#include <QDebug>

TitleWidget::TitleWidget(QString strtitle, QWidget *parent)
    : QFrame(parent),
      _pTitleLabel(nullptr),
      _pToolButton(nullptr)
{
    setObjectName("TitleWidget");
    setMaximumHeight(40);
    _pTitleLabel = new QLabel(strtitle,this);
    _pTitleLabel->setObjectName("TitleLabel");
    _pToolButton = new QToolButton(this);

    QSpacerItem *pSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QHBoxLayout *playout = new QHBoxLayout;
    playout->setMargin(4);
    playout->setSpacing(0);
    playout->addWidget(_pTitleLabel);
    playout->addSpacerItem(pSpacer);
    playout->addWidget(_pToolButton);

    this->setLayout(playout);
}

FgoDisplayerWidget::FgoDisplayerWidget(QString strTiltle,QWidget *parent)
    : QFrame(parent),
      m_strTitle(strTiltle),
      m_pGraphicsView(nullptr),
      m_pScene(nullptr),
      m_pTitleBar(nullptr),
      m_pPostedImage(nullptr)
{
    this->setObjectName("FgoDisplayerWidget");
    m_pGraphicsView = new FgoGraphicsView(this);
    m_pScene = new QGraphicsScene(this);
    m_pGraphicsView->setScene(m_pScene);
    initLayout();
}


void FgoDisplayerWidget::initLayout()
{
    m_pTitleBar = new TitleWidget(m_strTitle,this);

    QVBoxLayout *playout = new QVBoxLayout;
    playout->setMargin(0);
    playout->setSpacing(0);
    playout->addWidget(m_pTitleBar);
    playout->addWidget(m_pGraphicsView);
    this->setLayout(playout);
}

FgoGraphicsView *FgoDisplayerWidget::getGraphicsView()
{
    return m_pGraphicsView;
}

QGraphicsScene *FgoDisplayerWidget::getGraphicsScene()
{
    return m_pScene;
}

void FgoDisplayerWidget::clearScene()
{
    m_pScene->removeItem(m_pPostedImage);
    if(m_pPostedImage)
    {
        delete m_pPostedImage;
        m_pPostedImage = nullptr;
    }
}

QString FgoDisplayerWidget::getPostImagePath()
{
    QString strPath;
    if(m_pPostedImage)
    {
        strPath = m_pPostedImage->data(Qt::UserRole).toString();
    }
    return strPath;
}

void FgoDisplayerWidget::postImage(QString strfilepath)
{
    if(m_pPostedImage)
    {
        clearScene();
    }

    m_pPostedImage = new QGraphicsPixmapItem(QPixmap(strfilepath));
    m_pPostedImage->setData(Qt::UserRole,strfilepath);
    m_pScene->addItem(m_pPostedImage);
}


