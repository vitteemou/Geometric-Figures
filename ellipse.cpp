#include <QtWidgets>
#include "ellipse.h"

Ellipse::Ellipse()
{

}
void Ellipse::Draw(QGraphicsView *view) const {
    QGraphicsScene* scene = view->scene();
    QPen pen(border_color_, pen_width_);
    QBrush brush(backet_color_);

    QPointF key_point_ = points[0];
    QPointF diff = points[0] - points[1];
    int r = sqrt(pow(diff.x(), 2) + pow(diff.y(), 2));
    scene->addEllipse(key_point_.x() - r, key_point_.y() - r, 2*r, 2*r, pen, brush);
}

bool Ellipse::AddPoint(const QPoint& point) {
    if (have_key_) {
        points[1] = point;
        return true;
    } else {
        points[0] = point;
        have_key_ = true;
        return false;
    }
}

bool Ellipse::Move(const QPoint& new_key_point){
    QPointF diff = points[0] - points[1];
    points[0] = new_key_point;
    points[1] = points[0] - diff;
    return true;
}

