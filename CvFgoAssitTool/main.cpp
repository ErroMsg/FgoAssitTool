#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile  qssFile("/home/gaopy/GitHubProj/Build/stypesheet.qss");
    if(qssFile.open(QFile::ReadOnly))
    {
        QString ba = QLatin1String(qssFile.readAll());
        qssFile.close();
        qApp->setStyleSheet(ba);
    }
    MainWindow w;
    w.show();

    return a.exec();
}
