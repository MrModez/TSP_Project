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
}

void TSP_SolverGA::SetSettings(QVector<float>args, float result /* = -1.0f*/)
{
    GA->SetSettings(args.toStdVector());
    m_fResult = result;
}

void TSP_SolverGA::Execute()
{
    GA->Reset();
    GA->SetArray(m_pMap->GetArray());
    GA->InitPopulation();
    //qDebug("GA RUN");

    int wait = 10;
    int left = wait;

    int index = 0;
    float best_fit = INT_MAX;
    while (!m_bStop)
    {
        if (m_bPaused && !m_bStop)
        {
            qDebug() << "GA Paused";
            continue;
        }

        GA->NextIteration();
        GA->CalcFitness();
        GA->SortByFitness();
        index++;
        left--;

        float fit = GA->GetBestFitness();
        if (fit < best_fit)
        {
            best_fit = fit;
            left = wait;
            vectorint best = GA->GetBestWay();
            /*
            qDebug("GA %i:", index);
            QString str = "";
            for (auto &i : best)
            {
                str += QString::number(i) + " ";
            }
            QByteArray bstr = str.toLatin1();
            qDebug("WAY %s", bstr.data());
            qDebug("FIT %f\n", fit);
            */
            emit updateInfo(best, fit, index);
        }
        if ((m_fResult > 0.0 && fit == m_fResult) || left == 0)
        {
            m_bStop = true;
        }
        GA->Mate();
        GA->Swap();
    }
    m_bStop = true;
    emit finished();
}

void TSP_SolverGA::Update()
{
    qDebug("TSP_SolverGA::Update");
    m_pMap->SetWay(GA->GetBestWay());
}
