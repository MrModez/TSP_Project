// ===== Copyright © 2015-2016, MrModez (Zagir Fabarisov), Flatag (Tagir Fabarisov), All rights reserved. =====
//
// Purpose: Branch and Bound Algorithm
// Назначение: Метод ветвей и границ
//
// ============================================================================================================
#include "TSP_BB.h"
#include "math.h"

TSPM::TSPM(int nt , BB_Info *_info)
  : pl(nullptr),
    pr(nullptr),
    n(0),
    S0(0),
    Sm(0),
    simm(0),
    info(_info)
{
    int n1 = 0;
    n1 = nt + 1;
    n = nt;
    ns1.resize(n1);
    ns2.resize(n1);
    mj1.resize(n1);
    mj2.resize(n1);
    mi1.resize(n1);
    mi2.resize(n1);
    MR.resize(n1);
    for (auto &mr : MR)
        mr.resize(n1);
}

TSPM::~TSPM( )
{
    ns1.clear();
    ns2.clear();
    mj1.clear();
    mj2.clear();
    mi1.clear();
    mi2.clear();
    MR.clear();
}

void TSPM::Copy(TSPM*& r)
{
    S0 = r->S0;
    Sm = r->Sm;
    for (int j = 1; j <= n; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            MR[j][i] = r->MR[j][i];
        }
        ns1[j] = r->ns1[j];
        ns2[j] = r->ns2[j];
    }
}

void TSPM::Mzero1()
{
    float k = 0, Sq = 0; /*--------------------------------------------*/
    //col = col + 1;
    for (int j = 1; j <= n; j++)     /*По строкам - вычитание мин.*/
    {
        k = 1;
        for (int i = 2; i <= n; i++)
            if (MR[j][k] > MR[j][i])
                k = i;
        Sq = MR[j][k];
        S0 = S0 + Sq;
        mj1[j] = k;
        for (int i = 1; i <= n; i++)
            MR[j][i] = MR[j][i] - Sq;
    } /*-------------------------------------------*/
    for (int i = 1; i <= n; i++)    /*По столбцам - вычитание мин.*/
    {
        k = 1;
        for (int j = 2; j <= n; j++)
            if (MR[k][i] > MR[j][i])
                k = j;
        Sq = MR[k][ i];
        S0 = S0 + Sq;
        mi1[i] = k;
        for (int j = 1; j <= n; j++)
            MR[j][i] = MR[j][i] - Sq;
    } /*-------------------------------------------*/
    Sm = S0;
}  /*---------------------------------------------*/



void TSPM::Mzero2()
{
    float a = 0, b = 0, d = 0, q = 0; /*-------------------по строкам-------*/
    float Sq = 0, k = 0, k2 = 0;
    for (int j = 1; j <= n; j++) /*По строкам 2-й мин.*/
    {
        if (mj1[j] == 1)
            k = 2;
        else
            k = 1;
        for (int i = 2; i <= mj1[j] - 1; i++)
            if (MR[j][k] > MR[j][i])
                k = i;
        for (int i = mj1[j] + 1; i <= n; i++)
            if (MR[j][k] > MR[j][i])
                k = i;
        mj2[j] = k;
    }
    k2 = 1;
    while (k2 == 1)
    {
        k2 = 0;
        for (int i = 1; i <= n; i++)
            info->nsq1[i] = 0; /*номера проверенных строк с одним 0*/
        int i = 1;
        while (i <= n)
        {
            while ((i <= n) && ((MR[i][mj2[i]] == 0) || (info->nsq1[i] == 1)))
                i = i + 1;
            if (i < n)
            {
                k = mj1[i];
                q = 1;
                info->Pq[1] = i;
                d = MR[i][mj2[i]];
                info->nsq1[i] = 1;
                for (int j = 1; j <= n; j++)
                    info->nsq2[j] = 0; /*номера группы строк с одним 0*/
                info->nsq2[i] = 1;
                int j = i + 1;
                while (j <= n)
                {
                    if ((mj1[j] == k) && (MR[j][mj2[j]] > 0) && (info->nsq1[j] == 0))
                    {
                        q = q + 1;
                        info->Pq[q] = j;
                        info->nsq1[j] = 1;
                        info->nsq2[j] = 1;
                        if (d > MR[j][mj2[j]])
                            d = MR[j][mj2[j]];
                    }
                    j = j + 1;
                }
                if (q > 1)
                { /*---вычитание из строк d----*/
                    k2 = 1;
                    S0 = S0 + (q - 1) * d;
                    for (int j = 1; j <= q; j++)
                    {
                        int ii = info->Pq[j];
                        for (int jj = 1; jj <= n; jj++)
                            if (jj != k)
                            {
                                MR[ii][jj] = MR[ii][jj] - d;
                                if (MR[ii][jj] == 0)
                                    mj2[ii] = jj;
                            }
                    }
                    for (int j = 1; j <= n; j++)
                        if (info->nsq2[j] == 0)
                        {
                            MR[j][k] = MR[j][k] + d;
                            if ((mj1[j] == k) || (mj2[j] == k))
                            { /*коррекция*/
                                a = 1;
                                b = 2;
                                if (MR[j][1] > MR[j][2])
                                {
                                    a = 2;
                                    b = 1;
                                }
                                for (int jj = 3; jj <= n; jj++)
                                    if (MR[j][jj] < MR[j][a])
                                    {
                                        b = a;
                                        a = jj;
                                    }
                                    else if (MR[j][jj] < MR[j][b])
                                        b = jj;
                                mj1[j] = a;
                                mj2[j] = b;
                            }
                        }
                }
            }
            i = i + 1;
        }
    }
    /*------------------------------------------------*/
    for (int i = 1; i <= n; i++) /*По столбцам - вычитание мин.*/
    {
        k = 1;
        k2 = 2;
        if (MR[k][i] > MR[k2][i])
        {
            k = 2;
            k2 = 1;
        }
        for (int j = 3; j <= n; j++)
            if (MR[k][i] > MR[j][i])
            {
                k2 = k;
                k = j;
            }
            else if (MR[k2][i] > MR[j][i])
                k2 = j;
        Sq = MR[k][i];
        S0 = S0 + Sq;
        mi1[i] = k;
        mi2[i] = k2;
        for (int j = 1; j <= n; j++)
            MR[j][i] = MR[j][i] - Sq;
    } /*-------------------------------------------*/
    /*------------Конец--- по строкам---------------*/
    /*------------Начало----------по столбцам-------*/
    k2 = 1;
    while (k2 == 1)
    {
        k2 = 0;
        for (int i = 1; i <= n; i++)
            info->nsq1[i] = 0; /*номера проверенных столбцов с одним 0*/
        int i = 1;
        while (i <= n)
        {
            while ((i <= n) && ((MR[mi2[i]][i] == 0) || (info->nsq1[i] == 1)))
                i = i + 1;
            if (i < n)
            {
                k = mi1[i];
                q = 1;
                info->Pq[1] = i;
                d = MR[mi2[i]][i];
                info->nsq1[i] = 1;
                for (int j = 1; j <= n; j++)
                    info->nsq2[j] = 0; /*номера группы столбцов с одним 0*/
                info->nsq2[i] = 1;
                int j = i + 1;
                while (j <= n)
                {
                    if ((mi1[j] == k) && (MR[mi2[j]][j] > 0) && (info->nsq1[j] == 0))
                    {
                        q = q + 1;
                        info->Pq[q] = j;
                        info->nsq1[j] = 1;
                        info->nsq2[j] = 1;
                        if (d > MR[mi2[j]][j])
                            d = MR[mi2[j]][j];
                    }
                    j = j + 1;
                }
                if (q > 1)
                { /*---вычитание из столбцов d----*/
                    k2 = 1;
                    S0 = S0 + (q - 1) * d;
                    for (int j = 1; j <= q; j++)
                    {
                        int ii = info->Pq[j];
                        for (int jj = 1; jj <= n; jj++)
                            if (jj != k)
                            {
                                MR[jj][ii] = MR[jj][ii] - d;
                                if (MR[jj][ii] == 0)
                                    mi2[ii] = jj;
                            }
                    }
                    for (int j = 1; j <= n; j++)
                        if (info->nsq2[j] == 0)
                        {
                            MR[k][j] = MR[k][j] + d;
                            if ((mi1[j] == k) || (mi2[j] == k))
                            { /*коррекция*/
                                a = 1;
                                b = 2;
                                if (MR[1][j] > MR[2][j])
                                {
                                    a = 2;
                                    b = 1;
                                }
                                for (int jj = 3; jj <= n; jj++)
                                    if (MR[jj][j] < MR[a][j])
                                    {
                                        b = a;
                                        a = jj;
                                    }
                                    else if (MR[jj][j] < MR[b][j])
                                        b = jj;
                                mi1[j] = a;
                                mi2[j] = b;
                            }
                        }
                }
            }
            i = i + 1;
        }
    }
    /*------------------------------------------------*/
    for (int i = 1; i <= n; i++) /*По строкам - вычитание мин.*/
    {
        k = 1;
        k2 = 2;
        if (MR[i][k] > MR[i][k2])
        {
            k = 2;
            k2 = 1;
        }
        for (int j = 3; j <= n; j++)
            if (MR[i][k] > MR[i][j])
            {
                k2 = k;
                k = j;
            }
            else if (MR[i][k2] > MR[i][j])
                k2 = j;
        Sq = MR[i][k];
        S0 = S0 + Sq;
        mj1[i] = k;
        mj2[i] = k2;
        for (int j = 1; j <= n; j++)
            MR[i][j] = MR[i][j] - Sq;
    } /*-------------------------------------------*/
    for (int i = 1; i <= n; i++) /*По столбцам 2-й мин.*/
    {
        if (mi1[i] == 1)
            k = 2;
        else
            k = 1;
        for (int j = 2; j <= mi1[i] - 1; j++)
            if (MR[k][i] > MR[j][i])
                k = j;
        for (int j = mi1[i] + 1; j <= n; j++)
            if (MR[k][i] > MR[j][i])
                k = j;
        mi2[i] = k;
    }
    /*------------Конец----------------------------*/
    if (Sm < S0)
        Sm = S0;
} /*---------------------------------------------*/


void TSPM::Mcase()
{
    float a = 0, b = 0, a2 = 0, b2 = 0;
    float d = 0, s1 = 0, s2 = 0, s3 = 0;
    float l1 = 0; /*---------------------------------------------*/
    a = 1;
    b = mj1[1];
    s1 = MR[1][mj2[1]]; /*Выбор ребра по максимуму*/
    s3 = MR[mi2[b]][b];
    for (int i = 2; i <= n; i++)
    {
        b2 = mj1[i];
        s2 = MR[i][mj2[i]];
        if (s1 < s2)
        {
            a = i;
            b = mj1[a];
            s1 = s2;
            s3 = MR[mi2[b2]][b2];
        }
    }
    for (int j = 1; j <= n; j++)
    {
        a2 = mi1[j];
        s2 = MR[mi2[j]][j];
        if (s1 < s2)
        {
            b = j;
            a = mi1[b];
            s1 = s2;
            s3 = MR[a2][mj2[a2]];
        }
    }
    d = s1 + s3;
    if (MR[b][a] == 0)
        l1 = MR[b][mj2[b]] + MR[mi2[a]][a];
    else
        l1 = 0;
    info->Pt[ns2[a]] = ns1[b];
    /*========================================  Новая матрица n-1   ==========*/
    if (a < b)
    {
        for (int j = 1; j <= a - 1; j++)
        {
            int ii = 0;
            for (int i = 1; i <= n; i++)
                if (i != a)
                {
                    ii = ii + 1;
                    pl->MR[ii][j] = MR[i][j];
                }
        }
        int ii = 0;
        for (int i = 1; i <= n; i++)
            if (i != a)
            {
                ii = ii + 1;
                pl->MR[ii][b - 1] = MR[i][a];
                pl->ns1[ii] = ns1[i];
                pl->ns2[ii] = ns2[i];
            }
        for (int j = a + 1; j <= b - 1; j++)
        {
            int ii = 0;
            for (int i = 1; i <= n; i++)
                if (i != a)
                {
                    ii = ii + 1;
                    pl->MR[ii][j - 1] = MR[i][j];
                }
        }
        for (int j = b + 1; j <= n; j++)
        {
            int ii = 0;
            for (int i = 1; i <= n; i++)
                if (i != a)
                {
                    ii = ii + 1;
                    pl->MR[ii][j - 1] = MR[i][j];
                }
        }
        pl->MR[b - 1][b - 1] = 50000;
        pl->ns1[b - 1] = ns1[a];
    }
    else
    {
        for (int j = 1; j <= b - 1; j++)
        {
            int ii = 0;
            for (int i = 1; i <= n; i++)
                if (i != a)
                {
                    ii = ii + 1;
                    pl->MR[ii][j] = MR[i][j];
                }
        }
        int ii = 0;
        for (int i = 1; i <= n; i++)
            if (i != a)
            {
                ii = ii + 1;
                pl->MR[ii][b] = MR[i][a];
                pl->ns1[ii] = ns1[i];
                pl->ns2[ii] = ns2[i];
            }
        for (int j = b + 1; j <= a - 1; j++)
        {
            int ii = 0;
            for (int i = 1; i <= n; i++)
                if (i != a)
                {
                    ii = ii + 1;
                    pl->MR[ii][j] = MR[i][j];
                }
        }
        for (int j = a + 1; j <= n; j++)
        {
            int ii = 0;
            for (int i = 1; i <= n; i++)
                if (i != a)
                {
                    ii = ii + 1;
                    pl->MR[ii][j - 1] = MR[i][j];
                }
        }
        pl->MR[b][b] = 50000;
        pl->ns1[b] = ns1[a];
    }
    pl->simm = 0;
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    if (n == 4)
    { /*Если новая матрица стала 3х3*/
        s1 = pl->MR[1][2] + pl->MR[2][3] + pl->MR[3][1];
        s2 = pl->MR[1][3] + pl->MR[3][2] + pl->MR[2][1];
        if ((S0 + s1 < info->Smin) || (S0 + s2 < info->Smin))
        {
            if (s1 <= s2)
            {
                info->Pt[pl->ns2[1]] = pl->ns1[2];
                info->Pt[pl->ns2[2]] = pl->ns1[3];
                info->Pt[pl->ns2[3]] = pl->ns1[1];
                info->Smin = S0 + s1;
            }
            else
            {
                info->Pt[pl->ns2[1]] = pl->ns1[3];
                info->Pt[pl->ns2[3]] = pl->ns1[2];
                info->Pt[pl->ns2[2]] = pl->ns1[1];
                info->Smin = S0 + s2;
            }
            for (int i = 1; i <= info->nn; i++)
                info->Popt[i] = info->Pt[i];
        }
        pl->Sm = 999999; /*В будущем удаление  матрицы 3х3*/
    }
    else
    { /*Если матрица больше чем 3х3*/
        pl->S0 = S0;
        pl->Sm = S0 + l1;
    }
    MR[a][b] = 50000;
    Sm = S0 + d; /*Коррекция старой матрицы*/
    if (simm == 1)
    { /*Если матрица симметрична*/
        if (MR[b][a] == 0)
            Sm = Sm + MR[b][mj2[b]] + MR[mi2[a]][a];
        MR[b][a] = 50000;
    }
}


//////
////
///
TSP_BB::TSP_BB() : TSP_Algorithm()
{

}

TSP_BB::~TSP_BB()
{
    delete info;

}

void TSP_BB::SetArray(vectorCity Array)
{
    TSP_Algorithm::SetArray(Array);

    int nn = Array.size();
    info = new BB_Info(nn);
    pb = new TSPM(nn, info);
    pb->pr = nullptr;

    for (auto j = 1; j <= nn; j++)
    {
        for (auto i = 1; i <= nn; i++)
        {
            if (i != j)
            {
                float len = Length(m_Array[i-1], m_Array[j-1]);
                pb->MR[i][j] = len;
                pb->MR[j][i] = len;
            }
            else
            {
                pb->MR[i][i] = 999999;
            }
        }
    }
    pb->S0 = 0;
    pb->Sm = 0;
    for (int i = 1; i <= nn; i++)
    {
        pb->ns1[i] = i;
        pb->ns2[i] = i;
        info->Pt[i] = 0;
    }
    pb->simm = 1;
    int i = 2; /*проверка на симметричность матрицы*/
    while (i <= nn)
    {
        int j = 1;
        while (j < i)
        {
            if (pb->MR[i][j] != pb->MR[j][i])
            {
                i = nn + 1;
                j = i;
                pb->simm = 0;
            }
            j = j + 1;
        }
        i = i + 1;
    }
}

void TSP_BB::Start() {
    if (!pb)
        return;

    TSPM *p1 = pb;
    TSPM *p2;
    for (int i = info->nn - 1; i >= 3; i--)
    {
        TSPM *p2 = new TSPM(i, info);
        p2->pr = p1;
        p1->pl = p2;
        p1 = p2;
    }
    p1->pl = nullptr;
    p1 = pb;
    while (p1 != nullptr)
    {
        if (p1->Sm < info->Smin)
            p1->Mzero1();
        if (p1->Sm < info->Smin)
            p1->Mzero2();
        if (p1->Sm < info->Smin)
            p1->Mcase();
        p2 = p1->pl;
        if (p2->Sm < info->Smin)
            p1 = p2;
        else if (p1->Sm >= info->Smin)
            p1 = p1->pr;
    }
    p1 = pb;
    while (p1 != nullptr)
    {
        p2 = p1->pl;
        delete p1;
        p1 = p2;
    }

    ///
    Way.clear();
    int i = 1;
    for (int j = 1; j <= info->nn; j++)
    {
      Way.push_back(i-1);
      i = info->Popt[i];
    }
    Way.push_back(0);

    m_fFitness = info->Smin;
    m_fFitness += Length(m_Array[i-1], m_Array[0]);
}

float TSP_BB::Length(City a, City b)
{
    return (float)sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

void TSP_BB::Reset()
{
}

vectorint TSP_BB::GetBestWay()
{
    return Way;
}

float TSP_BB::GetBestFitness()
{
    return m_fFitness;
}
