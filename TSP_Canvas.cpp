// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Canvas
//
// =============================================================================
#include "tsp_canvas.h"
#include "tsp_map.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent, TSP_Map *map) : QWidget(parent)
{
    setBackgroundColor(Qt::white);
    setMap(map);
    m_ID = -1;
}

Canvas::~Canvas()
{
}

void Canvas::setMap(TSP_Map *map)
{
    m_pMap = map;
}

void Canvas::setBackgroundColor(QColor val)
{
    QPalette Pal;
    Pal.setColor(QPalette::Background, val);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);

    QPen pen(QColor(0, 0, 0, 20));
    QBrush brush(QColor(125, 255, 255, 255));
    painter->setBrush(brush);
    painter->setPen(pen);

    for (auto city1 : m_pMap->GetArray())
    {
        for (auto city2 : m_pMap->GetArray())
        {
            float x1 = city1.x;
            float x2 = city2.x;
            float y1 = city1.y;
            float y2 = city2.y;
            painter->drawLine(x1, y1, x2, y2);
        }
    }

    pen.setColor(QColor(0, 0, 0, 255));
    pen.setWidth(1);
    painter->setBrush(brush);
    painter->setPen(pen);
    for (auto city : m_pMap->GetArray())
    {
        int x = city.x;
        int y = city.y;
        int r = 15;
        painter->drawEllipse(x - r , y - r, r * 2, r * 2);
        //if (getLineThickness() == 0)
        //    pen.setStyle(Qt::NoPen);
    }
    delete painter;
}

bool Canvas::event(QEvent *event)
{
    if (event->type() == QEvent::Paint)
    {
        QPaintEvent *ke = reinterpret_cast<QPaintEvent *>(event);
        paintEvent(ke);
        //qDebug( "Paint" );
        return true;
    }

    if (event->type() == QEvent::KeyPress)
    {
        qDebug( "KeyPress" );
        // return true;
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        qDebug( "MouseButtonPress" );
        int x = reinterpret_cast<QMouseEvent *>(event)->x();
        int y = reinterpret_cast<QMouseEvent *>(event)->y();
        int ID = m_pMap->GetCityID(x, y, 15);
        if (ID == -1)
        {
            emit addCity(x, y);
        }
        else
        {
            m_ID = ID;
        }
        // return true;
    }
    if (event->type() == QEvent::MouseMove)
    {
        qDebug( "MouseMove" );
        int x = reinterpret_cast<QMouseEvent *>(event)->x();
        int y = reinterpret_cast<QMouseEvent *>(event)->y();
        if (m_ID != -1)
        {
            emit moveCity(m_ID, x, y);
        }
        // return true;
    }
    if (event->type() == QEvent::MouseButtonRelease)
    {
        qDebug( "MouseButtonRelease" );
        m_ID = -1;
       // return true;
    }

    repaint();
    return true;
}
