#include <QtWidgets>
#include "rectangle.h"

Rectangle::Rectangle()
{

}

void Rectangle::Draw(QGraphicsView *view) const {
    QGraphicsScene* scene = view->scene();
    QPen pen(border_color_, pen_width_);
    QBrush brush(backet_color_);

    QPointF key_point_ = points[0];
    QPointF help_point_ = points[1];
    //QPointF diff = points[0] - points[1];
    //int r = sqrt(pow(diff.x(), 2) + pow(diff.y(), 2));
    //scene->addEllipse(key_point_.x() - r, key_point_.y() - r, 2*r, 2*r, pen, brush);

    //QPoint diff = key_point_ - help_point_;
    //int r = sqrt(pow(diff.x(), 2) + pow(diff.y(), 2));
    //SetRadius(r);
    int width = help_point_.x() - key_point_.x();
    int height = help_point_.y() - key_point_.y();
    scene->addRect(key_point_.x(), key_point_.y(), width, height, pen, brush);
    //scene->addEllipse(key_point_.x() - r, key_point_.y() - r, 2*r, 2*r, pen, brush);
}

bool Rectangle::AddPoint(const QPoint& point) {
    if (have_key_) {
        points[1] = point;
        return true;
    } else {
        points[0] = point;
        have_key_ = true;
        return false;
    }
    /*if (have_key_) {
        help_point = point;
        have_key_ = false;
        return true;
    } else {
        key_point_ = point;
        have_key_ = true;
        return false;
    }*/
}

bool Rectangle::Move(const QPoint& new_key_point){
    QPointF diff = points[0] - points[1];
    points[0] = new_key_point;
    points[1] = points[0] - diff;
    return true;
}

/*bool Rectangle::includesPoint(const QPoint& point){
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

