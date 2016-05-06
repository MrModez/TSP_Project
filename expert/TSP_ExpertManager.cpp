#include <QtCore>
#include "TSP_ExpertManager.h"
#include "TSP_ExpertSolver.h"

TSP_ExpertManager::TSP_ExpertManager(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<vectorint>("vectorint");
    qRegisterMetaType<TSP_Result>("TSP_Result");
}

TSP_ExpertManager::~TSP_ExpertManager()
{
    m_pExpertSolvers.clear();
}

void TSP_ExpertManager::Init(QVector<float>args)
{
    m_iSize = args[0];
    m_iCities = args[1];
    m_iTries = args[2];
    for (int i = 0; i < m_iSize; i++)
    {
        TSP_ExpertSolver *pExpertSolver = new TSP_ExpertSolver(i, m_iCities, m_iTries);
        m_pExpertSolvers.push_back(pExpertSolver);
        InitSolver(i);
    }
}

void TSP_ExpertManager::InitSolver(int ID)
{
    qDebug() << "START" << ID;
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
    qDebug() << "THREAD UPDATED" << ID;
    emit UpdateTable(ID, iter, fit);
}

void TSP_ExpertManager::Finished(float fit, int iter)
{
    TSP_ExpertSolver *pExpertSolver = qobject_cast<TSP_ExpertSolver*>(sender());
    int ID = m_pExpertSolvers.indexOf(pExpertSolver);
    qDebug() << "THREAD FINISHED" << ID;
    pExpertSolver->deleteLater();
    //emit UpdateTable(ID, iter, fit);
}




