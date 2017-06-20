#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QtWidgets>
#include "figure.h"

class Rectangle : public Figure2D
{
public:
    Rectangle();

    void Draw(QGraphicsView *view) const;
    bool AddPoint(const QPoint& help_point);
    bool Move(const QPoint& new_key_point);
    //bool includesPoint(const QPoint& point);

protected:
    bool have_key_;
    //QPoint help_point;
    //int radius;
};

#endif // RECTANGLE_H
