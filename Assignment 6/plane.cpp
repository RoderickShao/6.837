# include "plane.h"
# include "material.h"
# include <GL/gl.h>
# include "matrix.h"
# include "grid.h"
# include "transform.h"

bool Plane::intersect(const Ray &r, Hit &h, float tmin) {
    Vec3f normal = getNormal();
    
    //光线与平面几乎平行的情况
    if (fabs(normal.Dot3(r.getDirection())) <EPSILON) return false;

    float t =  (d-r.getOrigin().Dot3(normal)) / r.getDirection().Dot3(normal);

    if (t < tmin-EPSILON) return false;

    h.set(t,material,normal, r);
    RayTracingStats::IncrementNumIntersections();
    return true;
}

void Plane::paint() {
    material->glSetMaterial();
    Vec3f v(1,0,0);
    if (normal.y()==0 && normal.z()==0)
        v.Set(0,1,0);    
    Vec3f b1,b2;
    Vec3f::Cross3(b1,normal,v);
    Vec3f::Cross3(b2,normal,b1);
    b1.Normalize();
    b2.Normalize();
    Vec3f c1 = b1*100000;
    Vec3f c2 = b2*100000;
    Vec3f c3 = d*normal;

    Vec3f d1 = c1+c2+c3;
    Vec3f d2 = c2+c3-c1;
    Vec3f d3 = c3-c1-c2;
    Vec3f d4 = c1-c2+c3;

    glBegin(GL_QUADS);
        glNormal3f(normal.x(), normal.y(), normal.z());
        glVertex3f(d1.x(), d1.y(), d1.z());
        glVertex3f(d2.x(), d2.y(), d2.z());
        glVertex3f(d3.x(), d3.y(), d3.z());
        glVertex3f(d4.x(), d4.y(), d4.z());
    glEnd();
}

void Plane::insertIntoGrid(Grid *g, Matrix *m) {
    Object3D *obj = this;
    if (m != nullptr)
    {
        obj = new Transform(*m, this);
    }
    g->insertInfObject(obj);
}