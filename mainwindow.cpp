#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ellipse.h"
#include "polygon.h"
#include "rectangle.h"
#include "segment.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(1800, 1000);
    CreatePanelLayout();

    graphics_area_ = new QGraphicsView(this);
    ClearArea();
    graphics_area_->installEventFilter(this);
    QGridLayout* main_layout = new QGridLayout;
    main_layout->addWidget(graphics_area_, 0, 0);
    main_layout->addWidget(buttons_box_, 0, 1);

    QWidget* window = new QWidget();
    window->setLayout(main_layout);

    setCentralWidget(window);

    setWindowTitle("Graphics");

    connect(segment_button_, SIGNAL(released()), this, SLOT(ProcessSegmentPush()));
    connect(ray_button_, SIGNAL(released()), this, SLOT(ProcessRayPush()));
    //connect(line_button_, SIGNAL(released()), this, SLOT(ProcessLinePush()));
    connect(ellipse_button_, SIGNAL(released()), this, SLOT(ProcessEllipsePush()));
    connect(rectangle_button_, SIGNAL(released()), this, SLOT(ProcessRectanglePush()));
    connect(polygon_button_, SIGNAL(released()), this, SLOT(ProcessPolygonPush()));


    connect(clear_button_, SIGNAL(pressed()), this, SLOT(ClearArea()));
    connect(border_color_button_, SIGNAL(pressed()), this, SLOT(ChooseBorderColor()));
    connect(backet_color_button_, SIGNAL(pressed()), this, SLOT(ChooseBacketColor()));
    connect(pen_width_slider_, SIGNAL(sliderReleased()), this, SLOT(SetPenWidth()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::CreatePanelLayout() {
    CreatePanelItems();
    QVector<QWidget*> one_d_buttons({segment_button_, ray_button_/*, line_button_*/});
    QVector<QWidget*> two_d_buttons({polygon_button_, ellipse_button_, rectangle_button_});
    QVector<QWidget*> manager_buttons({clear_button_});
    QVector<QWidget*> color_buttons({border_color_button_, backet_color_button_});
    QVector<QWidget*> pen_width({pen_width_slider_});

    CreateGroupBox(tr("1D"), one_d_buttons, &one_d_box_);
    CreateGroupBox(tr("2D"), two_d_buttons, &two_d_box_);
    CreateGroupBox(tr("Manager tools"), manager_buttons, &manager_box_);
    CreateGroupBox(tr("Colors"), color_buttons, &color_box_);
    CreateGroupBox(tr("Pen width"), pen_width, &pen_width_box_);

    buttons_box_ = new QGroupBox(tr("Tools"));
    buttons_box_->setAlignment(Qt::AlignHCenter);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(one_d_box_);
    layout->addWidget(two_d_box_);
    layout->addWidget(manager_box_);
    layout->addWidget(color_box_);
    layout->addWidget(pen_width_box_);
    layout->addStretch(1);
    buttons_box_->setLayout(layout);
    buttons_box_->setMaximumWidth(200);

}

void MainWindow::CreateGroupBox(const QString& name, const QVector<QWidget*>& items, QGroupBox** box) {
    *box = new QGroupBox(name);
    (*box)->setAlignment(Qt::AlignHCenter);
    QVBoxLayout* layout = new QVBoxLayout;

    for (auto item : items) {
        layout->addWidget(item);
    }

    (*box)->setLayout(layout);
}

void MainWindow::CreatePanelItems() {
    segment_button_ = new QPushButton("Segment");
    ray_button_ = new QPushButton("Ray");
    //line_button_ = new QPushButton("Line");
    polygon_button_ = new QPushButton("Polygon");
    ellipse_button_ = new QPushButton("Ellipse");
    rectangle_button_ = new QPushButton("Rectangle");
    clear_button_ = new QPushButton("Clear area");

    border_color_button_ = new QPushButton("Border...");
    backet_color_button_ = new QPushButton("Backet...");

    pen_width_slider_ = new QSlider(Qt::Horizontal, this);

    figure_buttons_.clear();
    figure_buttons_.append(segment_button_);
    figure_buttons_.append(ray_button_);
    //figure_buttons_.append(line_button_);
    figure_buttons_.append(polygon_button_);
    figure_buttons_.append(ellipse_button_);
    figure_buttons_.append(rectangle_button_);

    for (QPushButton* button : figure_buttons_) {
        button->setCheckable(true);
    }
}

void MainWindow::SetFigure(Figure *figure) {
    if (figure_ != nullptr) {
        QColor border_color = figure_->GetBorderColor();
        int width = figure_->GetPenWidth();
        delete figure_;
        figure_ = figure;
        figure_->SetBorderColor(border_color);
        figure_->SetPenWidth(width);
    } else {
        figure_ = figure;
    }
}

void MainWindow::CheckButtons(QPushButton *checked_button) {
    for (QPushButton* button : figure_buttons_) {
        button->setChecked(false);
    }
    checked_button->setChecked(true);
}

void MainWindow::UncheckButtons() {
    for (QPushButton* button : figure_buttons_) {
        button->setChecked(false);
    }
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == graphics_area_ && event->type() == QEvent::MouseButtonPress) {
        ProcessAreaClick(static_cast<QMouseEvent*> (event));
        return true;
    }
    else {
        return QWidget::eventFilter(obj, event);
    }
}

void MainWindow::ProcessAreaClick(QMouseEvent* event) {
    if (figure_ != nullptr){
        /*if(has_figure){
            figure_->Move(event->pos());
            Redraw();
            figure_->Draw(graphics_area_);
        }
        else{*/
            if (figure_->AddPoint(event->pos())){
                figure_->Draw(graphics_area_);
                has_figure = true;
            //}
        }
    }
}

void MainWindow::Redraw() {
    QGraphicsScene* scene = new QGraphicsScene;
    scene->setSceneRect(graphics_area_->geometry());
    graphics_area_->setScene(scene);
}

void MainWindow::ClearArea() {
    Redraw();
    has_figure = false;
    figure_ = nullptr;
    UncheckButtons();
}

void MainWindow::ChooseBorderColor() {
    QColor color = QColorDialog::getColor(Qt::black, this);
    figure_->SetBorderColor(color);
}

void MainWindow::ChooseBacketColor() {
    QColor color = QColorDialog::getColor(Qt::black, this);
    Figure2D* f2d = dynamic_cast<Figure2D*>(figure_);
    f2d->SetBacketColor(color);
}

void MainWindow::SetPenWidth() {
    int width = pen_width_slider_->value();
    figure_->SetPenWidth(width / 5);
}

void MainWindow::ProcessSegmentPush() {
    Segment* segment = new Segment();
    SetFigure(segment);
    CheckButtons(segment_button_);
}
void MainWindow::ProcessRayPush() {
    Ray* ray = new Ray();
    SetFigure(ray);
    CheckButtons(ray_button_);
}
/*void MainWindow::ProcessLinePush() {
    Line* line = new Line();
    SetFigure(line);
    CheckButtons(line_button_);
}*/
void MainWindow::ProcessEllipsePush() {
    Ellipse* ellipse = new Ellipse();
    SetFigure(ellipse);
    CheckButtons(ellipse_button_);
}
void MainWindow::ProcessRectanglePush() {
    Rectangle* rectangle = new Rectangle();
    SetFigure(rectangle);
    CheckButtons(rectangle_button_);
}
void MainWindow::ProcessPolygonPush() {
    Polygon* polygon = new Polygon();
    SetFigure(polygon);
    CheckButtons(polygon_button_);
}
