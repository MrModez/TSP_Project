// ====== Copyright © 2015-2016, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: BB Solver
//
// =============================================================================
#include "TSP_SolverBB.h"
#include "TSP_BB.h"
#include "TSP_Algorithm.h"
#include "TSP_Map.h"
#include <QtCore>

#define BB dynamic_cast<TSP_BB*>(m_pAlgorithm)

TSP_SolverBB::TSP_SolverBB(TSP_Algorithm *pAlgorithm, TSP_Map *pMap) : TSP_Solver(pAlgorithm, pMap)
{
    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    //timer->start(1000);
}

void TSP_SolverBB::Execute()
{
    BB->SetArray(m_pMap->GetArray());
    BB->Reset();
    //BB->InitPopulation();
    qDebug("GA RUN");

    int index = 0;
    while (!m_bStop)
    {
        qDebug("BB %i:", index++);
        BB->Start();

        //m_Mutex.lock();
        //if (this->m_bStop) break;
        //m_Mutex.unlock();

        //BB->NextIteration();
        //BB->CalcFitness();
        //BB->SortByFitness();

        vectorint best = BB->GetBestWay();
        float fit = BB->GetBestFitness();
        QString str = "";
        for (auto &i : best)
        {
            str += QString::number(i) + " ";
        }
        QByteArray bstr = str.toLatin1();
        qDebug("WAY %s", bstr.data());
        qDebug("FIT %f\n", fit);
        emit updateInfo(best, fit, index);
        //QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

        //BB->Mate();
        //BB->Swap();
        StopAlgorithm();
    }
    emit finished();
}

void TSP_SolverBB::StartAlgorithm()
{
    qDebug("TSP_SolverBB::StartBB");
    m_bStop = false;
    Execute();
}

void TSP_SolverBB::StopAlgorithm()
{
    qDebug("TSP_SolverBB::StopBB");
    m_bStop = true;
}

void TSP_SolverBB::Update()
{
    qDebug("TSP_SolverBB::Update");
    m_pMap->SetWay(BB->GetBestWay());
}
