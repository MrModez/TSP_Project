// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Branch and Bound Algorithm
//
// =============================================================================
#include "tsp_bb.h"

TSP_BB::TSP_BB(TSP_Map *Map) : TSP_Algorithm(Map)
{

}

void TSP_BB::Reset()
{
}

vectorint TSP_BB::GetBestWay()
{
    return m_Way;
}
