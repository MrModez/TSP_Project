// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Branch and Bound Algorithm
//
// =============================================================================
#include "TSP_BB.h"
#include "math.h"

TSP_BB::TSP_BB() : TSP_Algorithm()
{

}

void TSP_BB::SetArray(vectorCity Array)
{
    TSP_Algorithm::SetArray(Array);

    m_iSize = m_Array.size();

    m_fMatrix.resize(m_iSize);
    for (int i = 0; i < m_iSize; i++) {
        m_fMatrix[i].resize(m_iSize);
    }

    for (auto a = 0; a < m_iSize; a++)
    {
        for (auto i = 0; i < m_iSize; i++)
        {
            if (i != a)
            {
                float len = Length(m_Array[i], m_Array[a]);
                m_fMatrix[i][a] = len;
                m_fMatrix[a][i] = len;
            }
        }
    }
}

void TSP_BB::Start() {
    Recursiv(flag, cur_path, cur_length, 1);
}

float TSP_BB::Length(City a, City b)
{
    return (float)sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

void TSP_BB::Reset()
{
    m_iIteration = 0;
        min_path.clear();
        sel_city.clear();
        citymatrix.clear();
        cur_path.clear();

        int count = 0;
        sel_city.resize(m_iSize);
        for (int i = 0; i < m_iSize; i++)
            sel_city[count++] = i;

        citymatrix.resize(m_iSize);
        for (int i = 0; i < m_iSize; i++) {
            citymatrix[i].resize(m_iSize);
        }

        for (int i = 0; i < m_iSize; i++) {
            for (int j = 0; j < m_iSize; j++) {
                citymatrix[i][j] = m_fMatrix[sel_city[j]][sel_city[i]];
                //citymatrix[i][j] = TSP->GetMatrix(sel_city[j], sel_city[i]);
            }
        }

        // заполнение признаков посещения городов
        flag.resize(m_iSize + 1);
        flag[0] = true;
        for (int i = 1; i < m_iSize; i++)
            flag[i] = false;

        cur_path.resize(m_iSize + 1);
        min_path.resize(m_iSize + 1);
        Way.resize(m_iSize + 1);

        // заполнение матриц минимального пути и текущего пути
        min_path[0] = 1;
        min_path[m_iSize] = 1;
        min_length = 0;
        for (int i = 1; i < m_iSize; i++) {
            min_path[i] = i + 1;
            min_length += citymatrix[i - 1][i];
            cur_path[i] = 0;
        }
        min_length += citymatrix[min_path[m_iSize - 1] - 1][min_path[m_iSize] - 1];
        cur_length = 0;
        cur_path[0] = cur_path[m_iSize] = 1;
}

void TSP_BB::Recursiv(std::vector<bool>flag, std::vector<int>cur_path, float cur_length, int j) {
    int n = m_Array.size();
    for (int i = 0; i < n; i++) {
        // для каждой точки
        if (flag[i] == false) {
            // где мы еще не были
            flag[i] = true;
            // переходим в нее,
            cur_path[j] = i + 1;
            // вычисляя длину пройденного пути
            cur_length += citymatrix[cur_path[j - 1] - 1][cur_path[j] - 1];
            if (cur_length < min_length) {
                if (j < n - 1)
                    Recursiv(flag, cur_path, cur_length, j + 1);
                else {
                    // или вычисляем длинув сего пути и ...
                    cur_length +=
                        citymatrix[cur_path[n - 1] - 1][cur_path[n] - 1];
                    // ...  сравниваем с минимальным
                    if (cur_length < min_length) {
                        m_iIteration++;
                        for (int k = 0; k <= n; k++) {
                            min_path[k] = cur_path[k];
                            if (k < n)
                                Way[k] = min_path[k] - 1;
                        }
                        min_length = cur_length;
                    }
                    cur_length -=
                        citymatrix[cur_path[n - 1] - 1][cur_path[n] - 1];
                }
            }
            flag[i] = false;
            cur_length -= citymatrix[cur_path[j - 1] - 1][cur_path[j] - 1];
        }
    }
    return;
}

vectorint TSP_BB::GetBestWay()
{
    return Way;
}

float TSP_BB::GetBestFitness()
{
    return min_length;
}
