// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Genetic Algorithm
//
// =============================================================================
#ifndef TSP_GA_H
#define TSP_GA_H

#include "TSP_Algorithm.h"

struct ga_struct
{
    vectorint way;
    float fitness;
};
typedef std::vector<ga_struct> ga_vector;

class TSP_GA : public TSP_Algorithm
{
public:
    TSP_GA();
    ~TSP_GA();

    virtual void Reset();
    virtual vectorint GetBestWay();
    virtual float GetBestFitness();

    void SetSettings(vectorfloat args);
    void InitPopulation();
    void CalcFitness();
    void SortByFitness();
    void Elitism(int esize);
    void Mutate(ga_struct &member);
    void SupMutate(ga_struct &member);
    void Mutate_move(ga_struct &member);
    double WayLength(vectorint &way, int pos1, int pos2);
    void Mate();
    void Swap();

private:
    int         m_iPopulationSize;
    float       m_fElitRate;
    float       m_fMutationRate;
    float       m_fMutationMoveRate;
    float       m_fMutationSupRate;
    ga_vector   m_Population;
    ga_vector   m_Buffer;
};

#endif // TSP_GA_H
