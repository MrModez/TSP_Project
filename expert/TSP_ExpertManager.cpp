#include <QtCore>
#include "TSP_ExpertManager.h"
#include "TSP_ExpertSolver.h"
#include "TSP_Map.h"

TSP_ExpertManager::TSP_ExpertManager(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<vectorint>("vectorint");
    qRegisterMetaType<TSP_Result>("TSP_Result");
    m_pMap = new TSP_Map();
}

TSP_ExpertManager::~TSP_ExpertManager()
{
    m_pExpertSolvers.clear();
    delete m_pMap;
}

void TSP_ExpertManager::Init(QVector<int>args)
{
    m_iSize = args[0];
    m_iCities = args[1];
    m_iTries = args[2];
    m_pMap->GenerateRandom(m_iCities);
    for (int i = 0; i < m_iSize; i++)
    {
        QVector<int>args = {i, m_iTries};
        TSP_ExpertSolver *pExpertSolver = new TSP_ExpertSolver(m_pMap, args);
        m_pExpertSolvers.push_back(pExpertSolver);
        InitSolver(i);
    }
}

void TSP_ExpertManager::InitSolver(int ID)
{
    qDebug() << "THREAD STARTED" << ID;
    QThread *pSolverThread = new QThread(this);
    TSP_ExpertSolver *pExpertSolver = m_pExpertSolvers[ID];

    pExpertSolver->moveToThread(pSolverThread);
    connect(pExpertSolver, &TSP_ExpertSolver::updateInfo, this, &TSP_ExpertManager::UpdateInfo);
    connect(pSolverThread, &QThread::started, pExpertSolver, &TSP_ExpertSolver::StartWorking);
    connect(pExpertSolver, &TSP_ExpertSolver::finished, this, &TSP_ExpertManager::UpdateInfo);
    connect(pExpertSolver, &TSP_ExpertSolver::finished, this, &TSP_ExpertManager::Finished);
    connect(pExpertSolver, &TSP_ExpertSolver::finished, pSolverThread, &QThread::quit);
    //connect(pExpertSolver, &TSP_ExpertSolver::finished, pExpertSolver, &TSP_ExpertSolver::deleteLater);
    connect(pSolverThread, &QThread::finished, pSolverThread, &QThread::deleteLater);

    pSolverThread->start();
}

void TSP_ExpertManager::UpdateInfo(float fit, int iter)
{
    TSP_ExpertSolver *pExpertSolver = qobject_cast<TSP_ExpertSolver*>(sender());
    int ID = m_pExpertSolvers.indexOf(pExpertSolver);
    //qDebug() << "THREAD UPDATED" << ID;
    emit updateTable(ID, m_iTries-iter, fit);
}

void TSP_ExpertManager::Finished(float fit, int iter)
{
    TSP_ExpertSolver *pExpertSolver = qobject_cast<TSP_ExpertSolver*>(sender());
    int ID = m_pExpertSolvers.indexOf(pExpertSolver);
    qDebug() << "THREAD FINISHED" << ID;
    pExpertSolver->deleteLater();
    emit updateTable(ID, m_iTries-iter, fit);
    emit finishedWorking();
}





