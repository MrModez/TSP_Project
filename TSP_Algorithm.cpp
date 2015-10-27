// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Base TSP algorithm
//
// =============================================================================
#include "tsp_algorithm.h"

TSP_Algorithm::TSP_Algorithm(TSP_Map* Map) : QObject()
{
    m_pMap = Map;
    m_iIteration = 0;
    m_fFitness = 0.0f;
    m_Way.clear();
}

void TSP_Algorithm::NextIteration()
{
    m_iIteration++;
}

void TSP_Algorithm::Reset()
{
    m_iIteration = 0;
    m_fFitness = 0;
}

int TSP_Algorithm::GetIteration()
{
    return m_iIteration;
}

float TSP_Algorithm::GetFitness()
{
    return m_fFitness;
}
