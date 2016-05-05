// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Solver
//
// =============================================================================
#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "TSP_Shared.h"
#include <QObject>

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
    virtual void StartAlgorithm();
    virtual void StopAlgorithm();
    virtual void PauseAlgorithm();
    virtual void ContinueAlgorithm();
    virtual bool IsWorking();
    virtual void Update(){}

signals:
    void updateInfo(vectorint vec, float fit, int id);
    void finished(TSP_Solver *solver);

protected:
    TSP_Algorithm *m_pAlgorithm;
    TSP_Map     *m_pMap;
    bool        m_bStop;
    bool        m_bPaused;
};

#endif // TSP_SOLVER_H
