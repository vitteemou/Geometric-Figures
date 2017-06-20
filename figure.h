#ifndef FIGURE_H
#define FIGURE_H

#include <QtWidgets>

class Figure {
public:
    Figure(): points(3), border_color_() {}
    explicit Figure(const QPoint& key_point) :
        points(3), border_color_() { points[0] = key_point; }
    virtual void Draw(QGraphicsView* view) const = 0;
    virtual bool AddPoint(const QPoint& point) = 0;
    virtual bool Move(const QPoint& new_key_point) = 0;
    //virtual bool includesPoint(const QPoint& point) = 0;

    QPointF Location() const { return points[0]; }
    QColor BorderColor() const { return border_color_; }

    virtual void SetBorderColor(const QColor& border_color)
                        { border_color_ = border_color; }
    virtual QColor GetBorderColor() const { return border_color_; }
    virtual void SetPenWidth(int pen_width) { pen_width_ = pen_width; }
    virtual int GetPenWidth() const { return pen_width_; }

    virtual ~Figure() {}
protected:
    //QPoint key_point_;
    //QPoint help_point_;
    QVector<QPointF> points;
    QColor border_color_ = Qt::black;
    int pen_width_ = 1;
};

class Figure1D : public Figure {
public:
    using Figure::Figure;

    virtual void Draw(QGraphicsView* view) const = 0;
    virtual bool AddPoint(const QPoint& point) = 0;
    virtual bool Move(const QPoint& new_key_point) = 0;
    //virtual bool includesPoint(const QPoint& point) = 0;

protected:
    double length;

};

class Figure2D : public Figure {
public:
    using Figure::Figure;

    virtual void Draw(QGraphicsView *view) const = 0;
    virtual bool AddPoint(const QPoint &point) = 0;
    virtual bool Move(const QPoint& new_key_point) = 0;
    //virtual bool includesPoint(const QPoint& point) = 0;

    virtual void SetBacketColor(const QColor& backet_color)
                                { backet_color_ = backet_color; }
    virtual QColor GetBacketColor() const { return backet_color_; }

protected:
    QColor backet_color_ = Qt::yellow;
};

#endif // FIGURE_H
