// ====== Copyright © 2015-2016, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: BB Solver
//
// =============================================================================
#ifndef TSP_SOLVERBB_H
#define TSP_SOLVERBB_H

#include "TSP_Solver.h"
#include "TSP_BB.h"

class QTimer;

class TSP_SolverBB : public TSP_Solver
{
    Q_OBJECT

public:
    TSP_SolverBB(TSP_Algorithm *pAlgorithm, TSP_Map *pMap);
    virtual void Execute();
    //void SetSettings(int iPopsize, float fElitrate, float fMutation, float fSupmutation);

public slots:
    virtual void StartAlgorithm();
    virtual void StopAlgorithm();
    virtual void Update();

signals:
    void finished();

private:
    QTimer *timer;
};

#endif // TSP_SolverBB_H
