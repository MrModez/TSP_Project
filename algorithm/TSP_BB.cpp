// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Branch and Bound Algorithm
//
// =============================================================================
#include "TSP_BB.h"

TSP_BB::TSP_BB() : TSP_Algorithm()
{

}

void TSP_BB::Reset()
{
}

vectorint TSP_BB::GetBestWay()
{
    return m_Way;
}

float TSP_BB::GetBestFitness()
{
    return m_fFitness;
}
