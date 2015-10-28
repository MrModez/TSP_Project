// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Base TSP algorithm
//
// =============================================================================
#ifndef TSP_ALGORITHM_H
#define TSP_ALGORITHM_H

#include "TSP_Shared.h"
#include <QThread>

class TSP_Map;

class TSP_Algorithm : public QThread
{
    Q_OBJECT

public:
    TSP_Algorithm(TSP_Map* Map);
    virtual void NextIteration();
    virtual void Reset();
    virtual int GetIteration();
    virtual float GetFitness();
    virtual vectorint GetBestWay() = 0;

public slots:
    virtual void StartAlgorithm(){};
    virtual void StopAlgorithm(){};

signals:
    void updateWay(vectorint vec);

protected:
    TSP_Map*    m_pMap;
    vectorint   m_Way;

    float       m_fFitness;
    int         m_iIteration;
    bool        m_bShow;
};

#endif // TSP_ALGORITHM_H
