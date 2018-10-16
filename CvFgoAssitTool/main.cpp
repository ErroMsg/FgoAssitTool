#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    {
        QFile  qssFile("/home/gaopy/GitHubProj/Build/stypesheet.qss");
        if(qssFile.open(QFile::ReadOnly))
        {
            QString ba = QLatin1String(qssFile.readAll());
            qDebug()<<ba;
            qssFile.close();
            qApp->setStyleSheet(ba);
        }
    }

    w.show();

    return a.exec();
}
