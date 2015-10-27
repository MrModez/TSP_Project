#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T23:29:03
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TSP_Project
TEMPLATE = app


SOURCES += main.cpp\
    TSP_Map.cpp \
    TSP_Shared.cpp \
    TSP_GA.cpp \
    TSP_MainWindow.cpp \
    TSP_Canvas.cpp \
    TSP_BB.cpp \
    TSP_Algorithm.cpp

HEADERS  += \
    TSP_Map.h \
    TSP_Shared.h \
    TSP_GA.h \
    TSP_MainWindow.h \
    TSP_Canvas.h \
    TSP_BB.h \
    TSP_Algorithm.h

FORMS    += \
    TSP_MainWindow.ui
