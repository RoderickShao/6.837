# include "surface.h"
#include <windows.h>
#include <GL/gl.h>

TriangleMesh* SurfaceOfRevolution::OutputTriangles(ArgParser *args) {
    float angle = 2 * M_PI / args->revolution_tessellation;
    Matrix m = Matrix::MakeYRotation(angle);
    Vec3f* points = curve->tessellate(args);
    int num_points = curve->getNumCurves()*args->curve_tessellation;
    auto *mesh = new TriangleNet( args->revolution_tessellation,num_points-1);
    for (auto i = 0; i <= args->revolution_tessellation; i++) {
        for (int j = 0; j < num_points; j++) {
            mesh->SetVertex(i, j, points[j]);
            m.Transform(points[j]);
        }
    }
    return mesh;
}

TriangleMesh* BezierPatch::OutputTriangles(ArgParser *args) {
    auto *mesh = new TriangleNet(args->patch_tessellation-1, args->patch_tessellation-1);
    BezierCurve** curves = new BezierCurve*[4];
    for (int i = 0; i < 4; i++) {
        curves[i] = new BezierCurve(4);
        for (int j = 0; j < 4; j++){
            curves[i]->set(j, vertices[i * 4 + j]);
        }
    }
    
    for (int i = 0; i < args->patch_tessellation; i++) {
        BezierCurve* tmpCurve = new BezierCurve(4);
        tmpCurve->set(0, curves[0]->tessellate(args)[i]);
        tmpCurve->set(1, curves[1]->tessellate(args)[i]);
        tmpCurve->set(2, curves[2]->tessellate(args)[i]);  
        tmpCurve->set(3, curves[3]->tessellate(args)[i]);
        for (int j = 0; j < args->patch_tessellation; j++) {
            
            mesh->SetVertex(i, j, tmpCurve->tessellate(args)[j]);
        }
    }
    return mesh;
}

void BezierPatch::Paint(ArgParser *args) {
    glLineWidth(1);
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 1);
    for (int i = 0; i < 16; i++) {
        Vec3f p = vertices[i];
        glVertex2f(p.x(), p.y());
    }
    glEnd();

    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    for (int i = 0; i < 16; i++) {
        Vec3f p = vertices[i];
        glVertex2f(p.x(), p.y());
    }
    glEnd();
}

