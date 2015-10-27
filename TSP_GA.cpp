// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Genetic Algorithm
//
// =============================================================================
#include "tsp_ga.h"

TSP_GA::TSP_GA(TSP_Map *Map, int iPopsize, float fElitrate, float fMutation, float fSupmutation)
    : TSP_Algorithm(Map)
{
    m_iPopulationSize = iPopsize;
    m_fElitRate = fElitrate;
    m_fMutationRate = fMutation;
    m_fMutationSupRate = fSupmutation;
}

void TSP_GA::Reset()
{
    m_Way.clear();
    m_Population.clear();
    m_Buffer.clear();
}

vectorint TSP_GA::GetBestWay()
{
    return m_Population[0].way;
}
