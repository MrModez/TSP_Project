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
               forms    \
               shared   \
               solver

QMAKE_LIBS+=-static -lgomp -lpthread
QMAKE_CXXFLAGS+=-fopenmp

SOURCES += main.cpp\
    algorithm/TSP_Algorithm.cpp \
    algorithm/TSP_BB.cpp \
    algorithm/TSP_GA.cpp \
    forms/TSP_Canvas.cpp \
    forms/TSP_MainWindow.cpp \
    forms/TSP_Map.cpp \
    shared/TSP_Shared.cpp \
    solver/TSP_SolverCollection.cpp \
    solver/TSP_Solver.cpp \
    solver/TSP_SolverGA.cpp \
    solver/TSP_SolverBB.cpp \
    forms/TSP_SolverWindow.cpp \
    forms/TSP_BaseWindow.cpp

HEADERS  += \
    algorithm/TSP_Algorithm.h \
    algorithm/TSP_BB.h \
    algorithm/TSP_GA.h \
    forms/TSP_Canvas.h \
    forms/TSP_MainWindow.h \
    forms/TSP_Map.h \
    shared/TSP_Shared.h \
    solver/TSP_SolverCollection.h \
    solver/TSP_Solver.h \
    solver/TSP_SolverGA.h \
    solver/TSP_SolverBB.h \
    forms/TSP_SolverWindow.h \
    forms/TSP_BaseWindow.h

FORMS    += \
    forms/TSP_MainWindow.ui \
    forms/TSP_SolverWindow.ui
