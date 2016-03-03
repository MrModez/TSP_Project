#include <QtCore>
#include "TSP_SolverCollection.h"
#include "TSP_SolverGA.h"
#include "TSP_SolverBB.h"
#include "TSP_Map.h"

TSP_SolverCollection::TSP_SolverCollection(TSP_Map *pMap)
{
    m_pMap = pMap;
    for (int i = 0; i < Solver_Count; i++)
    {
        QPointer<TSP_Solver>solver;
        m_pSolvers.push_back(solver);
    }
}

TSP_SolverCollection::~TSP_SolverCollection()
{
}

TSP_Solver *TSP_SolverCollection::Fabricate(int ID)
{
    if (ID == Solver_GA)
    {
        return new TSP_SolverGA(new TSP_GA(), m_pMap);
    }
    if (ID == Solver_BB)
    {
        return  new TSP_SolverBB(new TSP_BB(), m_pMap);
    }
    return NULL;
}

void TSP_SolverCollection::Solve(int ID)
{
    qDebug("Solving %i", ID);

    QThread *pSovlerThread = new QThread;
    m_pSolvers[ID] = Fabricate(ID);
    m_pSolvers[ID]->moveToThread(pSovlerThread);

    qRegisterMetaType<vectorint>("vectorint");
    connect(m_pSolvers[ID], &TSP_Solver::updateWay,  m_pMap, &TSP_Map::SetWay);
    connect(pSovlerThread, &QThread::started, m_pSolvers[ID], &TSP_Solver::StartAlgorithm);
    connect(m_pSolvers[ID], &TSP_Solver::finished, pSovlerThread, &QThread::quit);
    connect(m_pSolvers[ID], &TSP_Solver::finished, m_pSolvers[ID], &TSP_Solver::deleteLater);
    connect(pSovlerThread, &QThread::finished, pSovlerThread, &QThread::deleteLater);

    if (ID == Solver_GA)
    {
        int pop = 10000;
        float elit = 0.001f;
        float mut = 0.55f;
        float supmut = 0.75f;
        dynamic_cast<TSP_SolverGA*>(m_pSolvers[ID])->SetSettings(pop, elit, mut, supmut);
    }

    pSovlerThread->start();
}

void TSP_SolverCollection::Stop(int ID)
{
    qDebug("Stopping %i", ID);
    if (m_pSolvers[ID])
    {
        m_pSolvers[ID]->StopAlgorithm();
    }
}
