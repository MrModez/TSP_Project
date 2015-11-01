// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Base TSP algorithm
//
// =============================================================================
#ifndef TSP_ALGORITHM_H
#define TSP_ALGORITHM_H

#include "TSP_Shared.h"

class TSP_Algorithm
{
public:
    TSP_Algorithm();
    virtual void NextIteration();
    virtual void Reset();
    virtual int GetIteration();
    virtual float GetFitness();
    virtual vectorint GetBestWay() = 0;
    virtual void SetArray(vectorCity Array);
    virtual float GetLength(City a, City b);

protected:
    vectorCity  m_Array;
    vectorint   m_Way;

    float       m_fFitness;
    int         m_iIteration;
    int         m_iSize;
    bool        m_bShow;
};

#endif // TSP_ALGORITHM_H
