// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Genetic Algorithm
//
// =============================================================================
#include "TSP_GA.h"
#include "TSP_Map.h"

TSP_GA::TSP_GA() : TSP_Algorithm()
{
}

void TSP_GA::Reset()
{
    m_Way.clear();
    m_Population.clear();
    m_Buffer.clear();
}

vectorint TSP_GA::GetBestWay()
{
    return m_Population[0].way;
}

float TSP_GA::GetBestFitness()
{
    return m_Population[0].fitness;
}

void TSP_GA::SetSettings(int iPopsize, float fElitrate, float fMutation, float fSupmutation)
{
    m_iPopulationSize = iPopsize;
    m_fElitRate = fElitrate;
    m_fMutationRate = fMutation;
    m_fMutationSupRate = fSupmutation;
}

///Algorithm
void TSP_GA::InitPopulation()
{
    for (int i = 0; i < m_iPopulationSize; i++)
    {
        ga_struct citizen;

        citizen.fitness = 0;
        for (int j = 1; j < m_iSize; j++)
        {
            citizen.way.push_back(j);
        }
        random_shuffle(citizen.way.begin(), citizen.way.end());
        citizen.way.insert(citizen.way.begin(), 0);
        citizen.way.insert(citizen.way.end(), 0);

        m_Population.push_back(citizen);
    }

    m_Buffer.resize(m_iPopulationSize);
}


void TSP_GA::CalcFitness()
{
    for (int i = 0; i < m_iPopulationSize; i++)
    {
        float m_fFitness = 0.0f;
        for (int j = 0; j < m_iSize; j++)
        {
            int a1 = m_Population[i].way[j];
            int a2 = m_Population[i].way[j + 1];
            m_fFitness += GetLength(m_Array[a1], m_Array[a2]);
        }
        m_Population[i].fitness = m_fFitness;
    }
}


void TSP_GA::SortByFitness()
{
    std::sort(m_Population.begin(), m_Population.end(),
              [](ga_struct a, ga_struct b) {return a.fitness < b.fitness;});
}

void TSP_GA::Elitism(int esize)
{
    for (int i = 0; i < esize; i++)
    {
        m_Buffer[i].way = m_Population[i].way;
        m_Buffer[i].fitness = m_Population[i].fitness;
    }
}


double TSP_GA::WayLength(std::vector<int>way, int pos1, int pos2)
{
    if (pos1 > pos2)
    {
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    int len = 0;
    for (int i = pos1; i < pos2; i++)
        len += GetLength(m_Array[way[pos1]], m_Array[way[pos2]]);
    return len;
}

void TSP_GA::Mutate(ga_struct &member)
{
    int pos1 = rand() % (m_iSize - 2) + 1;
    int pos2 = rand() % (m_iSize - 2) + 1;
    int temp = member.way[pos1];
    member.way[pos1] = member.way[pos2];
    member.way[pos2] = temp;
}

void TSP_GA::Mutate_move(ga_struct &member)
{
    int pos1 = rand() % (m_iSize - 2) + 1;
    int pos2 = rand() % (m_iSize - 2) + 1;
    int temp = member.way[pos1];
    member.way.erase(member.way.begin()+pos1);
    member.way.insert(member.way.begin()+pos2, temp);
    //member.way[pos1] = member.way[pos2];
    //member.way[pos2] = temp;
}

void TSP_GA::SupMutate(ga_struct &member)
{
    int pos1 = rand() % (m_iSize - 2) + 1;
    int pos2 = rand() % (m_iSize - 2) + 1;
    if (pos1 > pos2)
    {
        std::swap(pos1, pos2);
    }
    if (pos1 != pos2)
    {
        std::reverse(member.way.begin() + pos1, member.way.begin() + pos2);
    }
}

void TSP_GA::Mate()
{
    int esize = m_iPopulationSize * m_fElitRate;
    Elitism(esize);

    std::vector<ga_struct> omp_Buffer = m_Buffer;
    //omp_Buffer.
    //omp_Buffer.resize(m_Buffer.size());
   // for (int i = 0; i < m_Buffer.size(); i++)
    //    omp_Buffer[i] = m_Buffer[i];

    // Mate the rest
#pragma omp parallel for shared(omp_Buffer)
    for (int i = esize; i < m_iPopulationSize; i++)
    {
        //qDebug("%i", omp_get_thread_num());
        int pos1 = -1, pos2 = -1, i1, i2;

        int elit = (m_iPopulationSize * m_fElitRate);
        i1 = rand() % elit;//(int)(m_iPopulationSize / 2.0);
        i2 = (rand() % (m_iPopulationSize - elit)) + elit;

        pos1 = rand() % m_iSize;
        pos2 = rand() % m_iSize;
        if (pos1 > pos2)
        {
            std::swap(pos1, pos2);
        }

        omp_Buffer[i].way.clear();
        std::vector<int>num;
        for (int j = 0; j < m_iSize; j++)
        {
            num.push_back(j);
        }

        for (int j = 1; j < m_iSize - 1; j++)
        {
            for (int k = j + 1; k < m_iSize - 1; k++)
            {
                if (m_Population[i1].way[j] == m_Population[i2].way[j]
                 && m_Population[i1].way[k] == m_Population[i2].way[k])
                {
                    pos1 = j, pos2 = k;
                }
            }
        }

        if (WayLength(m_Population[i1].way, pos1, pos2) <
            WayLength(m_Population[i2].way, pos1, pos2))
        {
            for (int j = pos1; j < pos2; j++)
            {
                num[m_Population[i1].way[j]] = -1;
            };
            for (int j = 0; j < pos1; j++)
            {
                if (num[m_Population[i2].way[j]] != -1)
                {
                    omp_Buffer[i].way.push_back(m_Population[i2].way[j]);
                    num[m_Population[i2].way[j]] = -1;
                }
            };
            for (int j = pos1; j < pos2; j++)
            {
                omp_Buffer[i].way.push_back(m_Population[i1].way[j]);
            }
            for (int j = pos1; j < m_iSize; j++)
            {
                if (num[m_Population[i2].way[j]] != -1)
                {
                    omp_Buffer[i].way.push_back(m_Population[i2].way[j]);
                    num[m_Population[i2].way[j]] = -1;
                }
            };
        }
        else {
            for (int j = pos1; j < pos2; j++)
            {
                num[m_Population[i2].way[j]] = -1;
            };
            for (int j = 0; j < pos1; j++)
            {
                if (num[m_Population[i1].way[j]] != -1)
                {
                    omp_Buffer[i].way.push_back(m_Population[i1].way[j]);
                    num[m_Population[i1].way[j]] = -1;
                }
            };
            for (int j = pos1; j < pos2; j++)
            {
                omp_Buffer[i].way.push_back(m_Population[i2].way[j]);
            }
            for (int j = pos1; j < m_iSize; j++)
            {
                if (num[m_Population[i1].way[j]] != -1)
                {
                    omp_Buffer[i].way.push_back(m_Population[i1].way[j]);
                    num[m_Population[i1].way[j]] = -1;
                }
            };
        }
        omp_Buffer[i].way.push_back(0);

        float rnd = rand() / (float)RAND_MAX;

        if (rnd < m_fMutationRate)
        {
            Mutate(omp_Buffer[i]);
        }
        /*
        else if (rand() < m_fMutationRate)
        {
            Mutate_move(omp_Buffer[i]);
        }
        */
        else if (rnd < m_fMutationSupRate)
        {
            SupMutate(omp_Buffer[i]);
        }

    }

   // for (int i = 0; i < m_Buffer.size(); i++)
    //    m_Buffer[i] = omp_Buffer[i];
    m_Buffer = omp_Buffer;
}

void TSP_GA::Swap()
{
    m_Population = m_Buffer;
}


/*
QString TSP_GA::PrintBest()
{
    ga_struct gav = m_Population[0];
    m_fFitness = gav.fitness;
    QString Line = "[GA] " + QString::number(m_iIteration) + " - " +
                             QString::number((int)gav.fitness) + ": ";
    for (unsigned int i = 0; i < gav.way.size(); i++)
    {
        Line = Line + QString::number((int)gav.way[i] + 1) + " ";
    }
    return Line;
}
*/
