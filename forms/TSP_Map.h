// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Map
//
// =============================================================================
#ifndef TSP_MAP_H
#define TSP_MAP_H

#include "TSP_Shared.h"
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
    int GetCityID(float x, float y, int r = 10);
    City GetCity(int ID);
    City GetCityFromWay(int ID);

    float Length(City a, City b);
    void Recount(int a);

    int GetIteration();
    int GetFitness();
    vectorCity GetArray();
    vectorint GetWay();
    vectorint GetRightWay();
    std::vector<vectorfloat> GetMatrix();
    int GetBest();
    float GetMatrix(int i, int j);
    bool CheckEqual(vectorint Way);

    void SetIteration(int iteration);
    void SetFitness(int fitness);
    void SetArray(vectorCity array);
    void SetRightWay(vectorint rightway);
    void SetBest(int best);
    void SetArrayX(int i, float X);
    void SetArrayY(int i, float Y);
    void Clear();

public slots:
    void addCity(float newX, float newY);
    void moveCity(int ID, float newX, float newY);
    void removeCity(int ID);
    void SetWay(vectorint way);
    void UpdateInfo(vectorint way, float fit, int id);

signals:
    void Update();

protected:
    int m_iIteration;
    int m_iFitness;
    int m_iBest;
    bool m_bShow;

    std::vector<vectorfloat>m_fMatrix;
    vectorCity m_Array;
    vectorint m_iWay;
    vectorint m_iRightWay;
};

#endif // TSP_MAP_H
