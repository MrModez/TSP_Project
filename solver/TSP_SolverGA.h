// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: GA Solver
//
// =============================================================================
#ifndef TSP_SOLVERGA_H
#define TSP_SOLVERGA_H

#include "TSP_Solver.h"
#include "TSP_GA.h"

class TSP_SolverGA : public TSP_Solver
{
public:
    TSP_SolverGA(TSP_Algorithm *pAlgorithm, TSP_Map *pMap);
    virtual void Execute();
    void SetSettings(int iPopsize, float fElitrate, float fMutation, float fSupmutation);

public slots:
    virtual void StartAlgorithm();
    virtual void StopAlgorithm();
};

#endif // TSP_SOLVERGA_H
