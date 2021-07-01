#-------------------------------------------------
#
# Project created by QtCreator 2021-06-29T14:08:21
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2021thubot
TEMPLATE = app
#QT       += multimedia
#QT       += multimediawidgets

SOURCES += main.cpp\
        logwindow.cpp \
    modeswindow.cpp \
    autotouristwindow.cpp \
    datuimage.cpp

HEADERS  += logwindow.h \
    modeswindow.h \
    autotouristwindow.h \
    datuimage.h

FORMS    += logwindow.ui \
    modeswindow.ui \
    autotouristwindow.ui \
    datuimage.ui

RESOURCES += \
    image.qrc

