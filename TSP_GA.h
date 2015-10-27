// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Genetic Algorithm
//
// =============================================================================
#ifndef TSP_GA_H
#define TSP_GA_H

#include "tsp_algorithm.h"

struct ga_struct
{
    vectorint way;
    float fitness;
};
typedef std::vector<ga_struct> ga_vector;

class TSP_GA : public TSP_Algorithm
{
public:
    TSP_GA(TSP_Map* Map, int iPopsize = 0, float fElitrate = 0, float fMutation = 0, float fSupmutation = 0);
    virtual void Reset();
    virtual vectorint GetBestWay();

private:
    int         m_iPopulationSize;
    float       m_fElitRate;
    float       m_fMutationRate;
    float       m_fMutationSupRate;
    ga_vector   m_Population;
    ga_vector   m_Buffer;
};

#endif // TSP_GA_H
