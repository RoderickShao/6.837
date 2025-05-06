# include "curve.h"
#include <windows.h>
#include <GL/gl.h>
void Curve::Paint(ArgParser *args)
{
    glLineWidth(2);
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < numVertices; i++){
        glVertex2f(getVertex(i).x(), getVertex(i).y());    
    }
    glEnd();

    Vec3f* points = tessellate(args);

    glPointSize(4);
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <  numCurves*args->curve_tessellation; i++){
        glVertex2f(points[i].x(), points[i].y()); 
    }
    glEnd();
    
    for (int i = 0; i < numVertices; i++)
    {
        glPointSize(5);
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2f(getVertex(i).x(), getVertex(i).y());
        glEnd();
    }

}

Vec3f* BezierCurve::tessellate(ArgParser *args)
{
    Vec3f* points = new Vec3f[numCurves*args->curve_tessellation];
    float step = 1.0 / (args->curve_tessellation-1);
    for (int i = 0; i < numVertices-3; i+=3 )
    {
        float vertex[]={
        vertices[i].x(), vertices[i+1].x(), vertices[i+2].x(), vertices[i+3].x(),
        vertices[i].y(), vertices[i+1].y(), vertices[i+2].y(), vertices[i+3].y(),
        vertices[i].z(), vertices[i+1].z(), vertices[i+2].z(), vertices[i+3].z(),
        1, 1, 1, 1
        };
        Matrix matVertex(vertex);
        for (int j = 0; j < args->curve_tessellation; j++)
        {
            float t = j * step;
            Vec4f T(t*t*t, t*t, t, 1);
            Matrix m = matVertex * mat;
            m.Transform(T);
            points[(i/3) * args->curve_tessellation+j] = Vec3f(T[0], T[1], T[2]);
        }
    }
    return points;
}

Vec3f* BSplineCurve::tessellate(ArgParser *args)
{
    Vec3f* points = new Vec3f[numCurves*args->curve_tessellation];
    float step = 1.0 / (args->curve_tessellation-1);
    for (int i = 0; i < numVertices-3; i++ )
    {
        float vertex[]={
        vertices[i].x(), vertices[i+1].x(), vertices[i+2].x(), vertices[i+3].x(),
        vertices[i].y(), vertices[i+1].y(), vertices[i+2].y(), vertices[i+3].y(),
        vertices[i].z(), vertices[i+1].z(), vertices[i+2].z(), vertices[i+3].z(),
        1, 1, 1, 1
        };
        Matrix matVertex(vertex);
        for (int j = 0; j < args->curve_tessellation; j++)
        {
            float t = j * step;
            Vec4f T(t*t*t, t*t, t, 1);
            Matrix m = matVertex * mat;
            m.Transform(T);
            points[i * args->curve_tessellation+j] = Vec3f(T[0], T[1], T[2]);
        }
    }
    return points;
}

void BezierCurve::OutputBezier(FILE *file)
{
    fprintf(file, "bezier\n");
    fprintf(file, "num_vertices %d\n", numVertices);
    for (int i = 0; i < numVertices; i++)
    {
        Vec3f v = getVertex(i);
        fprintf(file, "%f %f %f\n", v.x(), v.y(), v.z());
    }
}

void BezierCurve::OutputBSpline(FILE *file)
{
    fprintf(file, "bspline\n");
    float vertex[]={
        vertices[0].x(), vertices[1].x(), vertices[2].x(), vertices[3].x(),
        vertices[0].y(), vertices[1].y(), vertices[2].y(), vertices[3].y(),
        vertices[0].z(), vertices[1].z(), vertices[2].z(), vertices[3].z(),
        1, 1, 1, 1
    };
    Matrix matVertex(vertex);
    Matrix result = matVertex * matInver;
    fprintf(file, "num_vertices %d\n", numVertices);
    for (int i = 0; i < 4; i++)
    {
        Vec3f v = Vec3f(result.Get(i, 0), result.Get(i, 1), result.Get(i, 2));
        fprintf(file, "%f %f %f\n", v.x(), v.y(), v.z());
    }
}

void BSplineCurve::OutputBSpline(FILE *file)
{
    fprintf(file, "bspline\n");
    fprintf(file, "num_vertices %d\n", numVertices);
    for (int i = 0; i < numVertices; i++)
    {
        Vec3f v = getVertex(i);
        fprintf(file, "%f %f %f\n", v.x(), v.y(), v.z());
    }
}

void BSplineCurve::OutputBezier(FILE *file)
{
    fprintf(file, "bezier\n");
    float vertex[]={
        vertices[0].x(), vertices[1].x(), vertices[2].x(), vertices[3].x(),
        vertices[0].y(), vertices[1].y(), vertices[2].y(), vertices[3].y(),
        vertices[0].z(), vertices[1].z(), vertices[2].z(), vertices[3].z(),
        1, 1, 1, 1
    };
    Matrix matVertex(vertex);
    Matrix result = matVertex * matInver;
    fprintf(file, "num_vertices %d\n", numVertices);
    for (int i = 0; i < 4; i++)
    {
        Vec3f v = Vec3f(result.Get(i, 0), result.Get(i, 1), result.Get(i, 2));
        fprintf(file, "%f %f %f\n", v.x(), v.y(), v.z());
    }
}
