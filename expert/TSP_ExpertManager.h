#ifndef TSP_EXPERTMANAGER_H
#define TSP_EXPERTMANAGER_H

#include <QObject>
#include <QPointer>
#include <QVector>
#include <QThread>
#include "TSP_Shared.h"

class TSP_ExpertSolver;
class TSP_Map;

class TSP_ExpertManager : public QObject
{
    Q_OBJECT
public:
    explicit TSP_ExpertManager(QObject *parent = 0);
    ~TSP_ExpertManager();
    void Init(QVector<int>args);
    void InitSolver(int ID);

signals:
    void updateTable(int ID, int iter, float fit);
    void finishedWorking();

public slots:
    void UpdateInfo(float fit, int iter);
    void Finished(float fit, int iter);

private:
    int m_iSize;
    int m_iCities;
    int m_iTries;
    TSP_Map *m_pMap;
    QVector<TSP_ExpertSolver*>  m_pExpertSolvers;
};

#endif // TSP_EXPERTMANAGER_H
