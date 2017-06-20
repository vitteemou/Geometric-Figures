#include "segment.h"

Segment::Segment(const QPoint& key_point, const QPoint& help_point) :
    Figure1D(key_point){

    points[1] = help_point;
    QPointF diff = points[1] - points[0];
    length = sqrt(pow(diff.x(), 2) + pow(diff.y(), 2));
}

bool Segment::AddPoint(const QPoint& point) {
    /*if (have_key_) {
        help_point_ = point;
        have_key_ = false;
        return true;
    } else {
        key_point_ = point;
        have_key_ = true;
        return false;
    }*/
    if (have_key_) {
        points[1] = point;
        return true;
    } else {
        points[0] = point;
        have_key_ = true;
        return false;
    }

}

void Segment::Draw(QGraphicsView* view) const {
    QPointF key_point_ = points[0];
    QPointF help_point_ = points[1];

    QLineF line(key_point_, help_point_);
    QPen pen(border_color_, pen_width_);
    view->scene()->addLine(line, pen);
}

QPointF Ray::GetFarawayPoint(const QPointF& start, const QPointF& finish) const {
    int x_dist = abs(finish.x() - start.x());
    int y_dist = abs(finish.y() - start.y());
    int min_dist = x_dist < y_dist ? x_dist : y_dist;
    int width = QApplication::desktop()->geometry().width();
    const int big_number = width / min_dist + 1;
    int new_x = start.x() + big_number*(finish.x() - start.x());
    int new_y = start.y() + big_number*(finish.y() - start.y());
    return QPoint(new_x, new_y);
}

bool Ray::AddPoint(const QPoint& point) {
    bool result = Segment::AddPoint(point);
    //if (result) {
        points[2] = points[1];
        points[1] = GetFarawayPoint(points[0], points[1]);
    //}
    return true;//result;
}

/*bool Line::AddPoint(const QPoint &point) {
    //bool result = Ray::AddPoint(point);
    //if (result) {
        points[0] = GetFarawayPoint(points[2], points[0]);
    //}
    return true;//result;
}*/

bool Ray::Move(const QPoint& new_key_point){
    QPointF diff = points[0] - points[1];
    points[0] = new_key_point;
    points[1] = points[0] - diff;
    return true;
}

/*bool Line::Move(const QPoint& new_key_point){
    QPointF diff = points[0] - points[1];
    points[0] = new_key_point;
    points[1] = points[0] - diff;
    return true;
}*/

bool Segment::Move(const QPoint& new_key_point){
    QPointF diff = points[0] - points[1];
    points[0] = new_key_point;
    points[1] = points[0] - diff;
    return true;
}
