#-------------------------------------------------
#
# Project created by QtCreator 2018-10-09T18:35:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CvFgoAssitTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(CvFgoAssitTool/CvFgoAssitTool.pri)
include(CvFgoUiSys/CvFgoUiSys.pri)

win32:{
INCLUDEPATH += D:/opencv/build/include \
                D:/opencv/build/include/opencv \
                D:/opencv/build/include/opencv2

DEPENDPATH += D:/opencv/build/x64/vc14

CONFIG(debug, debug|release): LIBS += -LD:/opencv/build/x64/vc14/lib/ -lopencv_world343d
CONFIG(release, debug|release): LIBS += -LD:/opencv/build/x64/vc14/lib/ -lopencv_world343
}

linux:{
INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so
}

macx:{
INCLUDEPATH +=/usr/local/include
LIBS +=-L/usr/local/lib -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_imgcodecs
}


