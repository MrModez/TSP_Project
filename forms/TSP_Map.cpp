// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Map
//
// =============================================================================
#include "TSP_Map.h"

TSP_Map::TSP_Map() : QObject()
{
    m_iBestFitness = INT_MAX;
    m_bShow = false;
    m_Array.clear();
    m_iWay.clear();
    m_iBestWay.clear();
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
    for (size_t i = a; i < m_Array.size(); i++)
    {
        for (size_t j = 0; j < m_Array.size(); j++)
        {
            m_fMatrix[i][j] = m_fMatrix[i + 1][j + 1];
        }
    }
    MatrixResize((int)m_Array.size());
    emit MatrixUpdated();
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

int TSP_Map::GetCityID(float x, float y, int r /*= 10*/)
{
    for (size_t i = 0; i < GetArray().size(); i++)
    {
        if (x < m_Array[i].x + r && x > m_Array[i].x - r
         && y < m_Array[i].y + r && y > m_Array[i].y - r)
        {
            return i;
        }
    }
    return -1;
}

City TSP_Map::GetCity(int ID)
{
    return m_Array[ID];
}

City TSP_Map::GetCityFromWay(std::vector<int>Way, int ID)
{
    return m_Array[Way[ID]];
}

void TSP_Map::Recount(size_t a)
{
    for (size_t i = 0; i < m_Array.size(); i++)
    {
        if (i != a)
        {
            float len = Length(m_Array[i], m_Array[a]);
            m_fMatrix[i][a] = len;
            m_fMatrix[a][i] = len;
        }
    }
    emit MatrixUpdated();
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

vectorint TSP_Map::GetBestWay()
{
    return m_iBestWay;
}

std::vector<vectorfloat> TSP_Map::GetMatrix()
{
    return m_fMatrix;
}

int TSP_Map::GetBestFitness()
{
    return m_iBestFitness;
}

float TSP_Map::GetMatrix(int i, int j)
{
    return m_fMatrix[i][j];
}

bool TSP_Map::CheckEqual(vectorint SWay)
{
    if (m_iBestWay == SWay)
        return true;
    std::reverse(SWay.begin(), SWay.end());
    if (m_iBestWay == SWay)
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
    //qDebug( "TSP_Map::SetWay" );
    m_iWay = way;
    emit WayUpdated();
}

void TSP_Map::UpdateInfo(TSP_Result result)
{
    SetFitness(result.fit);
    SetIteration(result.id);
    SetWay(result.vec);
    if (result.fit < GetBestFitness())
        SetBest(result.vec, result.fit);
}

void TSP_Map::SetBest(vectorint way, float fit)
{
    m_iBestFitness = fit;
    m_iBestWay = way;
}

void TSP_Map::SetArrayX(int i, float X)
{
    m_Array[i].x = (float)X;
}

void TSP_Map::SetArrayY(int i, float Y)
{
    m_Array[i].y = (float)Y;
}

void TSP_Map::Clear()
{
    for (size_t i = 0; i < m_Array.size(); i++)
    {
        for (size_t j = 0; j < m_Array.size(); j++)
        {
            m_fMatrix[i][j] = 0.0;
        }
    }
    m_iBestFitness = INT_MAX;
    m_bShow = false;
    m_Array.clear();
    m_iWay.clear();
    m_iBestWay.clear();
}

void TSP_Map::ClearBest()
{
    m_iBestFitness = INT_MAX;
    m_iBestWay.clear();
}

void TSP_Map::GenerateRandom(int size)
{
    for (int i = 0; i < size; i++)
    {
        int rand_x = qrand() % 750 + 50;
        int rand_y = qrand() % 400 + 20;
        addCity(rand_x, rand_y);
    }
}

//Signals/Slots stuff
void TSP_Map::addCity(float newX, float newY)
{
    //qDebug( "TSP_Map::addCity %i %i", newX, newY );
    TPoint city(newX, newY);
    Add(city);
    Recount(Size() - 1);
    ClearBest();
}

void TSP_Map::moveCity(int ID, float newX, float newY)
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
        //qDebug( "%s", bstr.data() );
    }
    ClearBest();
    //qDebug( "" );
}

void TSP_Map::removeCity(int ID)
{
    //qDebug( "TSP_Map::removeCity %i", ID );
    Del(ID);
    ClearBest();
}
