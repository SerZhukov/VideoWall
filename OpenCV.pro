QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

CONFIG += c++17

TARGET = opencvtest
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    handlerrtsp.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    rtspinputdisplay.cpp \
    screen.cpp \
    screenaddsettings.cpp \
    screenpartitionbuttons.cpp \
    videoplayer.cpp \
    worksreens.cpp

HEADERS += \
    handlerrtsp.h \
    mainwindow.h \
    player.h \
    rtspinputdisplay.h \
    screen.h \
    screenaddsettings.h \
    screenpartitionbuttons.h \
    videoplayer.h \
    worksreens.h

INCLUDEPATH += C:\OpenCV\opencv\release\install\include

LIBS += C:\OpenCV\opencv\release\bin\libopencv_core4100.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_highgui4100.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_imgcodecs4100.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_imgproc4100.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_features2d4100.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_calib3d4100.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_videoio4100.dll
LIBS += C:\OpenCV\opencv\release\bin\libopencv_video4100.dll


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../../../Users/Sergey Zhukov/Desktop/icon/icon_screens.jpg

RESOURCES += \
    resource.qrc
