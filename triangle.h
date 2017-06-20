#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QtWidgets>
#include "figure.h"

class Triangle : public Figure2D
{
public:
    Triangle();

    void Draw(QGraphicsView *view) const;
    bool AddPoint(const QPoint& help_point);
    //bool Move(const QPoint& new_key_point);
    //bool includesPoint(const QPoint& point);

protected:
    bool have_key_;
    QPoint help_point_1;
    QPoint help_point_2;
    //int radius;
};

#endif // TRIANGLE_H
