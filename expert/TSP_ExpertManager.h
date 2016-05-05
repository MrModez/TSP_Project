#ifndef TSP_EXPERTMANAGER_H
#define TSP_EXPERTMANAGER_H

#include <QObject>
#include <QPointer>
#include <QVector>
#include <QThread>
#include "TSP_Shared.h"

class TSP_Solver;
class TSP_Map;

class TSP_ExpertManager : public QObject
{
    Q_OBJECT
public:
    explicit TSP_ExpertManager(QObject *parent = 0);
    ~TSP_ExpertManager();
    void Init(QVector<float>args);
    void InitSolver(int ID);

signals:

public slots:
    void UpdateInfo(vectorint vec, float fit, int id);
    void Finished();

private:
    int m_iSize;
    int m_iCities;
    int m_iTries;
    QVector<TSP_Solver*>    m_pSolvers;
    QVector<QThread*>       m_pSolverThreads;
    QVector<int>            m_Tries;
    QVector<TSP_Map*>       m_pMaps;
};

#endif // TSP_EXPERTMANAGER_H
