// ====== Copyright © 2015, MrModez (Zagir Fabarisov), All rights reserved. ====
//
// Purpose: Canvas
//
// =============================================================================
#include "TSP_Canvas.h"
#include "TSP_Map.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

TSP_Canvas::TSP_Canvas(QWidget *parent, TSP_Map *map) : QWidget(parent)
{
    setBackgroundColor(Qt::white);
    setMap(map);
    m_ID = -1;
}

TSP_Canvas::~TSP_Canvas()
{
}

void TSP_Canvas::setMap(TSP_Map *map)
{
    m_pMap = map;
}

void TSP_Canvas::setBackgroundColor(QColor val)
{
    QPalette Pal;
    Pal.setColor(QPalette::Background, val);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

void TSP_Canvas::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);
    QPen pen(QColor(0, 0, 0, 20));
    QBrush brush(QColor(125, 255, 255, 255));
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
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
    for (auto i = 0; i < m_pMap->GetArray().size(); i++)
    {
        auto city = m_pMap->GetArray()[i];
        int x = city.x;
        int y = city.y;
        int r = 15;
        painter->drawEllipse(x - r , y - r, r * 2, r * 2);
        painter->drawText(x - r, y - r, QString::number(i));
    }
    delete painter;
}

bool TSP_Canvas::event(QEvent *event)
{
    if (event->type() == QEvent::Paint)
    {
        QPaintEvent *pPaintEvent = reinterpret_cast<QPaintEvent *>(event);
        paintEvent(pPaintEvent);
        return true;
    }

    if (event->type() == QEvent::KeyPress)
    {
        //qDebug("KeyPress");
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *pMouseEvent = reinterpret_cast<QMouseEvent *>(event);
        int x = pMouseEvent->x();
        int y = pMouseEvent->y();
        int ID = m_pMap->GetCityID(x, y, 15);

        if (pMouseEvent->button() == Qt::LeftButton)
        {
            if (ID != -1)
            {
                m_ID = ID;
            }
            else
            {
                emit addCity(x, y);
            }
        }
        else if (pMouseEvent->button() == Qt::RightButton)
        {
            if (ID != -1)
            {
                emit removeCity(ID);
            }
        }
    }
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *pMouseEvent = reinterpret_cast<QMouseEvent *>(event);
        int x = pMouseEvent->x();
        int y = pMouseEvent->y();
        if (m_ID != -1)
        {
            emit moveCity(m_ID, x, y);
        }
    }
    if (event->type() == QEvent::MouseButtonRelease)
    {
        m_ID = -1;
    }
    repaint();
    return true;
}