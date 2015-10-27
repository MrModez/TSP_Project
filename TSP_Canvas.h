// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Canvas
//
// =============================================================================
#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class TSP_Map;

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = 0, TSP_Map *map = 0);
    virtual ~Canvas();
    void setBackgroundColor(QColor val);
    void setMap(TSP_Map *map);

protected:
    void paintEvent(QPaintEvent *event) override;
    bool event(QEvent *event) override;

signals:
    void addCity(int newX, int newY);
    void moveCity(int ID, int newX, int newY);
    void removeCity(int ID);

private:
    TSP_Map* m_pMap;
    int      m_ID;
};

#endif // CANVAS_H
