#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QColor>
#include <QVector>
#include <QPixmap>
#include <QRubberBand>
#include <QLabel>
#include <sstream>
#include "QTime"
#include <QRadioButton>
#include <QGridLayout>
#include <QPushButton>

struct cn {
    long double a, b;
    cn(long double a1 = 0, long double b1 = 0) {
        a = a1, b = b1;
    }
    long double len() {
        return sqrt(a * a + b * b);
    }
    cn operator+ (cn other) {
        return cn(a + other.a, b + other.b);
    }
    cn operator- (cn other) {
        return cn(a - other.a, b - other.b);
    }
    cn operator* (cn other) {
        return cn(a * other.a - b * other.b, a * other.b + b * other.a);
    }
    cn conjugate() {
        return cn(a, -b);
    }
    cn operator/ (cn other) {
        double d = a * a + b * b;
        return cn((a * other.a + b * other.b) / d, (-a * other.b + b * other.a) / d);
    }
    cn sq() {
        return cn(a * a - b * b, 2 * a * b);
    }
    cn operator+ (long double other) {
        return cn(a + other, b);
    }
    cn operator- (long double other) {
        return cn(a - other, b);
    }
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QPixmap PM;
    QRubberBand *RB;
    QLabel lab_x, lab_y, lab_c;

    QWidget tools;
    QGridLayout layout;
    QRadioButton b1, b2, b3, b4, b5;
    QLabel c0, c1, c2, c3, c4, c5;
    QVector <QVector <QColor>> colors;
    QColor q1, q2, q3, q4, q5;
    QPushButton rand;

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);

    QPoint origin;
    int W, H, K;
    long double MUL, X1, Y1, X2, Y2;
    long double D;
    bool draw;
    int xm(long double);
    int ym(long double);
    long double x(int);
    long double y(int);
    int get_iter(cn);
    cn f(cn);
    cn C, START;
    QVector <cn> points;

public slots:
    void set_color1(bool);
    void set_color2(bool);
    void set_color3(bool);
    void set_color4(bool);
    void set_color5(bool);
    void gen_rand_fract();


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
