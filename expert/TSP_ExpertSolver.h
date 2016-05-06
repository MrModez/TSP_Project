#ifndef TSP_EXPERTSOLVER_H
#define TSP_EXPERTSOLVER_H

#include <QObject>
#include <QPointer>
#include <QVector>
#include <QThread>
#include "TSP_Shared.h"

class TSP_Solver;
class TSP_Map;

class TSP_ExpertSolver : public QObject
{
    Q_OBJECT
public:
    explicit TSP_ExpertSolver(int ID, int cities, int tries, QObject *parent = 0);
    //QVector<TSP_Result> GetResults();

signals:
    void finished(float fit, int iter);
    void updateInfo(float fit, int iter);

public slots:
    void StartWorking();
    void Finished(TSP_Result result);
    void UpdateInfo(TSP_Result result);

private:
    int             m_iTries;
    TSP_Map        *m_pMap;
    TSP_Solver     *m_pSolver;
    int             m_ID;
    //QVector<TSP_Result>  m_Results;
};

#endif // TSP_EXPERTSOLVER_H
