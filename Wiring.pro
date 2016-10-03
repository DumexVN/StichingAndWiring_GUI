
#-------------------------------------------------
# -- MSc. FINAL PROJECT: VISUAL INTERFACE FOR ----
# -- EULER CIRCUIT AND EULER PATH IN STICHING ----
# ----------- AND WIRING PROBLEMS ----------------
# - Author: Ngoc Vu ------------------------------
# - Version: 1.0 ---------------------------------
#-------------------------------------------------
#-------------------------------------------------
#Project created by QtCreator 2013-07-24T19:01:45-
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wiring
TEMPLATE = app


SOURCES += main.cpp \
    algorithm.cpp \
    edge.cpp \
    vertex.cpp \
    propertiesdialog.cpp \
    graph.cpp \
    algorithmthread.cpp \
    graphview.cpp

HEADERS  += \
    algorithm.h \
    edge.h \
    vertex.h \
    propertiesdialog.h \
    LineAnimator.h \
    graph.h \
    removeAdjCommand.h \
    revertColorCommand.h \
    algorithmthread.h \
    graphview.h

FORMS    += propertiesdialog.ui

RESOURCES += wiring.qrc

