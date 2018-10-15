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

class TitleWidget : public QWidget
{
public:
    TitleWidget(QString strtitle,QWidget *parent)
        : QWidget(parent),
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
        playout->setContentsMargins(0,0,0,5);
        playout->setSpacing(0);
        playout->addWidget(_pTitleLabel);
        playout->addSpacerItem(pSpacer);
        playout->addWidget(_pToolButton);

        this->setLayout(playout);
    }
private:
    QLabel *_pTitleLabel;
    QToolButton *_pToolButton;
};

FgoDisplayerWidget::FgoDisplayerWidget(QString strTiltle,QWidget *parent)
    : QWidget(parent),
      m_strTitle(strTiltle),
      m_pGraphicsView(nullptr),
      m_pScene(nullptr),
      m_pTitleBar(nullptr),
      m_pPostedImage(nullptr)
{
    setObjectName("FgoDisplayerWidget");
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

void FgoDisplayerWidget::postImage(QString strfilepath)
{
    if(m_pPostedImage)
    {
        delete m_pPostedImage;
        m_pPostedImage = nullptr;
    }

    m_pPostedImage = new QGraphicsPixmapItem(QPixmap(strfilepath));
    m_pPostedImage->setData(Qt::UserRole,strfilepath);
    m_pScene->addItem(m_pPostedImage);
}


