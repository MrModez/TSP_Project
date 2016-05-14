// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Branch and Bound Algorithm
//
// =============================================================================
#ifndef TSP_BB_H
#define TSP_BB_H

#include "TSP_Algorithm.h"

class BB_Info
{
public:
    BB_Info(int _nn)
        : nn(_nn)
    {
        Popt.resize(nn);
        Pt.resize(nn);
        nsq1.resize(nn);
        nsq2.resize(nn);
        Pq.resize(nn);
        Smin = 999999;
        col = 0;
    }

    ~BB_Info()
    {
    }

    int col;
    float Smin;
    int nn;
    std::vector<int> Popt;
    std::vector<int> Pt;
    std::vector<int> nsq1, nsq2, Pq;
};

class TSPM
{
public:
    TSPM(int nt, BB_Info *_info);     /*создание нового узла в начале списка*/
    ~TSPM();    /*уничтожение узла в начале списка*/
    void Mzero1();       /*вычитание минимальных элементов из строк и столбцов*/
    void Mzero2();       /*дополнительное преобразование матрицы с увеличением S0*/
    void Copy(TSPM*& r); /*копирование содержимого узла (одинакового размера)*/
    void Mcase(); /*выбор наилучшего очередного ребра для маршрута и создание пред. узла*/

    TSPM *pl,*pr;      /*указатели на предыдущий и последующий узлы дерева решений*/
    int n;
    float S0, Sm; /*текущий размер матрицы, сумма вычтенных из матрицы*/
                            /*элементов, более точная оценка снизу для маршрута: S0<=Sm*/
    typedef std::vector<float> TSPMATR2__0;
    std::vector<TSPMATR2__0> MR;    /*текущая матрица в узле*/
    int simm;    /*признак симметричности матрицы*/
    std::vector<int> ns1, ns2; /*начала и концы для каждого отрезка маршрута*/
    std::vector<int> mj1, mj2; /*номера столбцов с 0, номера столбцов с 2 мин. эл.*/
    std::vector<int> mi1, mi2; /*номера строк с 0, номера строк с 2 мин. эл.*/

    BB_Info *info;
};


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
    float Length(City a, City b);

protected:
    TSPM *pb;
    BB_Info *info;

    int m_iIteration;
    float m_fFitness;
    std::vector<int>Way;
};

#endif // TSP_BB_H
