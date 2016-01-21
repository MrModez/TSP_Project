#ifndef TSP_SOLVERCOLLECTION_H
#define TSP_SOLVERCOLLECTION_H

#include "TSP_Shared.h"

class TSP_Solver;
class TSP_Algorithm;
class TSP_Map;

enum TSP_Problem
{
    Prob_GA,
    Prob_BB,

    Prob_Count
};

class TSP_SolverCollection
{
public:
    TSP_SolverCollection();

    void AddSolver(TSP_Problem iProb);


private:
    std::vector<TSP_Solver*>    m_pSolvers;
    TSP_Map                    *m_pMap;
};

#endif // TSP_SOLVERCOLLECTION_H
