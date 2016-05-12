#include <QtCore>
#include "TSP_ExpertSolver.h"
#include "TSP_Map.h"
#include "TSP_SolverGA.h"

TSP_ExpertSolver::TSP_ExpertSolver(TSP_Map *map, QVector<int>args, QObject *parent) : QObject(parent)
{
    m_ID = args[0];
    m_iTries = args[1];
    m_pMap = map;
}

TSP_ExpertSolver::~TSP_ExpertSolver()
{
}

void TSP_ExpertSolver::StartWorking()
{
    m_pSolver = new TSP_SolverGA(new TSP_GA(), m_pMap);
    connect(m_pSolver, &TSP_Solver::updateInfo, this, &TSP_ExpertSolver::UpdateInfo);
    connect(m_pSolver, &TSP_Solver::finished, this, &TSP_ExpertSolver::Finished);
    float mut1 = 0.0;
    float mut2 = 0.0;
    float mut3 = 0.0;
    int ID = m_ID % 8;
    if (ID == 1)
    {
        mut1 = 0.5f;
    }
    if (ID == 2)
    {
        mut2 = 0.5f;
    }
    if (ID == 3)
    {
        mut3 = 0.5f;
    }
    if (ID == 4)
    {
        mut1 = 0.33f;
        mut2 = 0.66f;
    }
    if (ID == 5)
    {
        mut2 = 0.33f;
        mut3 = 0.66f;
    }
    if (ID == 6)
    {
        mut1 = 0.33f;
        mut3 = 0.66f;
    }
    if (ID == 7)
    {
        mut1 = 0.25f;
        mut2 = 0.50f;
        mut3 = 0.75f;
    }
    QVector<float>arg{10000, 0.001f, mut1, mut2, mut3};
    dynamic_cast<TSP_SolverGA*>(m_pSolver)->SetSettings(arg);
    m_pSolver->StartAlgorithm();
}

void TSP_ExpertSolver::Finished(TSP_Result result)
{
    //qDebug() << "FINISHED" << m_ID << "WITH" << m_iTries << "TRIES LEFT";

    //m_pSolver->deleteLater();
    delete m_pSolver;   //cleans memory faster

    if (m_iTries == 0)
    {
        emit finished(result.fit, m_iTries);
        return;
    }

    emit updateInfo(result.fit, m_iTries);
    m_iTries--;
    StartWorking();
}

void TSP_ExpertSolver::UpdateInfo(TSP_Result result)
{
    //qDebug() << m_ID << result.fit;
    // emit updateInfo(result.fit, m_iTries);
}
