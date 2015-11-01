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

class TSP_Solver : public QThread
{
    Q_OBJECT

public:
    TSP_Solver(TSP_Algorithm *pAlgorithm, TSP_Map *pMap);
    ~TSP_Solver();
    virtual void run();

public slots:
    //virtual void SetSettings(int iPopsize = 0, float fElitrate = 0, float fMutation = 0, float fSupmutation = 0);
    virtual void StartAlgorithm(){}
    virtual void StopAlgorithm(){}

signals:
    void updateWay(vectorint vec);

protected:
    TSP_Algorithm *m_pAlgorithm;
    TSP_Map     *m_pMap;
    QMutex      m_Mutex;
    bool        m_bStop;
};

#endif // TSP_SOLVER_H
