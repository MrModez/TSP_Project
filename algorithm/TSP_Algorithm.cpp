// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Base TSP algorithm
//
// =============================================================================
#include "TSP_Algorithm.h"
#include "math.h"

TSP_Algorithm::TSP_Algorithm()
{
    m_iIteration = 0;
    m_iSize = 0;
    m_fFitness = 0.0f;
    m_Way.clear();
}

TSP_Algorithm::~TSP_Algorithm()
{

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

void TSP_Algorithm::SetArray(vectorCity Array)
{
    m_Array = Array;
    m_iSize = (int)Array.size();
}

float TSP_Algorithm::GetLength(City &a, City &b)
{
    return (float)sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));    
}
