#ifndef TSP_SOLVERCOLLECTION_H
#define TSP_SOLVERCOLLECTION_H

#include "TSP_Shared.h"
#include <QObject>
#include <QPointer>

class TSP_Solver;
class TSP_Map;

enum TSP_SolverID
{
    Solver_GA,
    Solver_BB,
    //...
    Solver_Count
};

class TSP_SolverCollection : public QObject
{
    Q_OBJECT

public:
    TSP_SolverCollection(TSP_Map *pMap);
    ~TSP_SolverCollection();

    TSP_Solver *Fabricate(int ID);
    void Solve(int ID, std::vector<float> arg);
    void Stop(int ID);
    void Pause(int ID);
    void Continue(int ID);
    bool IsWorking(int ID);

private:
    std::vector<TSP_Solver*>    m_pSolvers;
    TSP_Map                    *m_pMap;
};

#endif // TSP_SOLVERCOLLECTION_H
