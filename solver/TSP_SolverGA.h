// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: GA Solver
//
// =============================================================================
#ifndef TSP_SOLVERGA_H
#define TSP_SOLVERGA_H

#include "TSP_Solver.h"
#include "TSP_GA.h"

class QTimer;

class TSP_SolverGA : public TSP_Solver
{
    Q_OBJECT

public:
    TSP_SolverGA(TSP_Algorithm *pAlgorithm, TSP_Map *pMap);
    virtual void Execute();
    void SetSettings(QVector<float> args, float result = -1.0f);

public slots:
    virtual void Update();

private:
    float m_fResult;
};

#endif // TSP_SOLVERGA_H
