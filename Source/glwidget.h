#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "GL/glut.h"
#include <QVector>
#include <QGridLayout>
#include <QFrame>
#include <QMouseEvent>
#include <QDebug>
#include <QListWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#define SWAP(x0,x) {float *tmp=x0;x0=x;x=tmp;}
#define IX(i,j) ((i)+(j<<gird_sizelog))

class GLWidget : public QGLWidget//, public QOpenGLFunctions
{
    Q_OBJECT
public:


    struct Rect{
        QPointF point1;
        QPointF point2;
    };
    struct Circle{
        QPointF center;
        float Radius;
    };
    QVector <Rect> RectVec;
    QVector <Circle> circleVec;
    QVector <QPoint> boundary;
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void paintGL();
    void paintRect();
    void resizeGL(int w, int h);

    void genNewGird(int w,int h);
    void regenGird(int w,int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool mMouseDown;
    QPointF lastMousePos;

    QSize girdSize();

    enum Mode{
        Initializing,
        Idle,
        DrawInitialDensity,
        Simulating,
        rectangleMode,
        circleMode

    } mode;


    void startDrawInitialDensity();
    void startSimulating();
    void stopSimulating();

    void clearDensity();

    void diffuse();
    void add_source(float *x, float *s,float dt);
    void diffuse(int b, float *x, float *x0, float diff, float dt);
    void project(float *u, float *v, float *p, float *div);


    void advect(int b, float *d, float *d0, float *u, float *v, float dt);
    void set_bnd(int b, float *x);
    void dens_step(float *x,float *x0,float *u,float *v,float diff,float dt);
    void vel_step(float *u,float *v,float *u0,float *v0,float visc,float dt);

    void setVisc( float value );
    void setDiff( float value );
    float getVisc();
    float getDiff();


    void genGird2DArray(float *&g);
    void clearGird2DArray(float *&g);
    void freeGird2DArray(float *&g);
    void copyGird2DArray(float *gfrom, float *gto);

    void rectMode();
    void checkBoundary(int b,float *x);
    void checkCircle(int b,float *x);

    void clearBarrier();
    qreal initialVel;
    qreal initialDes;
    QColor color;

signals:
public slots:
    void simulationTick();

protected:
    float* gird;
    float* initial;

    float* u;
    float* u_prev;
    float* v;
    float* v_prev;
    bool* barrier;

    int gird_w;
    int gird_h;
    int gird_total;
    int gird_sizelog;
    int NSquare;
    int Nplus1;
    int N;


    int timerInterval;
    QTimer timer;
    QElapsedTimer elapsedTime;
    float visc;
     float diff;
    void paintGird();
    void paintCircle();




};


#endif // GLWIDGET_H
