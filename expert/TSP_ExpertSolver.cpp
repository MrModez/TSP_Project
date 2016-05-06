#include <QtCore>
#include "TSP_ExpertSolver.h"
#include "TSP_Map.h"
#include "TSP_SolverGA.h"

TSP_ExpertSolver::TSP_ExpertSolver(int ID, int cities, int tries, QObject *parent) : QObject(parent)
{
    m_ID = ID;
    m_iTries = tries;
    m_pMap = new TSP_Map();
    m_pMap->GenerateRandom(cities);
}

void TSP_ExpertSolver::StartWorking()
{
    m_pSolver = new TSP_SolverGA(new TSP_GA(), m_pMap);
    connect(m_pSolver, &TSP_Solver::updateInfo, this, &TSP_ExpertSolver::UpdateInfo);
    connect(m_pSolver, &TSP_Solver::finished, this, &TSP_ExpertSolver::Finished);
    QVector<float>arg{10000, 0.001f, 0.20f, 0.55f, 0.75f};
    dynamic_cast<TSP_SolverGA*>(m_pSolver)->SetSettings(arg);
    m_pSolver->StartAlgorithm();
}

void TSP_ExpertSolver::Finished(TSP_Result result)
{
    qDebug() << "FINISHED" << m_ID << "WITH" << m_iTries << "TRIES LEFT";
    //m_Results.push_back(result);
    m_pSolver->deleteLater();

    if (m_iTries == 0)
    {
        emit finished(result);
        return;
    }

    m_iTries--;
    StartWorking();
}

void TSP_ExpertSolver::UpdateInfo(TSP_Result result)
{
    qDebug() << m_ID << result.fit;
}

