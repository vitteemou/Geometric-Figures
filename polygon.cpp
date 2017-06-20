#include <QtWidgets>
#include "polygon.h"

Polygon::Polygon()
{
}

void Polygon::Draw(QGraphicsView *view) const {
    QGraphicsScene* scene = view->scene();
    QPen pen(border_color_, pen_width_);
    QBrush brush(backet_color_);
    //QPoint diff = key_point_ - help_point_;
    //int r = sqrt(pow(diff.x(), 2) + pow(diff.y(), 2));
    //SetRadius(r);
    //scene->addEllipse(key_point_.x() - r, key_point_.y() - r, 2*r, 2*r, pen, brush);

    QPolygonF polygon;
    polygon.append(poly_points);
    //QPolygonF* polygon = new QPolygonF(points);
    scene->addPolygon(polygon, pen, brush);
}

bool Polygon::AddPoint(const QPoint& point) {
    if(poly_points.length() > 4){
        points.clear();
        have_key_ = false;
        return true;
    }
    if (have_key_) {
        poly_points.append(point);
        //have_key_ = false;
        return true;
    } else {
        points[0] = point;
        poly_points.clear();
        poly_points.append(points[0]);
        have_key_ = true;
        return false;
    }
}

bool Polygon::Move(const QPoint& new_key_point){
   return true;
}

/*bool Polygon::includesPoint(const QPoint& point){
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


