#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    gird(NULL),
    gird_h(0),
    gird_w(0),
    mode(Initializing),
    mMouseDown(false)
{
    genNewGird(128,128);
    //this->setFormat(QGLFormat(QGL::SampleBuffers));


    timerInterval = 30;
    connect(&timer,SIGNAL(timeout()),this,SLOT(simulationTick()));
    visc = 0.0000000001;
    diff = 0.0000000001;

    initialVel = 500;
    initialDes = 1.25;

    color = QColor::fromRgb(255,255,255);

}

GLWidget::~GLWidget()
{
    if(gird){
        freeGird2DArray(gird);
        freeGird2DArray(initial);
        freeGird2DArray(u);
        freeGird2DArray(v);
        freeGird2DArray(u_prev);
        freeGird2DArray(v_prev);
    }
}



void GLWidget::initializeGL()
{
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //initializeOpenGLFunctions();

    //initializeTexture();
    //prepareShader();

    glClearColor(0.0, 0.0, 0.0, 0.0);


    //glEnable(GL_MULTISAMPLE);
    //glEnable(GL_LINE_SMOOTH);

    startSimulating();

}

void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    paintGird();
    paintRect();
    paintCircle();
}
void GLWidget::paintCircle(){
    if(circleVec.empty())
            return;
        for(int i=0;i<circleVec.size();i++){
            glColor3f(1.0,1.0,1.0);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(circleVec[i].center.x(),circleVec[i].center.y());

            for (float angle=1.0f;angle<361.0f;angle+=0.2)
            {
                float x2 = circleVec[i].center.x()+sin(angle)*circleVec[i].Radius;
                float y2 = circleVec[i].center.y()+cos(angle)*circleVec[i].Radius;
                glVertex2f(x2,y2);
            }
            glEnd();

        }

}
void GLWidget::paintRect(){
    if(RectVec.empty())
        return;
    for(int i=0;i<RectVec.size();i++){
        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,1.0);
            glVertex2f(RectVec[i].point1.x(),RectVec[i].point1.y());
            glVertex2f(RectVec[i].point1.x(),RectVec[i].point2.y());
            glVertex2f(RectVec[i].point2.x(),RectVec[i].point2.y());
            glVertex2f(RectVec[i].point2.x(),RectVec[i].point1.y());
        glEnd();

    }

}

void GLWidget::resizeGL(int w, int h)
{

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, gird_w,gird_h,0);
}

void GLWidget::genNewGird(int w, int h)
{
    //kill old
    if(gird){
        freeGird2DArray(gird);
        freeGird2DArray(initial);
        freeGird2DArray(u);
        freeGird2DArray(v);
        freeGird2DArray(u_prev);
        freeGird2DArray(v_prev);
        delete [] barrier;
    }
    // gen new
    gird_w = w;
    gird_h = h;
    gird_total = gird_w * gird_h;

    gird_sizelog = (int)log2(w);


    N = gird_w-2;
    Nplus1 = gird_w-1;
    NSquare = (N)*(N);


    genGird2DArray(gird);
    genGird2DArray(initial);
    genGird2DArray(u);
    genGird2DArray(v);
    genGird2DArray(u_prev);
    genGird2DArray(v_prev);


    /*
    for(int i = 0; i < gird_w; ++i){
        for(int j = 0; j < gird_h; ++j){
            u_prev[i][j] = 50;
            v_prev[i][j] = 50;//((float)qrand()/RAND_MAX)-0.5;
        }
    }
    */
    barrier = new bool[gird_total];
    for(int i = 0; i < gird_total; ++i)
            barrier[i] = false;

    qDebug() << "w/h" << gird_w << "/" << gird_h << "==" << gird_sizelog;


}

void GLWidget::regenGird(int w, int h)
{
    clearBarrier();
    stopSimulating();

    genNewGird(w,h);
    resizeGL(width(),height());
    startSimulating();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    mMouseDown = true;
    lastMousePos = event->localPos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(mode == Simulating && mMouseDown){
        QPointF girdCoord = event->localPos();
        girdCoord.setX(girdCoord.x() / width() * gird_w);
        girdCoord.setY(girdCoord.y() / height() * gird_h);
        QPoint girdCoordInt = girdCoord.toPoint();

        if ( ! (girdCoordInt.x() < gird_w && girdCoordInt.x() >= 0 &&
             girdCoordInt.y() < gird_h && girdCoordInt.y() >= 0) )
            return;

        QPointF vec = event->localPos() - lastMousePos;
        vec/=sqrt(QPointF::dotProduct(vec,vec));
        vec*=initialVel;


        //lining
        QPointF lastGirdCoord = QPointF(lastMousePos.x() / width() * gird_w,
                                        lastMousePos.y() / height() * gird_h);
        QPointF d = girdCoord - lastGirdCoord;
        int dis = (int)ceil(sqrt( QPointF::dotProduct(d,d)));

        for(int i=0;i<=dis;++i){
            qreal t = (qreal)(i)/dis;
            QPoint pt = (lastGirdCoord * t + girdCoord * (1-t)).toPoint();

            gird[IX(pt.x(),pt.y())] = initialDes;

            u_prev[IX(pt.x(),pt.y())] = vec.x();
            v_prev[IX(pt.x(),pt.y())] = vec.y();
        }

        lastMousePos = event->localPos();
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{


    mMouseDown = false;
    if(mode == rectangleMode){
        Rect rec;
        rec.point1 = lastMousePos;
        rec.point1.setX(rec.point1.x() / width() * gird_w);
        rec.point1.setY(rec.point1.y() / height() * gird_h);
        rec.point2 = event->localPos();
        rec.point2 .setX(rec.point2.x() / width() * gird_w);
        rec.point2 .setY(rec.point2.y() / height() * gird_h);
        RectVec.push_back(rec);
        int rectRight = (int)qMax(rec.point1.x(),rec.point2.x());
        int rectLeft = (int)qMin(rec.point1.x(),rec.point2.x());
        int rectTop = (int)qMin(rec.point1.y(),rec.point2.y());
        int rectBottom = (int)qMax(rec.point1.y(),rec.point2.y());

        qDebug() << rec.point1<<" "<<rec.point2 ;
        for(int i=rectLeft; i<=rectRight;i++){
            for(int j=rectTop;j<=rectBottom;j++){
                barrier[IX(i,j)]=true;
                boundary.push_back(QPoint(i,j));
            }
        }
    }
    if(mode == circleMode){

        QPointF nowPos = event->localPos();
        nowPos.setX(nowPos.x() / width() * gird_w);
        nowPos.setY(nowPos.y() / height() * gird_h);
        Circle c;

        c.center = lastMousePos;
        c.center.setX(c.center.x() / width() * gird_w);
        c.center.setY(c.center.y() / height() * gird_h);
        c.Radius =sqrt((c.center.x()-nowPos.x())*(c.center.x()-nowPos.x())+(c.center.y()-nowPos.y())*(c.center.y()-nowPos.y()));

        circleVec.push_back(c);


        qDebug() << c.Radius<<" "<<c.center ;
        for (int i=0;i<gird_w;i++)
        {
            for (int j=0;j<gird_h;j++)
            {
                float dis = sqrt((i-c.center.x())*(i-c.center.x())+(j-c.center.y())*(j-c.center.y()));
                if(dis-c.Radius<0.5){
                    barrier[IX(i,j)] = true;
                    boundary.push_back(QPoint(i,j));
                }
            }
        }
    }
}

QSize GLWidget::girdSize()
{
    return QSize(gird_w,gird_h);
}

void GLWidget::startDrawInitialDensity()
{
    stopSimulating();
    mode = DrawInitialDensity;
}

void GLWidget::startSimulating()
{
    //copyGird2DArray(gird, initial);

    timer.start(timerInterval);
    elapsedTime.start();
    mode = Simulating;
}

void GLWidget::stopSimulating()
{
    timer.stop();
    mode = Idle;
}

void GLWidget::clearDensity()
{
    clearGird2DArray(gird);
    clearGird2DArray(initial);
    clearGird2DArray(u);
    clearGird2DArray(v);
    clearGird2DArray(u_prev);
    clearGird2DArray(v_prev);
}

void GLWidget::diffuse()
{

}

void GLWidget::add_source(float *x, float *s, float dt)
{
    for (int i=0 ; i<gird_total ; i++ ) x[i] += dt*s[i];
}

void GLWidget::diffuse(int b, float *x, float *x0, float diff, float dt)
{
    float a = NSquare*dt*diff;

    for(int k=0;k<20;++k){
        for(int i = 1; i < Nplus1; ++i){
            for(int j = 1; j < Nplus1; ++j){
                if(barrier[IX(i,j)]) continue;
                x[IX(i,j)] = (x0[IX(i,j)] + a*(x[IX(i-1,j)]+x[IX(i+1,j)]+
                 x[IX(i,j-1)]+x[IX(i,j+1)]))/(1+4*a);
            }
        }
        set_bnd(b,x);
    }
}

void GLWidget::project(float *u, float *v, float *p, float *div)
{
    int i, j, k;
    float h;
    h = 1.0/gird_w;
    for ( i=1 ; i<Nplus1 ; i++ ) {
        for ( j=1 ; j<Nplus1 ; j++ ) {
            div[IX(i,j)] = -0.5*h*(u[IX(i+1,j)]-u[IX(i-1,j)]+
            v[IX(i,j+1)]-v[IX(i,j-1)]);
            p[IX(i,j)] = 0;

        }
    }
    set_bnd (0, div); set_bnd (0, p);
    for ( k=0 ; k<20 ; k++ ) {
        for ( i=1 ; i<Nplus1 ; i++ ) {
            for ( j=1 ; j<Nplus1 ; j++ ) {
                p[IX(i,j)] = (div[IX(i,j)]+p[IX(i-1,j)]+p[IX(i+1,j)]+
                 p[IX(i,j-1)]+p[IX(i,j+1)])/4;
            }
        }
        set_bnd (0, p);
    }
    for ( i=1 ; i<Nplus1 ; i++ ) {
        for ( j=1 ; j<Nplus1 ; j++ ) {
            u[IX(i,j)] -= 0.5*(p[IX(i+1,j)]-p[IX(i-1,j)])/h;
            v[IX(i,j)] -= 0.5*(p[IX(i,j+1)]-p[IX(i,j-1)])/h;
        }
    }
    set_bnd (1, u); set_bnd (2, v);
}
/*
void GLWidget::checkRect(int b,float *x){
    if(RectVec.empty())
        return;
    for(int i=0;i<RectVec.size();i++){
        int rectRight = (int)qMax(RectVec[i].point1.x(),RectVec[i].point2.x());
        int rectLeft = (int)qMin(RectVec[i].point1.x(),RectVec[i].point2.x());
        int rectTop = (int)qMin(RectVec[i].point1.y(),RectVec[i].point2.y());
        int rectBottom = (int)qMax(RectVec[i].point1.y(),RectVec[i].point2.y());
     if(b==1){
            for(int i=rectTop;i<rectBottom;++i){
                x[rectRight][i] = -x[rectRight+1][i];
                x[rectLeft][i] = -x[rectLeft-1][i] ;
            }
     }else{
            for(int i=rectTop;i<rectBottom;++i){
                x[rectRight][i] = x[rectRight+1][i];
                x[rectLeft][i] = x[rectLeft-1][i] ;
            }
     }
     if(b==2){
            for(int i=rectLeft;i<rectRight;++i){
                x[i][rectBottom] = -x[i][rectBottom+1];
                x[i][rectTop] = -x[i][rectTop] ;
            }
     }else{
            for(int i=rectLeft;i<rectRight;++i){
                x[i][rectBottom] = x[i][rectBottom+1];
                x[i][rectTop] = x[i][rectTop] ;
            }
        }
    }
}*/
void GLWidget::checkBoundary(int b,float *x){
    if(circleVec.empty()&&RectVec.empty())
        return;
    if(b!=0){
        for (int i=0;i<boundary.size();i++)
        {
            x[IX(boundary[i].x(),boundary[i].y())] = -x[IX(boundary[i].x(),boundary[i].y())];
        }
    }
     //}else{
        //for (int i=0;i<boundary.size();i++)
        //{
        //    x[boundary[i].x()][boundary[i].y()] =  x[boundary[i].x()][boundary[i].y()];
        //}
    //}


}

void GLWidget::clearBarrier()
{
    for(int i = 0; i < gird_total; ++i)
        barrier[i] = false;
    boundary.clear();
    RectVec.clear();
    circleVec.clear();
}


void GLWidget::set_bnd(int b, float *x)
{
    //checkRect(b,x);
    checkBoundary(b,x);
    if(b==1){
        for(int i=1;i<=N;++i){
            x[IX(0 ,i)] = -x[IX(1,i)];
            x[IX(Nplus1,i)] = -x[IX(N,i)];
        }
    } else {
        for(int i=1;i<=N;++i){
            x[IX(0 ,i)] = x[IX(1,i)];
            x[IX(Nplus1,i)] = x[IX(N,i)];
        }
    }
    if(b==2){
        for(int i=1;i<=N;++i){
            x[IX(i,0 )] = -x[IX(i,1)];
            x[IX(i,Nplus1)] = -x[IX(i,N)];
        }
    }else{
        for(int i=1;i<=N;++i){
            x[IX(i,0 )] = x[IX(i,1)];
            x[IX(i,Nplus1)] =x[IX(i,N)];
        }

    }
    //corner

    x[IX(0 ,0 )] = 0.5*(x[IX(1,0 )]+x[IX(0 ,1)]);
    x[IX(0 ,Nplus1)] = 0.5*(x[IX(1,Nplus1)]+x[IX(0 ,N)]);
    x[IX(Nplus1,0 )] = 0.5*(x[IX(N,0 )]+x[IX(Nplus1,1)]);
    x[IX(Nplus1,Nplus1)] = 0.5*(x[IX(N,Nplus1)]+x[IX(Nplus1,N)]);
}

void GLWidget::dens_step(float *x, float *x0, float *u, float *v, float diff, float dt)
{
    //add_source(x,x0,dt);
    SWAP(x0,x);
    diffuse(0, x, x0, diff, dt);
    SWAP(x0,x);
    advect(0, x, x0, u, v, dt);
}

void GLWidget::vel_step(float *u, float *v, float *u0, float *v0, float visc, float dt)
{
    add_source (u, u0, dt); add_source (v, v0, dt);
    SWAP ( u0, u); diffuse (1, u, u0, visc, dt);
    SWAP ( v0, v); diffuse (2, v, v0, visc, dt);
    project (u, v, u0, v0);
    SWAP ( u0, u); SWAP ( v0, v);
    advect (1, u, u0, u0, v0, dt);
    advect (2, v, v0, u0, v0, dt);
    project (u, v, u0, v0);


}



void GLWidget::genGird2DArray(float *&g)
{
    g = new float[gird_total];
    for(int i = 0; i < gird_total; ++i)
        g[i] = 0;

}

void GLWidget::clearGird2DArray(float *&g)
{
    for(int i = 0; i < gird_total; ++i)
        g[i] = 0;
}

void GLWidget::freeGird2DArray(float *&g)
{

    delete [] g;
}

void GLWidget::copyGird2DArray(float *gfrom, float *gto)
{
    //for(int i = 0; i < gird_w; ++i)
    //    for(int j = 0; j < gird_h; ++j)
    //        gto[i][j] = gfrom[i][j];
}

void GLWidget::advect(int b, float *d, float *d0, float *u, float *v, float dt)
{

    int i,j,i0,j0,i1,j1;
    float x,y,s0,t0,s1,t1,dt0;
    dt0 = dt*gird_w;
    for(int i = 1; i < Nplus1; ++i){
        for(int j = 1; j < Nplus1; ++j){
            x = i-dt0*u[IX(i,j)]; y = j-dt0*v[IX(i,j)];
            if (x<0.5) x=0.5; if (x>N+0.5) x=N+ 0.5; i0=(int)x; i1=i0+1;
            if (y<0.5) y=0.5; if (y>N+0.5) y=N+ 0.5; j0=(int)y; j1=j0+1;
            s1 = x-i0; s0 = 1-s1; t1 = y-j0; t0 = 1-t1;
            d[IX(i,j)] = s0*(t0*d0[IX(i0,j0)]+t1*d0[IX(i0,j1)])+
             s1*(t0*d0[IX(i1,j0)]+t1*d0[IX(i1,j1)]);

        }
    }
    set_bnd(b,d);
}


void GLWidget::simulationTick()
{
    static float dt = 1.0/elapsedTime.restart();
    vel_step (u, v, u_prev, v_prev, visc, dt ); // visc
    dens_step(gird,initial,u,v,diff,dt); // diff
    //copyGird2DArray(u_prev,u);
    //copyGird2DArray(v_prev,v);
    update();
}

void GLWidget::setVisc( float value ){
    visc = value;

}
float GLWidget::getVisc(  ){
    return visc ;

}
void GLWidget::setDiff( float value ){
    diff = value;

}
float GLWidget::getDiff(  ){
    return diff ;

}
void GLWidget::paintGird()
{

    for(int i = 0; i < gird_w; ++i){
        for(int j = 0; j < gird_h; ++j){
            float c = gird[IX(i,j)];

            glBegin(GL_QUADS);
                glColor3f(color.redF()*c,color.greenF()*c,color.blueF()*c);
                glVertex2i(i,j);
                glVertex2i(i+1,j);
                glVertex2i(i+1,j+1);
                glVertex2i(i,j+1);
            glEnd();
        }
    }


    /*

    program.bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textures[0]);


    float textureData[256][256];
    for(int y = 0; y < 256; ++y)
        for(int x = 0; x < 256; ++x){
            textureData[y][x]= gird[x][y];
        }
    glTexSubImage2D(GL_TEXTURE_2D, 0 ,0, 0, 256, 256, GL_RED, GL_FLOAT, (GLvoid*)textureData);

    program.setUniformValue("qt_ModelViewProjectionMatrix",pMatrix);
    program.setUniformValue("qt_Texture0",0);


    glBegin(GL_QUADS);
        glTexCoord2f(1.f,1.f);
        glVertex2i(gird_w,gird_h);
        glTexCoord2f(0.f,1.f);
        glVertex2i(0,gird_h);
        glTexCoord2f(0.f,0.f);
        glVertex2i(0,0);
        glTexCoord2f(1.f,0.f);
        glVertex2i(gird_w,0);
    glEnd();

    program.release();

    */

}

