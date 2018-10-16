#ifndef FGODISPLAYERWIDGET_H
#define FGODISPLAYERWIDGET_H

#include <QWidget>
#include <QFrame>

class QLabel;
class QToolButton;
class QGraphicsScene;
class QGraphicsPixmapItem;
class FgoGraphicsView;

class TitleWidget : public QFrame
{
    Q_OBJECT
public:
    TitleWidget(QString strtitle,QWidget *parent=0);
private:
    QLabel *_pTitleLabel;
    QToolButton *_pToolButton;
};

class FgoDisplayerWidget : public QFrame
{
    Q_OBJECT
public:
    FgoDisplayerWidget(QString strTiltle,QWidget *parent = nullptr);

    void initLayout();
    FgoGraphicsView *getGraphicsView();
    QGraphicsScene *getGraphicsScene();
    void clearScene();
    QString getPostImagePath();

public slots:
    void postImage(QString strfilepath);

protected:
    FgoGraphicsView *m_pGraphicsView;
    QGraphicsScene *m_pScene;
    TitleWidget *m_pTitleBar;
    QString m_strTitle;
    QGraphicsPixmapItem *m_pPostedImage;
};

#endif // FGODISPLAYERWIDGET_H
