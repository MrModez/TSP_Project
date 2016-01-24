// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Map
//
// =============================================================================
#include "TSP_Map.h"

TSP_Map::TSP_Map() : QObject()
{
    m_iBest = INT_MAX;
    m_bShow = false;
    m_Array.clear();
    m_iWay.clear();
    m_iRightWay.clear();
    m_fMatrix.clear();
}

int TSP_Map::Size()
{
    return (int)m_Array.size();
}

void TSP_Map::Add(City cnew)
{
    m_Array.push_back(cnew);
    MatrixResize((int)m_Array.size());
}

void TSP_Map::Erase()
{
    for (auto i : m_fMatrix)
    {
        i.clear();
    }
    m_fMatrix.clear();
    m_Array.clear();
}

void TSP_Map::Del(int a)
{
    m_Array.erase(m_Array.begin() + a);
    for (auto i = a; i < m_Array.size(); i++)
    {
        for (auto j = 0; j < m_Array.size(); j++)
        {
            m_fMatrix[i][j] = m_fMatrix[i + 1][j + 1];
        }
    }
    MatrixResize((int)m_Array.size());
}

void TSP_Map::MatrixResize(int size)
{
    m_fMatrix.resize(size);
    for (auto i = 0; i < size; i++)
    {
        m_fMatrix[i].resize(size);
    }
}

float TSP_Map::Length(City a, City b)
{
    return (float)sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

int TSP_Map::GetCityID(int x, int y, int r /*= 10*/)
{
    for (auto i = 0; i < GetArray().size(); i++)
    {
        if (x < m_Array[i].x + r && x > m_Array[i].x - r
         && y < m_Array[i].y + r && y > m_Array[i].y - r)
        {
            return i;
        }
    }
    return -1;
}

TPoint TSP_Map::GetCity(int ID)
{
    return m_Array[ID];
}

TPoint TSP_Map::GetCityFromWay(int ID)
{
    return m_Array[m_iWay[ID]];
}

void TSP_Map::Recount(int a)
{
    for (auto i = 0; i < m_Array.size(); i++)
    {
        if (i != a)
        {
            float len = Length(m_Array[i], m_Array[a]);
            m_fMatrix[i][a] = len;
            m_fMatrix[a][i] = len;
        }
    }
}

//
int TSP_Map::GetIteration()
{
    return m_iIteration;
}

int TSP_Map::GetFitness()
{
    return m_iFitness;
}

vectorCity TSP_Map::GetArray()
{
    return m_Array;
}

vectorint TSP_Map::GetWay()
{
    return m_iWay;
}

vectorint TSP_Map::GetRightWay()
{
    return m_iRightWay;
}

std::vector<vectorfloat> TSP_Map::GetMatrix()
{
    return m_fMatrix;
}

int TSP_Map::GetBest()
{
    return m_iBest;
}

float TSP_Map::GetMatrix(int i, int j)
{
    return m_fMatrix[i][j];
}

bool TSP_Map::CheckEqual(vectorint SWay)
{
    if (m_iRightWay == SWay)
        return true;
    std::reverse(SWay.begin(), SWay.end());
    if (m_iRightWay == SWay)
        return true;
    return false;
};


//algorythm stuff
void TSP_Map::SetIteration(int iteration)
{
    m_iIteration = iteration;
}

void TSP_Map::SetFitness(int fitness)
{
    m_iFitness = fitness;
}

void TSP_Map::SetArray(vectorCity array)
{
    m_Array = array;
}

void TSP_Map::SetWay(vectorint way)
{
    qDebug( "TSP_Map::SetWay" );
    m_iWay = way;
    emit Update();
}

void TSP_Map::SetRightWay(vectorint rightway)
{
    m_iRightWay = rightway;
}

void TSP_Map::SetBest(int ibest)
{
    m_iBest = ibest;
}

void TSP_Map::SetArrayX(int i, int X)
{
    m_Array[i].x = (float)X;
}

void TSP_Map::SetArrayY(int i, int Y)
{
    m_Array[i].y = (float)Y;
}

void TSP_Map::Clear()
{
    for (auto i = 0; i < m_Array.size(); i++)
    {
        for (auto j = 0; j < m_Array.size(); j++)
        {
            m_fMatrix[i][j] = 0.0;
        }
    }
    m_iBest = INT_MAX;
    m_bShow = false;
    m_Array.clear();
    m_iWay.clear();
    m_iRightWay.clear();
}

//Signals/Slots stuff
void TSP_Map::addCity(int newX, int newY)
{
    qDebug( "TSP_Map::addCity %i %i", newX, newY );
    TPoint city(newX, newY);
    Add(city);
    Recount(Size() - 1);
}

void TSP_Map::moveCity(int ID, int newX, int newY)
{
    SetArrayX(ID, newX);
    SetArrayY(ID, newY);
    Recount(ID);

    for (auto &i : m_fMatrix)
    {
        QString str = "";
        for (auto &j : i)
        {
            str += QString::number((int)j) + " ";
        }
        QByteArray bstr = str.toLatin1();
        qDebug( "%s", bstr.data() );
    }
    qDebug( "" );
}

void TSP_Map::removeCity(int ID)
{
    qDebug( "TSP_Map::removeCity %i", ID );
    Del(ID);
}
