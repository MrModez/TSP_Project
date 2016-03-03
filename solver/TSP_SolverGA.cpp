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

#define GA dynamic_cast<TSP_GA*>(m_pAlgorithm)

TSP_SolverGA::TSP_SolverGA(TSP_Algorithm *pAlgorithm, TSP_Map *pMap) : TSP_Solver(pAlgorithm, pMap)
{
    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    //timer->start(1000);
}

void TSP_SolverGA::SetSettings(std::vector<float>args)
{
    GA->SetSettings(args);
}

void TSP_SolverGA::Execute()
{
    GA->Reset();
    GA->SetArray(m_pMap->GetArray());
    GA->InitPopulation();
    qDebug("GA RUN");

    int index = 0;
    while (!m_bStop)
    {
        //m_Mutex.lock();
        //if (this->m_bStop) break;
        //m_Mutex.unlock();

        qDebug("GA %i:", index++);
        GA->NextIteration();
        GA->CalcFitness();
        GA->SortByFitness();

        vectorint best = GA->GetBestWay();
        float fit = GA->GetBestFitness();
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

        GA->Mate();
        GA->Swap();
    }
    emit finished();
}

void TSP_SolverGA::StartAlgorithm()
{
    qDebug("TSP_SolverGA::StartGA");
    m_bStop = false;
    Execute();
}

void TSP_SolverGA::StopAlgorithm()
{
    qDebug("TSP_SolverGA::StopGA");
    m_bStop = true;
}

void TSP_SolverGA::Update()
{
    qDebug("TSP_SolverGA::Update");
    m_pMap->SetWay(GA->GetBestWay());
}
