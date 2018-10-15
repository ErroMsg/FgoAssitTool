#include "fgodisplayerwidget.h"
#include <QGraphicsView>
#include <QLabel>
#include <QToolButton>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>

//TitleWidet::TitleWidet(QString strtitle, QWidget *parent)
//{

//}
class TitleWidget : public QWidget
{
public:
    TitleWidget(QString strtitle,QWidget *parent)
        : QWidget(parent),
        _pTitleLabel(nullptr),
        _pToolButton(nullptr)
    {
        setObjectName("TitleWidget");
        setMaximumHeight(45);
        _pTitleLabel = new QLabel(strtitle,this);
        _pTitleLabel->setObjectName("TitleLabel");
        _pToolButton = new QToolButton(this);

        QSpacerItem *pSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
        QHBoxLayout *playout = new QHBoxLayout;
        playout->setMargin(0);
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
      m_pTitleBar(nullptr)
{
    setObjectName("FgoDisplayerWidget");
}


void FgoDisplayerWidget::initLayout()
{
    m_pTitleBar = new TitleWidget(m_strTitle,this);
    if(m_pGraphicsView)
    {
       QVBoxLayout *playout = new QVBoxLayout;
       playout->setMargin(0);
       playout->setSpacing(0);
       playout->addWidget(m_pTitleBar);
       playout->addWidget(m_pGraphicsView);
       this->setLayout(playout);
    }
}

void FgoDisplayerWidget::setGraphicsView(QGraphicsView *pView)
{
    m_pGraphicsView = pView;
    initLayout();
}

