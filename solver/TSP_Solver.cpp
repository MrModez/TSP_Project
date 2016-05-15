// ===== Copyright © 2015-2016, MrModez (Zagir Fabarisov), Flatag (Tagir Fabarisov), All rights reserved. =====
//
// Purpose: Base Solver class
// Назначение: Базовый класс для решателя
//
// ============================================================================================================
#include "TSP_Solver.h"
#include "TSP_Map.h"
#include "TSP_Algorithm.h"

TSP_Solver::TSP_Solver(TSP_Algorithm *pAlgorithm, TSP_Map *pMap)
{
    m_pAlgorithm = pAlgorithm;
    m_pMap = pMap;
    m_bStop = false;
    m_bPaused = false;
}

TSP_Solver::~TSP_Solver()
{
   delete m_pAlgorithm;
}

void TSP_Solver::Execute()
{

}

void TSP_Solver::StartAlgorithm()
{
    m_bStop = false;
    Execute();
}

void TSP_Solver::StopAlgorithm()
{
    m_bStop = true;
}

void TSP_Solver::PauseAlgorithm()
{
    m_bPaused = true;
}

void TSP_Solver::ContinueAlgorithm()
{
    m_bPaused = false;
}


bool TSP_Solver::IsWorking()
{
    return (!m_bStop);
}
