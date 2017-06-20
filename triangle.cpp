#include <QtWidgets>
#include "triangle.h"

Triangle::Triangle()
{

}

void Triangle::Draw(QGraphicsView *view) const {
    QGraphicsScene* scene = view->scene();
    QPen pen(border_color_, pen_width_);
    QBrush brush(backet_color_);
    //QPoint diff = key_point_ - help_point_;
    //int r = sqrt(pow(diff.x(), 2) + pow(diff.y(), 2));
    //SetRadius(r);
    //scene->addEllipse(key_point_.x() - r, key_point_.y() - r, 2*r, 2*r, pen, brush);
    scene->addPolygon()
}

bool Triangle::AddPoint(const QPoint& point) {
    if (have_key_) {
        help_point_ = point;
        have_key_ = false;
        return true;
    } else {
        key_point_ = point;
        have_key_ = true;
        return false;
    }
}

/*bool Triangle::Move(const QPoint& new_key_point){
    key_point_ = new_key_point;
    help_point_.setX(key_point_.x() - radius);
    help_point_.setY(key_point_.y() - radius);
    have_key_ = true;

    return true;
}

bool Triangle::includesPoint(const QPoint& point){
    int rect_x0 = key_point_.x() - radius;
    int rect_y0 = key_point_.y() - radius;
    int rect_x1 = key_point_.x() + radius;
    int rect_y1 = key_point_.x() + radius;

    if((point.x() >= rect_x0 && point.x() <= rect_x1 && point.y() >= rect_y0 && point.y() <= rect_y1)){
        return true;
    }
    else{
        return false;
    }
}*/

