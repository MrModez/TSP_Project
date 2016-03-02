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
    TSP_BB();
    ~TSP_BB();

    virtual void Reset();
    virtual vectorint GetBestWay();
    virtual float GetBestFitness();
    virtual void SetArray(vectorCity Array);
    void Start();
    void Recursiv(std::vector<bool>flag, std::vector<int>cur_path, float cur_length, int j);
    float Length(City a, City b);

    std::vector<int>min_path;
    std::vector<int>sel_city;
    std::vector<int>cur_path;
    std::vector<std::vector<float> >citymatrix;

    float cur_length;
    float min_length;

    std::vector<bool>flag;

    ///
    void SetSize(int Size);
    ///

protected:
    std::vector<vectorfloat>m_fMatrix;
    int m_iIteration;

    std::vector<int>Way;
};

#endif // TSP_BB_H
