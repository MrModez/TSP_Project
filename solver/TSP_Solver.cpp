// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Solver
//
// =============================================================================
#include "TSP_Solver.h"
#include "TSP_Map.h"
#include "TSP_Algorithm.h"

TSP_Solver::TSP_Solver(TSP_Algorithm *pAlgorithm, TSP_Map *pMap)
{
    m_pAlgorithm = pAlgorithm;
    m_pMap = pMap;
    m_bStop = false;
}

TSP_Solver::~TSP_Solver()
{
   delete m_pAlgorithm;
}

void TSP_Solver::Execute()
{

}
