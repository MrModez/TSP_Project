#include <QtCore>
#include "TSP_ExpertManager.h"
#include "TSP_Map.h"
#include "TSP_SolverGA.h"
#include "TSP_SolverBB.h"

TSP_ExpertManager::TSP_ExpertManager(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<vectorint>("vectorint");
}

TSP_ExpertManager::~TSP_ExpertManager()
{
    m_pSolvers.clear();
    m_pMaps.clear();
}

void TSP_ExpertManager::Init(QVector<float>args)
{
    m_iSize = args[0];
    m_iCities = args[1];
    m_iTries = args[2];
    for (int i = 0; i < m_iSize; i++)
    {
        QPointer<TSP_Map> pMap = new TSP_Map();
        pMap->GenerateRandom(m_iCities);
        m_pMaps.push_back(pMap);
        QPointer<TSP_Solver>pSolver = new TSP_SolverGA(new TSP_GA(), pMap);
        m_pSolvers.push_back(pSolver);
        m_Tries.push_back(m_iTries);
        //QThread *pSolverThread = new QThread(this);
        //m_pSolverThreads.push_back(pSolverThread);
        InitSolver(i);
    }
}

void TSP_ExpertManager::InitSolver(int ID)
{
    qDebug() << "START" << ID;
    QThread *pSolverThread = new QThread(this);

    m_pSolvers[ID]->moveToThread(pSolverThread);
    connect(m_pSolvers[ID], &TSP_Solver::updateInfo, this, &TSP_ExpertManager::UpdateInfo);
    connect(pSolverThread, &QThread::started, m_pSolvers[ID], &TSP_Solver::StartAlgorithm);
    connect(m_pSolvers[ID], &TSP_Solver::finished, this, &TSP_ExpertManager::Finished);
    connect(m_pSolvers[ID], &TSP_Solver::finished, pSolverThread, &QThread::quit);
    //connect(m_pSolvers[ID], &TSP_Solver::finished, m_pSolvers[ID], &TSP_Solver::deleteLater);
    connect(pSolverThread, &QThread::finished, pSolverThread, &QThread::deleteLater);

    QVector<float>arg{10000, 0.001f, 0.20f, 0.55f, 0.75f};
    dynamic_cast<TSP_SolverGA*>(m_pSolvers[ID])->SetSettings(arg);

    pSolverThread->start();
}

void TSP_ExpertManager::Finished()
{
    TSP_Solver *Solver = qobject_cast<TSP_Solver*>(sender());
    int ID = m_pSolvers.indexOf(Solver);
    qDebug() << "FINISHED" << ID << "AT" << m_Tries[ID];
    Solver->deleteLater();

    if (m_Tries[ID] == 0)
        return;

    m_pSolvers[ID] = new TSP_SolverGA(new TSP_GA(), m_pMaps[ID]);
    m_Tries[ID]--;
    InitSolver(ID);
}

void TSP_ExpertManager::UpdateInfo(vectorint vec, float fit, int id)
{
    TSP_Solver *Solver = qobject_cast<TSP_Solver*>(sender());
    int ID = m_pSolvers.indexOf(Solver);
    qDebug() << ID << fit;
}





