// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Solver
//
// =============================================================================
#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "TSP_Shared.h"
#include <QThread>

class TSP_Algorithm;
class TSP_Map;

class TSP_Solver : public QObject
{
    Q_OBJECT

public:
    TSP_Solver(TSP_Algorithm *pAlgorithm, TSP_Map *pMap);
    ~TSP_Solver();
    virtual void Execute();

public slots:
    virtual void StartAlgorithm(){}
    virtual void StopAlgorithm(){}

signals:
    void updateWay(vectorint vec);
    void finished();

protected:
    TSP_Algorithm *m_pAlgorithm;
    TSP_Map     *m_pMap;
    QMutex      m_Mutex;
    bool        m_bStop;
};

#endif // TSP_SOLVER_H
