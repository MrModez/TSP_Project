// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Shared stuff
//
// =============================================================================
#ifndef TSP_SHARED_H
#define TSP_SHARED_H

#define vectorint			std::vector<int>
#define vectorcity			std::vector<City>

double sqr(double a);

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
typedef TPoint City;

#endif // TSP_SHARED_H
