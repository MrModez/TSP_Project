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

struct TSP_Result
{
    //TSP_Result() : vec(_vec), fit(_fit), id(_id) {}
    TSP_Result() {}
    TSP_Result( std::vector<int> _vec, float _fit, int _id) : vec(_vec), fit(_fit), id(_id) {}
    std::vector<int> vec;
    float fit;
    int id;
};

double sqr(double a);

typedef TPoint              City;
typedef std::vector<int>    vectorint;
typedef std::vector<float>  vectorfloat;
typedef std::vector<City>   vectorCity;

#endif // TSP_SHARED_H
