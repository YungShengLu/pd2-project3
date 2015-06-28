#-------------------------------------------------
#
# Project created by QtCreator 2015-06-18T01:46:52
#
#-------------------------------------------------

QT       += core gui multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CandyCrush
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    subject.cpp \
    candy.cpp \
    board.cpp \
    game.cpp \
    judgeLined.cpp \
    judgeStriped.cpp \
    judgeWrapped.cpp \
    judgeColourBomb.cpp \
    QCandy.cpp

HEADERS  += mainwindow.h \
    QHeaderfile.h \
    game.h \
    observer.h \
    subject.h \
    board.h \
    candy.h \
    judgeLined.h \
    judgeStriped.h \
    judgeWrapped.h \
    judgeColourBomb.h \
    QCandy.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
