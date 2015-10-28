// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Branch and Bound Algorithm
//
// =============================================================================
#ifndef TSP_BB_H
#define TSP_BB_H

#include "TSP_Algorithm.h"

class TSP_BB : public TSP_Algorithm
{
public:
    TSP_BB(TSP_Map* Map);
    virtual void Reset();
    virtual vectorint GetBestWay();

private:
};

#endif // TSP_BB_H
