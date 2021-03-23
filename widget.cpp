#include "widget.h"
#include "ui_widget.h"
#include <iostream>

const long double EPS = 1e-6;

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    draw = 1;
    D = 0.05;

    //this->setWindowState(Qt::WindowFullScreen);
    //W = this->width();
    //H = this->height();

    W = H = 900;
    this->setFixedSize(W, H);
    PM = QPixmap(W, H);
    RB = nullptr;
    QFont f0 = lab_x.font();
    f0.setFamily("Courier");
    f0.setPixelSize(18);
    lab_x.setFont(f0);
    lab_y.setFont(f0);
    lab_c.setFont(f0);
    lab_x.setParent(this);
    lab_y.setParent(this);
    lab_c.setParent(this);
    lab_x.setStyleSheet("QLabel { color : white; }");
    lab_y.setStyleSheet("QLabel { color : white; }");
    lab_c.setStyleSheet("QLabel { color : white; }");
    lab_x.setGeometry(10, 5, 400, 30);
    lab_y.setGeometry(10, 45, 400, 30);
    lab_c.setGeometry(10, 85, 600, 30);

    X1 = -2, Y1 = 2, X2 = 2, Y2 = -2;

    K = 60;
    MUL = (long double)H / 4.0;

    points.push_back(cn(-0.3, 0.8));
    points.push_back(cn(-1, 0));
    points.push_back(cn(0.3, 0));
    points.push_back(cn(0.2, -0.65));
    points.push_back(cn(0.4, -0.2));
    points.push_back(cn(0.4, -0.1));
    points.push_back(cn(0.4, -0.4));
    points.push_back(cn(-0.9, -0.3));
    points.push_back(cn(-0.5, -0.7));
    points.push_back(cn(-0.75, -0.15));
    points.push_back(cn(-0.75, -0.3));
    points.push_back(cn(-0.65, -0.6));
    points.push_back(cn(-0.35, 0.7));
    points.push_back(cn(0.35, -0.05));
    points.push_back(cn(-0.8, -0.15));
    points.push_back(cn(-0.8, -0.2));
    points.push_back(cn(0.4, -0.25));
    points.push_back(cn(-0.6, -0.5));

    colors.resize(5);
    for (int i = 0; i < colors.size(); ++i) {
        colors[i].resize(5);
    }

    colors[0][0] = QColor(0, 5, 21);
    colors[0][1] = QColor(37, 44, 63);
    colors[0][2] = QColor(95, 165, 178);
    colors[0][3] = QColor(240, 235, 148);
    colors[0][4] = QColor(234, 108, 95);

    colors[1][0] = QColor(56, 62, 105);
    colors[1][1] = QColor(96, 136, 191);
    colors[1][2] = QColor(127, 174, 191);
    colors[1][3] = QColor(104, 223, 208);
    colors[1][4] = QColor(173, 255, 238);

    colors[2][0] = QColor(158, 47, 54);
    colors[2][1] = QColor(245, 140, 107);
    colors[2][2] = QColor(250, 229, 77);
    colors[2][3] = QColor(255, 230, 148);
    colors[2][4] = QColor(234, 237, 244);

    colors[3][0] = QColor(139, 75, 98);
    colors[3][1] = QColor(187, 111, 107);
    colors[3][2] = QColor(234, 150, 116);
    colors[3][3] = QColor(252, 188, 128);
    colors[3][4] = QColor(247, 226, 156);

    colors[4][0] = QColor(14, 36, 49);
    colors[4][1] = QColor(55, 33, 84);
    colors[4][2] = QColor(252, 58, 82);
    colors[4][3] = QColor(249, 178, 72);
    colors[4][4] = QColor(232, 213, 183);

    q1 = QColor(56, 62, 105), q2 = QColor(96, 136, 191), q3 = QColor(127, 174, 191),
            q4 = QColor(104, 223, 208), q5 = QColor(173, 255, 238);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    START = points[qrand() % points.size()];
    //START = cn(0.5, 0.5);
    C = START;

    //tools.setFixedSize(500, 500);
    tools.setWindowTitle("Colors");

    layout.setHorizontalSpacing(1);
    layout.setVerticalSpacing(1);

    layout.addWidget(&c0, 0, 0);
    layout.addWidget(&b1, 1, 0);
    layout.addWidget(&c1, 1, 1);
    layout.addWidget(&b2, 2, 0);
    layout.addWidget(&c2, 2, 1);
    layout.addWidget(&b3, 3, 0);
    layout.addWidget(&c3, 3, 1);
    layout.addWidget(&b4, 4, 0);
    layout.addWidget(&c4, 4, 1);
    layout.addWidget(&b5, 5, 0);
    layout.addWidget(&c5, 5, 1);
    layout.addWidget(&rand, 6, 0);

    QFont f = c1.font();
    f.setFamily("Courier");
    f.setPixelSize(20);

    rand.setText("random fractal");
    rand.setFont(f);

    c0.setFont(f);
    c0.setText("Choose the fractal color");
    c0.setFixedHeight(30);
    c1.setFont(f);
    c1.setText("sunny day");
    c1.setFixedHeight(30);
    c2.setFont(f);
    c2.setText("ocean water");
    c2.setFixedHeight(30);
    c3.setFont(f);
    c3.setText("camp fire");
    c3.setFixedHeight(30);
    c4.setFont(f);
    c4.setText("cozy blanket");
    c4.setFixedHeight(30);
    c5.setFont(f);
    c5.setText("summer berry");
    c5.setFixedHeight(30);

    tools.setLayout(&layout);
    tools.show();

    this->setStyleSheet("Widget {background-color: #F0DEFC}");
    QObject::connect(&b1, SIGNAL(toggled(bool)), this, SLOT(set_color1(bool)));
    QObject::connect(&b2, SIGNAL(toggled(bool)), this, SLOT(set_color2(bool)));
    QObject::connect(&b3, SIGNAL(toggled(bool)), this, SLOT(set_color3(bool)));
    QObject::connect(&b4, SIGNAL(toggled(bool)), this, SLOT(set_color4(bool)));
    QObject::connect(&b5, SIGNAL(toggled(bool)), this, SLOT(set_color5(bool)));
    QObject::connect(&rand, SIGNAL(released()), this, SLOT(gen_rand_fract()));

}

Widget::~Widget()
{
    delete ui;
}

int Widget::xm(long double x) {
    return (x - X1) * MUL;
}

int Widget::ym(long double y) {
    return (y + Y1) * MUL;
}

long double Widget::x(int xm) {
    return (long double)X1 + (long double)xm / (long double)MUL;
}

long double Widget::y(int ym) {
    return (long double)Y1 - (long double)ym / (long double)MUL;
}

cn Widget::f(cn z) {
    return z.sq() + C;
}

int Widget::get_iter(cn z) {
    for (int i = 0; i < K; ++i) {
        if (z.len() - 2.0 >= -EPS) {
            return i;
        }
        z = f(z);
    }
    return K;
}

void Widget::gen_rand_fract() {
    START = points[qrand() % points.size()];
    C = START;
    MUL = (long double)H / 4.0;
    X1 = -2, Y1 = 2, X2 = 2, Y2 = -2;
    draw = 1;
    repaint();
}

void Widget::set_color1(bool p) {
    if (!p) return;
    q1 = colors[0][0];
    q2 = colors[0][1];
    q3 = colors[0][2];
    q4 = colors[0][3];
    q5 = colors[0][4];
    draw = 1;
    repaint();
}

void Widget::set_color2(bool p) {
    if (!p) return;
    q1 = colors[1][0];
    q2 = colors[1][1];
    q3 = colors[1][2];
    q4 = colors[1][3];
    q5 = colors[1][4];
    draw = 1;
    repaint();
}

void Widget::set_color3(bool p) {
    if (!p) return;
    q1 = colors[2][0];
    q2 = colors[2][1];
    q3 = colors[2][2];
    q4 = colors[2][3];
    q5 = colors[2][4];
    draw = 1;
    repaint();
}

void Widget::set_color4(bool p) {
    if (!p) return;
    q1 = colors[3][0];
    q2 = colors[3][1];
    q3 = colors[3][2];
    q4 = colors[3][3];
    q5 = colors[3][4];
    draw = 1;
    repaint();
}

void Widget::set_color5(bool p) {
    if (!p) return;
    q1 = colors[4][0];
    q2 = colors[4][1];
    q3 = colors[4][2];
    q4 = colors[4][3];
    q5 = colors[4][4];
    draw = 1;
    repaint();
}

void get_color(int &r, int &g, int &b, QColor q1, QColor q2, int K, int u) {
    r = q1.red() + (int)((q2.red() - q1.red()) * (4 * u) / K);
    g = q1.green() + (int)((q2.green() - q1.green()) * (4 * u) / K);
    b = q1.blue() + (int)((q2.blue() - q1.blue()) * (4 * u) / K);
}

QString ld_to_str(long double x) {
    x *= 1e7;
    x = (double)((long long)(x));
    x /= 1e7;
    std::stringstream ss;
    ss << x;
    return QString::fromStdString(ss.str());
}

void Widget::paintEvent(QPaintEvent *event) {
    lab_x.setText("x = (" + ld_to_str(X1) + " ; " + ld_to_str(X2) + ")");
    lab_y.setText("y = (" + ld_to_str(Y1) + " ; " + ld_to_str(Y2) + ")");
    lab_c.setText("c = (" + ld_to_str(C.a) + ") + (" + ld_to_str(C.b) + ")i");
    if (!draw) {
        QPainter p2(this);
        p2.drawPixmap(0, 0, W, H, PM);
        return;
    }

    QPainter painter(&PM);
    QColor q(0, 0, 0);

    //sunny day
    //QColor q(0, 0, 0), q1(0, 5, 21), q2(37, 44, 63), q3(95, 165, 178), q4(240, 235, 148), q5(234, 108, 95);

    //ocean water
    //QColor q(0, 0, 0), q1(56, 62, 105), q2(96, 136, 191), q3(127, 174, 191), q4(104, 223, 208), q5(173, 255, 238);

    //camp fire
    //QColor q(0, 0, 0), q4(255, 230, 148), q1(158, 47, 54), q2(245, 140, 107), q3(250, 229, 77), q5(234, 237, 244);

    //cozy blanket
    //QColor q(0, 0, 0), q1(139, 75, 98), q2(187, 111, 107), q3(234, 150, 116), q4(252, 188, 128), q5(247, 226, 156);

    //summer berry
    //QColor q(0, 0, 0), q1(14, 36, 49), q2(55, 33, 84), q3(252, 58, 82), q4(249, 178, 72), q5(232, 213, 183);

    //umbrella
    //QColor q(0, 0, 0), q1(245, 244, 236), q2(86, 99, 138), q3(66, 186, 120), q4(250, 200, 205), q5(243, 185, 24);

    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            cn z(x(i), y(j));
            int num = get_iter(z);
            int u = num % (K / 4);
            int r, g, b;

            if (num <= K / 4) {
                get_color(r, g, b, q1, q2, K, u);
            }
            else if (num <= K / 2) {
                get_color(r, g, b, q2, q3, K, u);
            }
            else if (num <= 3 * K / 4) {
                get_color(r, g, b, q3, q4, K, u);
            }
            else {
                get_color(r, g, b, q4, q5, K, u);
            }
            q = QColor(r, g, b);
            painter.setPen(QPen(q, 2, Qt::SolidLine, Qt::FlatCap));
            painter.drawPoint(i, j);
        }
    }
    QPainter p2(this);
    p2.drawPixmap(0, 0, W, H, PM);
    draw = 0;
}

void Widget::keyPressEvent(QKeyEvent *event) {
    //std::cerr << event->key() << "\n";
    if (event->key() == Qt::Key_Escape) {
        this->close();
    }
    if (event->key() == 49) {
        C.a += D;
        draw = 1;
        repaint();
    }
    else if (event->key() == 50) {
        C.a -= D;
        draw = 1;
        repaint();
    }
    else if (event->key() == 51) {
        C.b += D;
        draw = 1;
        repaint();
    }
    else if (event->key() == 52) {
        C.b -= D;
        draw = 1;
        repaint();
    }
    else if (event->key() == 32) {
        C = START;
        MUL = (long double)H / 4.0;
        X1 = -2, Y1 = 2, X2 = 2, Y2 = -2;
        draw = 1;
        repaint();
    }
}

void Widget::mousePressEvent(QMouseEvent *event) {
    origin = event->pos();
    if (!RB) {
        RB = new QRubberBand(QRubberBand::Rectangle, this);
    }
    RB->setGeometry(QRect(origin, QSize()));
    RB->show();
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    RB->setGeometry(QRect(origin, event->pos()).normalized());
    repaint();
}

void Widget::mouseReleaseEvent(QMouseEvent *event) {
    long double x1 = x(origin.x()), y1 = y(origin.y()), x2 = x(event->x()), y2 = y(event->y());
    long double sz = std::max(fabs(x2 - x1), fabs(y2 - y1));

    long double x0 = (x1 + x2) / 2.0, y0 = (y1 + y2) / 2.0;
    X1 = x0 - sz / 2;
    X2 = x0 + sz / 2;
    Y1 = y0 + sz / 2;
    Y2 = y0 - sz / 2;

    MUL = H / sz;
    draw = 1;

    RB->hide();
    repaint();
}

void Widget::closeEvent(QCloseEvent *event) {
    tools.close();
}
