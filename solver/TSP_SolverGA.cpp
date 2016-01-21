// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: GA Solver
//
// =============================================================================
#include "TSP_SolverGA.h"
#include "TSP_GA.h"
#include "TSP_Algorithm.h"
#include "TSP_Map.h"
#include <QtCore>

#define CAST_GA(alg) dynamic_cast<TSP_GA*>(alg)

TSP_SolverGA::TSP_SolverGA(TSP_Algorithm *pAlgorithm, TSP_Map *pMap) : TSP_Solver(pAlgorithm, pMap)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start(1000);
}

void TSP_SolverGA::SetSettings(int iPopsize, float fElitrate, float fMutation, float fSupmutation)
{
    CAST_GA(m_pAlgorithm)->SetSettings(iPopsize, fElitrate, fMutation, fSupmutation);
}

void TSP_SolverGA::Execute()
{
    CAST_GA(m_pAlgorithm)->Reset();
    CAST_GA(m_pAlgorithm)->SetArray(m_pMap->GetArray());
    CAST_GA(m_pAlgorithm)->InitPopulation();
    qDebug("GA RUN");

    int index = 0;
    while (!m_bStop)
    {
        //m_Mutex.lock();
        //if (this->m_bStop) break;
        //m_Mutex.unlock();

        qDebug("GA %i:", index++);
        CAST_GA(m_pAlgorithm)->NextIteration();
        CAST_GA(m_pAlgorithm)->CalcFitness();
        CAST_GA(m_pAlgorithm)->SortByFitness();

        vectorint best = CAST_GA(m_pAlgorithm)->GetBestWay();
        float fit = CAST_GA(m_pAlgorithm)->GetBestFitness();
        QString str = "";
        for (auto &i : best)
        {
            str += QString::number(i) + " ";
        }
        QByteArray bstr = str.toLatin1();
        qDebug("WAY %s", bstr.data());
        qDebug("FIT %f\n", fit);
        emit updateWay(best);
        m_pMap->SetWay(best);
        //QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

        CAST_GA(m_pAlgorithm)->Mate();
        CAST_GA(m_pAlgorithm)->Swap();
    }
    emit finished();
}

void TSP_SolverGA::StartAlgorithm()
{
    qDebug("StartGA");
    m_bStop = false;
    Execute();
}

void TSP_SolverGA::StopAlgorithm()
{
    qDebug("StopGA");
    m_bStop = true;
}

void TSP_SolverGA::Update()
{
    qDebug("Update");
    m_pMap->SetWay(CAST_GA(m_pAlgorithm)->GetBestWay());
}
