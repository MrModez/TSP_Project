#ifndef TSP_SOLVERCOLLECTION_H
#define TSP_SOLVERCOLLECTION_H

#include "TSP_Shared.h"
#include <QObject>
#include <QVector>
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
    TSP_SolverCollection(TSP_Map *pMap, QObject *parent = 0);
    ~TSP_SolverCollection();

    TSP_Solver *Fabricate(int ID);
    void Solve(int ID, QVector<float> arg);
    void Stop(int ID);
    void Pause(int ID);
    void Continue(int ID);
    bool IsWorking(int ID);
    void Finished(TSP_Result result);

signals:
    void onFinish(int ID);

private:
    QVector<TSP_Solver*>    m_pSolvers;
    QVector<bool>            m_Status;
    TSP_Map                    *m_pMap;
};

#endif // TSP_SOLVERCOLLECTION_H
