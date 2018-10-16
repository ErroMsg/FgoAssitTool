#ifndef FGODISPLAYERWIDGET_H
#define FGODISPLAYERWIDGET_H

#include <QWidget>


class QLabel;
class QToolButton;
class QGraphicsScene;
class QGraphicsItem;
class FgoGraphicsView;
class FgoDisplayerWidget : public QWidget
{
    Q_OBJECT
public:
    FgoDisplayerWidget(QString strTiltle,QWidget *parent = nullptr);

    void initLayout();
    FgoGraphicsView *getGraphicsView();
    QGraphicsScene *getGraphicsScene();
    QString getPostImagePath();

public slots:
    void postImage(QString strfilepath);

protected:
    FgoGraphicsView *m_pGraphicsView;
    QGraphicsScene *m_pScene;
    QWidget *m_pTitleBar;
    QString m_strTitle;

    QGraphicsItem *m_pPostedImage;
};

#endif // FGODISPLAYERWIDGET_H
