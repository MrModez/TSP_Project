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
}

void TSP_SolverBB::Execute()
{
    BB->SetArray(m_pMap->GetArray());
    BB->Reset();
    qDebug("BB RUN");

    int index = 0;
    vectorint best;
    float fit = 0.0;
    while (!m_bStop)
    {
        qDebug("BB %i:", index++);
        BB->Start();

        best = BB->GetBestWay();
        fit = BB->GetBestFitness();
        QString str = "";
        for (auto &i : best)
        {
            str += QString::number(i) + " ";
        }
        QByteArray bstr = str.toLatin1();
        qDebug("WAY %s", bstr.data());
        qDebug("FIT %f\n", fit);
        emit updateInfo(TSP_Result(best, fit, index));

        StopAlgorithm();
    }
    m_bStop = true;
    emit finished(TSP_Result(best, fit, index));
}

void TSP_SolverBB::Update()
{
    qDebug("TSP_SolverBB::Update");
    m_pMap->SetWay(BB->GetBestWay());
}
