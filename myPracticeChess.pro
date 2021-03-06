QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    choosebar.cpp \
    ctrlpanel.cpp \
    main.cpp \
    mainwindow.cpp \
    multigame.cpp \
    netgame.cpp \
    piece.cpp \
    singlegame.cpp \
    step.cpp

HEADERS += \
    board.h \
    choosebar.h \
    ctrlpanel.h \
    mainwindow.h \
    multigame.h \
    netgame.h \
    piece.h \
    singlegame.h \
    step.h

