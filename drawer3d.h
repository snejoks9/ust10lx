#pragma once
#include <QWidget>
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <GL/gl.h>
#include <QGLFormat>
#include <QGLContext>
#include <QGLColormap>
#include <QGLPixelBuffer>
#include <QGLFunctions>
#include <QtGlobal>
#include <QOpenGLFunctions>
#include <QGL>
#include <QGLWidget>
#include <QtOpenGL>
#include <d3d8types.h>

class drawer3D : public QOpenGLWidget {

protected:
    void initializeGL( );
    void resizeGL (int nWidth, int nHeight);
    void paintGL ();
    QSize minimumSizeHint() const;
    //    QSize sizeHint();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public:
    drawer3D(QWidget* pwgt = 0);
    QVector<double> vecX, vecY;


public slots:
    void rotate(double x);
    void setXRot(int angle);
    void setYRot(int angle);
    void setZRot(int angle);

private:
    void draw_Axis();
    void draw(QVector<double>xvec,QVector<double>yvec,QVector<double>zvec);
    void renderText(D3DVECTOR &textPosWorld, QString text);
    inline project(GLdouble objx, GLdouble objy, GLdouble objz,
                   const GLdouble model[16], const GLdouble proj[16],
    const GLint viewport[4],
    GLdouble * winx, GLdouble * winy, GLdouble * winz);
    inline void transformPoint(GLdouble out[4], const GLdouble m[16], const GLdouble in[4]);
    int xRot;
    int yRot;
    int zRot;
    int strElemD;
    int chooseD;
    double zoomScale;
    QPoint lastPos;
    QVector<double> xvec,yvec,zvec;

};
