// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Genetic Algorithm
//
// =============================================================================
#include "TSP_GA.h"
#include "TSP_Map.h"

TSP_GA::TSP_GA(TSP_Map *Map) : TSP_Algorithm(Map)
{
    m_bStop = false;
    QObject::connect(this, SIGNAL(updateWay(vectorint)),
                     m_pMap, SLOT(SetWay(vectorint)));
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


void TSP_GA::SetSettings(int iPopsize, float fElitrate, float fMutation, float fSupmutation)
{
    m_iPopulationSize = iPopsize;
    m_fElitRate = fElitrate;
    m_fMutationRate = fMutation;
    m_fMutationSupRate = fSupmutation;
}

void TSP_GA::run()
{
    qDebug("GA RUN");
    for (int i = 0; i < 100000; i++)
    {
        m_Mutex.lock();
        if (this->m_bStop) break;
        m_Mutex.unlock();

        qDebug("GA WORKS %i", i);
        NextIteration();
        CalcFitness();
        SortByFitness();
        qDebug("FIT %f", m_Population[0].fitness);
        vectorint best = GetBestWay();
        QString str = "";
        for (auto &i : best)
        {
            str += QString::number(i) + " ";
        }
        QByteArray bstr = str.toLatin1();
        qDebug( "%s", bstr.data() );
        //vectorint qwe = GetBestWay();
        emit updateWay(GetBestWay());
        m_pMap->SetWay(best);
        ///
        Mate();
        Swap();
    }
}

void TSP_GA::StartAlgorithm()
{
    qDebug("StartGA");
    Reset();
    InitPopulation();
    m_bStop = false;
    start();
}

void TSP_GA::StopAlgorithm()
{
    qDebug("StopGA");
    m_bStop = true;
}


///Algorithm
void TSP_GA::InitPopulation()
{
    for (int i = 0; i < m_iPopulationSize; i++)
    {
        ga_struct citizen;
        int begin = 0;
        int end = 0;

        citizen.fitness = 0;
        for (int j = 0; j < m_pMap->Size(); j++)
        {
            if (j != begin && j != end)
            {
                citizen.way.push_back(j);
            }
        }
        random_shuffle(citizen.way.begin(), citizen.way.end());
        citizen.way.insert(citizen.way.begin(), begin);
        citizen.way.insert(citizen.way.end(), end);

        m_Population.push_back(citizen);
    }

    m_Buffer.resize(m_iPopulationSize);
}


void TSP_GA::CalcFitness()
{
    float m_fFitness;

    for (int i = 0; i < m_iPopulationSize; i++)
    {
        m_fFitness = 0.0;
        for (int j = 0; j < m_pMap->Size() - 1; j++)
        {
            m_fFitness += m_pMap->Length(m_pMap->GetCity(m_Population[i].way[j]),
                                         m_pMap->GetCity(m_Population[i].way[j + 1]));
        }
        m_fFitness += m_pMap->Length(m_pMap->GetCity(m_Population[i].way[m_pMap->Size() - 1]),
                                     m_pMap->GetCity(m_Population[i].way[m_pMap->Size()]));
        m_Population[i].fitness = m_fFitness;
    }
}


void TSP_GA::SortByFitness()
{
    std::sort(m_Population.begin(), m_Population.end(),
              [](ga_struct a, ga_struct b) {return a.fitness < b.fitness;});
}

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
        len += m_pMap->Length(m_pMap->GetArray()[way[pos1]], m_pMap->GetArray()[way[pos2]]);
    return len;
}

void TSP_GA::Mutate(ga_struct &member)
{
    int times = rand() % m_pMap->Size();

    for (int i = 0; i < times; i++)
    {
        int pos1 = rand() % m_pMap->Size();
        int pos2 = rand() % m_pMap->Size();
        if (pos1 == 0)
            pos1 += 1;
        if (pos1 == m_pMap->Size() - 1)
            pos1 -= 1;
        if (pos2 == 0)
            pos2 += 1;
        if (pos2 == m_pMap->Size() - 1)
            pos2 -= 1;
        int temp = member.way[pos1];
        member.way[pos1] = member.way[pos2];
        member.way[pos2] = temp;
    }
}

void TSP_GA::SupMutate(ga_struct &member)
{
    int pos1 = rand() % m_pMap->Size();
    int pos2 = rand() % m_pMap->Size();

    if (pos1 == 0)
        pos1 += 1;
    if (pos1 == m_pMap->Size() - 1)
        pos1 -= 1;
    if (pos2 == 0)
        pos2 += 1;
    if (pos2 == m_pMap->Size() - 1)
        pos2 -= 1;
    if (pos1 > pos2)
    {
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    if (pos1 != pos2)
    {
        reverse(member.way.begin() + pos1, member.way.begin() + pos2);
    }
}

void TSP_GA::Mate()
{
    int esize = m_iPopulationSize * m_fElitRate;
    int pos1 = -1, pos2 = -1, i1, i2;
    Elitism(esize);

    // Mate the rest
    for (int i = esize; i < m_iPopulationSize; i++)
    {
        i1 = rand() % (int)(m_iPopulationSize * m_fElitRate);
        i2 = rand() % (m_iPopulationSize);

        pos1 = rand() % m_pMap->Size();
        pos2 = rand() % m_pMap->Size();
        if (pos1 > pos2)
        {
            int temp = pos1;
            pos1 = pos2;
            pos2 = temp;
        }
        m_Buffer[i].way.clear();
        std::vector<int>num;
        for (int j = 0; j < m_pMap->Size(); j++)
        {
            num.push_back(j);
        }

        for (int j = 1; j < m_pMap->Size() - 1; j++)
        {
            for (int k = j + 1; k < m_pMap->Size() - 1; k++)
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
                    m_Buffer[i].way.push_back(m_Population[i2].way[j]);
                    num[m_Population[i2].way[j]] = -1;
                }
            };
            for (int j = pos1; j < pos2; j++)
            {
                m_Buffer[i].way.push_back(m_Population[i1].way[j]);
            }
            for (int j = pos1; j < m_pMap->Size(); j++)
            {
                if (num[m_Population[i2].way[j]] != -1)
                {
                    m_Buffer[i].way.push_back(m_Population[i2].way[j]);
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
                    m_Buffer[i].way.push_back(m_Population[i1].way[j]);
                    num[m_Population[i1].way[j]] = -1;
                }
            };
            for (int j = pos1; j < pos2; j++)
            {
                m_Buffer[i].way.push_back(m_Population[i2].way[j]);
            }
            for (int j = pos1; j < m_pMap->Size(); j++)
            {
                if (num[m_Population[i1].way[j]] != -1)
                {
                    m_Buffer[i].way.push_back(m_Population[i1].way[j]);
                    num[m_Population[i1].way[j]] = -1;
                }
            };
        }
        m_Buffer[i].way.push_back(0);

        if (rand() < m_fMutationSupRate)
        {
            SupMutate(m_Buffer[i]);
        }
        if (rand() < m_fMutationRate)
        {
            Mutate(m_Buffer[i]);
        }
    }
}

void TSP_GA::Swap()
{
    m_Population = m_Buffer;
}
