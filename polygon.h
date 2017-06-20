#ifndef POLYGON_H
#define POLYGON_H

#include <QtWidgets>
#include "figure.h"

class Polygon : public Figure2D
{
public:
    Polygon();

    void Draw(QGraphicsView *view) const;
    bool AddPoint(const QPoint& help_point);
    bool Move(const QPoint& new_key_point);
    //bool includesPoint(const QPoint& point);

protected:
    bool have_key_;
    QVector<QPointF> poly_points;
    //QPoint help_point_;
    //int radius;
};

#endif // POLYGON_H
