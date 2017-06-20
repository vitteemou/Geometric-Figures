#ifndef SEGMENT_H
#define SEGMENT_H

#include "figure.h"
#include <QtWidgets>

class Segment : public Figure1D
{
public:
    Segment() : Figure1D(){}
    Segment(const QPoint& key_point, const QPoint& help_point);
    bool AddPoint(const QPoint& point);
    void Draw(QGraphicsView* view) const;
    bool Move(const QPoint& new_key_point);

protected:
    //QPoint help_point_;
    bool have_key_ = false;
};

class Ray : public Segment
{
public:
    using Segment::Segment;
    bool AddPoint(const QPoint& point);
    bool Move(const QPoint& new_key_point);

protected:
    QPointF GetFarawayPoint(const QPointF& start, const QPointF& finish) const;
    //QPoint true_help_point_;
};

/*class Line : public Ray {
public:
    using Segment::Segment;
    bool AddPoint(const QPoint& point);
    bool Move(const QPoint& new_key_point);

};*/

#endif // SEGMENT_H
