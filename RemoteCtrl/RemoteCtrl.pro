#-------------------------------------------------
#
# Project created by QtCreator 2021-07-07T19:53:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteCtrl
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv

LIBS += -I/usr/include/opencv \
/usr/lib/x86_64-linux-gnu/libopencv_calib3d.so -lopencv_calib3d /usr/lib/x86_64-linux-gnu/libopencv_contrib.so -lopencv_contrib /usr/lib/x86_64-linux-gnu/libopencv_core.so -lopencv_core /usr/lib/x86_64-linux-gnu/libopencv_features2d.so -lopencv_features2d /usr/lib/x86_64-linux-gnu/libopencv_flann.so -lopencv_flann /usr/lib/x86_64-linux-gnu/libopencv_gpu.so -lopencv_gpu /usr/lib/x86_64-linux-gnu/libopencv_highgui.so -lopencv_highgui /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so -lopencv_imgproc /usr/lib/x86_64-linux-gnu/libopencv_legacy.so -lopencv_legacy /usr/lib/x86_64-linux-gnu/libopencv_ml.so -lopencv_ml /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so -lopencv_objdetect /usr/lib/x86_64-linux-gnu/libopencv_ocl.so -lopencv_ocl /usr/lib/x86_64-linux-gnu/libopencv_photo.so -lopencv_photo /usr/lib/x86_64-linux-gnu/libopencv_stitching.so -lopencv_stitching /usr/lib/x86_64-linux-gnu/libopencv_superres.so -lopencv_superres /usr/lib/x86_64-linux-gnu/libopencv_ts.so -lopencv_ts /usr/lib/x86_64-linux-gnu/libopencv_video.so -lopencv_video /usr/lib/x86_64-linux-gnu/libopencv_videostab.so -lopencv_videostab


SOURCES += main.cpp\
        mainwindow.cpp \
    serverprocess.cpp \
    serverwindow.cpp \
    SocketMatTransmissionServer.cpp

HEADERS  += mainwindow.h \
    serverprocess.h \
    serverwindow.h \
    SocketMatTransmissionServer.h

FORMS    += mainwindow.ui \
    serverwindow.ui
