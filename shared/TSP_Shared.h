// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Shared stuff
//
// =============================================================================
#ifndef TSP_SHARED_H
#define TSP_SHARED_H

#include "vector"
#include "omp.h"

class TPoint
{
public:
    TPoint()
    {

    }

    TPoint(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    float x;
    float y;
};

double sqr(double a);

typedef TPoint              City;
typedef std::vector<int>    vectorint;
typedef std::vector<float>  vectorfloat;
typedef std::vector<City>   vectorCity;

#endif // TSP_SHARED_H
