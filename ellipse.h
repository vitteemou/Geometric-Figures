#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QtWidgets>

#include "figure.h"

class Ellipse : public Figure2D
{
public:
    Ellipse();

    void Draw(QGraphicsView *view) const;
    bool AddPoint(const QPoint& help_point);
    bool Move(const QPoint& new_key_point);
    int radius();
    //bool includesPoint(const QPoint& point);

protected:
    bool have_key_ = false;
    //QPoint help_point_;
    //int radius;
};

#endif // ELLIPSE_H
