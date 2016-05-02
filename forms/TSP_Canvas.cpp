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
    m_bDrawBest = false;
    m_bEnabled = true;
    void (QWidget:: *signal)(void) = &QWidget::repaint;
    connect(m_pMap, &TSP_Map::WayUpdated, this, signal);
}

TSP_Canvas::~TSP_Canvas()
{
}

void TSP_Canvas::setMap(TSP_Map *map)
{
    m_pMap = map;
    repaint();
}

void TSP_Canvas::ShowBest(bool state)
{
    m_bDrawBest = state;
    repaint();
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
    QPen pen(QColor(0, 0, 0, 2));
    QBrush brush(QColor(125, 255, 255, 255));
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    for (auto &city1 : m_pMap->GetArray())
    {
        for (auto &city2 : m_pMap->GetArray())
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

    QString str = "Iteration: " + QString::number(m_pMap->GetIteration());
    painter->drawText(QPoint(20, 20), str);
    str = "Fitness: " + QString::number(m_pMap->GetFitness());
    painter->drawText(QPoint(20, 30), str);

    if (!m_pMap->GetBestWay().empty())
    {
        str = "Best: " + QString::number(m_pMap->GetBestFitness());
        painter->drawText(QPoint(20, 40), str);
    }

    if (m_bDrawBest && !m_pMap->GetBestWay().empty())
    {
        pen.setColor(QColor(150, 50, 150, 150));
        painter->setPen(pen);
        for (auto k = 0; k < m_pMap->GetBestWay().size() - 1; k++)
        {
            auto city1 = m_pMap->GetCityFromWay(m_pMap->GetBestWay(), k);
            auto city2 = m_pMap->GetCityFromWay(m_pMap->GetBestWay(), k + 1);
            float x1 = city1.x;
            float x2 = city2.x;
            float y1 = city1.y;
            float y2 = city2.y;
            painter->drawLine(x1, y1, x2, y2);
        }
    }

    if (!m_bDrawBest)
    {
        pen.setColor(QColor(0, 0, 0, 255));
        painter->setPen(pen);
        if (m_pMap->GetWay().size() > 0)
        {
            for (auto k = 0; k < m_pMap->GetWay().size() - 1; k++)
            {
                auto city1 = m_pMap->GetCityFromWay(m_pMap->GetWay(), k);
                auto city2 = m_pMap->GetCityFromWay(m_pMap->GetWay(), k + 1);
                float x1 = city1.x;
                float x2 = city2.x;
                float y1 = city1.y;
                float y2 = city2.y;
                painter->drawLine(x1, y1, x2, y2);
            }
        }
    }

    for (auto i = 0; i < m_pMap->Size(); i++)
    {
        auto city = m_pMap->GetCity(i);
        int x = city.x;
        int y = city.y;
        int r = 5;
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
        if (!m_bEnabled)
            return true;

        QMouseEvent *pMouseEvent = reinterpret_cast<QMouseEvent *>(event);
        int x = pMouseEvent->x();
        int y = pMouseEvent->y();
        int ID = m_pMap->GetCityID(x, y, 10);

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
        if (!m_bEnabled)
            return true;

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
        if (!m_bEnabled)
            return true;

        m_ID = -1;
    }
    repaint();
    return true;
}

void TSP_Canvas::setEnabled(bool state)
{
    m_bEnabled = state;
    this->setCursor(state ? Qt::ArrowCursor : Qt::WaitCursor);
}
