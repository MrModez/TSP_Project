// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Map
//
// =============================================================================
#ifndef TSP_MAP_H
#define TSP_MAP_H

#include "tsp_shared.h"
#include <QObject>

class TCANVAS;

class TSP_Map : public QObject
{
   Q_OBJECT

public:
    TSP_Map();

    int Size();
    void Add(City cnew);
    void Erase();
    void Del(int a);
    void MatrixResize(int size);
    int GetCityID(int x, int y, int r = 10);
    City GetCity(int ID);

    float Length(City a, City b);
    void Recount(int a);
    //void Paint(TCANVAS* pCanvas);

    int GetIteration();
    int GetFitness();
    vectorcity GetArray();
    vectorint GetWay();
    vectorint GetRightWay();
    int GetBest();
    float GetMatrix(int i, int j);
    bool CheckEqual(std::vector<int>Way);

    void SetIteration(int iteration);
    void SetFitness(int fitness);
    void SetArray(vectorcity array);
    void SetWay(std::vector<int>way);
    void SetRightWay(std::vector<int>rightway);
    void SetBest(int best);
    void SetArrayX(int i, int X);
    void SetArrayY(int i, int Y);
    void Clear();

public slots:
    void addCity(int newX, int newY);
    void moveCity(int ID, int newX, int newY);
    void removeCity(int ID);

protected:
    int m_iIteration;
    int m_iFitness;
    int m_iBest;
    bool m_bShow;

    std::vector<std::vector<float> >m_fMatrix;
    vectorcity m_Array;
    vectorint m_iWay;
    vectorint m_iRightWay;
};

#endif // TSP_MAP_H
