#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T23:29:03
#
#-------------------------------------------------

QT       += core gui opengl

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TSP_Project
TEMPLATE = app
INCLUDEPATH += algorithm \
               expert   \
               forms    \
               shared   \
               solver

LIBS+=-lgomp
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
    forms/TSP_BaseWindow.cpp \
    forms/TSP_ExpertWindow.cpp \
    expert/TSP_ExpertManager.cpp \
    expert/TSP_ExpertSolver.cpp

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
    forms/TSP_BaseWindow.h \
    forms/TSP_ExpertWindow.h \
    expert/TSP_ExpertManager.h \
    expert/TSP_ExpertSolver.h

FORMS    += \
    forms/TSP_MainWindow.ui \
    forms/TSP_SolverWindow.ui \
    forms/TSP_ExpertWindow.ui
