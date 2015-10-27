// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Base TSP algorithm
//
// =============================================================================
#ifndef TSP_ALGORITHM_H
#define TSP_ALGORITHM_H

#include "tsp_shared.h"
#include <QObject>

class TSP_Algorithm : public QObject
{
    Q_OBJECT

public:
    TSP_Algorithm();
};

#endif // TSP_ALGORITHM_H
