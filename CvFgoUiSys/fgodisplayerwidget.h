#ifndef FGODISPLAYERWIDGET_H
#define FGODISPLAYERWIDGET_H

#include <QWidget>

class QGraphicsView;
class QLabel;
class QToolButton;

class FgoDisplayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FgoDisplayerWidget(QString strTiltle,QWidget *parent = nullptr);

    void initLayout();
    void setGraphicsView(QGraphicsView *pView);

protected:
    QGraphicsView *m_pGraphicsView;
    QWidget *m_pTitleBar;
    QString m_strTitle;
};

#endif // FGODISPLAYERWIDGET_H
