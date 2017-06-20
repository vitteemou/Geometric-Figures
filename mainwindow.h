#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "figure.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::MainWindow *ui;
    void CreatePanelLayout();
    void CreatePanelItems();
    void CreateGroupBox(const QString& name, const QVector<QWidget*>& buttons, QGroupBox** box);
    void SetFigure(Figure *figure);
    int checkFigures(const QPoint& point);
    void CheckButtons(QPushButton* checked_button);
    void UncheckButtons();

    QPushButton* segment_button_;
    QPushButton* ray_button_;
    QPushButton* line_button_;
    QGroupBox* one_d_box_;

    QPushButton* polygon_button_;
    QPushButton* ellipse_button_;
    QPushButton* rectangle_button_;
    QGroupBox* two_d_box_;

    QPushButton* clear_button_;
    QGroupBox* manager_box_;

    QPushButton* border_color_button_;
    QPushButton* backet_color_button_;
    QGroupBox* color_box_;

    QSlider* pen_width_slider_;
    QGroupBox* pen_width_box_;

    QGroupBox* buttons_box_;

    QGraphicsView* graphics_area_;

    //QVector<Figure*> figures_;
    QVector<QPushButton*> figure_buttons_;

    Figure* figure_ = nullptr;
    QPoint key_figure_point;
    QPoint second_figure_point;
    bool has_figure = false;
    bool has_poly_figure = false;

 public slots:
    void ProcessAreaClick(QMouseEvent* event);

    void ClearArea();
    void Redraw();
    void ChooseBorderColor();
    void ChooseBacketColor();
    void SetPenWidth();

    void ProcessPolygonPush();
    void ProcessSegmentPush();
    void ProcessRayPush();
    //void ProcessLinePush();
    void ProcessEllipsePush();
    void ProcessRectanglePush();
};

#endif // MAINWINDOW_H
