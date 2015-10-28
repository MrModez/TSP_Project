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
INCLUDEPATH += algorithm \
               forms \
               shared

SOURCES += main.cpp\
    algorithm/TSP_Algorithm.cpp \
    algorithm/TSP_BB.cpp \
    algorithm/TSP_GA.cpp \
    algorithm/TSP_Map.cpp \
    forms/TSP_Canvas.cpp \
    forms/TSP_MainWindow.cpp \
    shared/TSP_Shared.cpp

HEADERS  += \
    algorithm/TSP_Algorithm.h \
    algorithm/TSP_BB.h \
    algorithm/TSP_GA.h \
    algorithm/TSP_Map.h \
    forms/TSP_Canvas.h \
    forms/TSP_MainWindow.h \
    shared/TSP_Shared.h

FORMS    += \
    forms/TSP_MainWindow.ui
