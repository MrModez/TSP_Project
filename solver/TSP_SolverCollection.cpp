#include "TSP_SolverCollection.h"
#include "TSP_GASolver.h"
#include "TSP_Map.h"

TSP_SolverCollection::TSP_SolverCollection()
{
    m_pMap = new TSP_Map();
    m_pSolvers.resize(Prob_Count);
}

void TSP_SolverCollection::AddSolver(TSP_Problem iProb)
{
    TSP_Solver *pSolver;
    if (iProb == Prob_GA)
    {
        pSolver = new TSP_GASolver(pMap);
    }

    m_pSolvers[iProb] = pSolver;
    //m_pAlgorithms[iProb] = pAlgorithm;
}

