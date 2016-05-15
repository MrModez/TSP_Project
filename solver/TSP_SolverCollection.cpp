// ===== Copyright © 2015-2016, MrModez (Zagir Fabarisov), Flatag (Tagir Fabarisov), All rights reserved. =====
//
// Purpose: Class for managing solvers
// Назначение: Класс для управления решателями
//
// ============================================================================================================
#include <QtCore>
#include "TSP_SolverCollection.h"
#include "TSP_SolverGA.h"
#include "TSP_SolverBB.h"
#include "TSP_Map.h"

TSP_SolverCollection::TSP_SolverCollection(TSP_Map *pMap, QObject *parent) : QObject(parent)
{
    qRegisterMetaType<vectorint>("vectorint");
    qRegisterMetaType<TSP_Result>("TSP_Result");

    m_pMap = pMap;
    for (int i = 0; i < Solver_Count; i++)
    {
        QPointer<TSP_Solver>solver;
        m_pSolvers.push_back(solver);
        m_Status.push_back(false);
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

void TSP_SolverCollection::Solve(int ID, QVector<float> arg)
{
    qDebug("Solving %i", ID);

    if (m_pMap->GetArray().size() < 4)
    {
        emit onFinish(ID);
        return;
    }

    QThread *pSovlerThread = new QThread(this);
    m_pSolvers[ID] = Fabricate(ID);
    m_pSolvers[ID]->moveToThread(pSovlerThread);
    m_Status[ID] = true;

    connect(m_pSolvers[ID], &TSP_Solver::updateInfo,  m_pMap, &TSP_Map::UpdateInfo);
    connect(pSovlerThread, &QThread::started, m_pSolvers[ID], &TSP_Solver::StartAlgorithm);
    connect(m_pSolvers[ID], &TSP_Solver::finished, this, &TSP_SolverCollection::Finished);
    connect(m_pSolvers[ID], &TSP_Solver::finished, pSovlerThread, &QThread::quit);
    //connect(m_pSolvers[ID], &TSP_Solver::finished, m_pSolvers[ID], &TSP_Solver::deleteLater);
    connect(pSovlerThread, &QThread::finished, pSovlerThread, &QThread::deleteLater);

    if (ID == Solver_GA)
    {
        //std::vector<float>arg{10000, 0.001f, 0.20f, 0.55f, 0.75f};
        dynamic_cast<TSP_SolverGA*>(m_pSolvers[ID])->SetSettings(arg);
    }

    pSovlerThread->start();
}

void TSP_SolverCollection::Finished(TSP_Result result)
{
    TSP_Solver *Solver = qobject_cast<TSP_Solver*>(sender());
    int ID = m_pSolvers.indexOf(Solver);
    m_Status[ID] = false;
    emit onFinish(ID);
    Solver->deleteLater();
}

void TSP_SolverCollection::Pause(int ID)
{
    qDebug("Pausing %i", ID);
    if (m_Status[ID] && m_pSolvers[ID])
    {
        m_pSolvers[ID]->PauseAlgorithm();
    }
}

void TSP_SolverCollection::Continue(int ID)
{
    qDebug("Continuing %i", ID);
    if (m_Status[ID] && m_pSolvers[ID])
    {
        m_pSolvers[ID]->ContinueAlgorithm();
    }
}


void TSP_SolverCollection::Stop(int ID)
{
    qDebug("Stopping %i", ID);
    if (m_Status[ID] && m_pSolvers[ID])
    {
        m_pSolvers[ID]->StopAlgorithm();
    }
}

bool TSP_SolverCollection::IsWorking(int ID)
{
    if (m_Status[ID] && m_pSolvers[ID])
    {
        return m_pSolvers[ID]->IsWorking();
    }
    return false;
}
