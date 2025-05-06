# include "triangle.h"
# include <GL/gl.h>
# include "material.h"

bool Triangle::intersect (const Ray &r, Hit &h, float tmin)
{
    Vec3f e1 = v1 - v0;
    Vec3f e2 = v2 - v0;
    Vec3f s1,s2;
    Vec3f::Cross3(s1,r.getDirection(), e2);
    Vec3f::Cross3(s2,r.getOrigin()-v0, e1);
    


    float det = 1/s1.Dot3(e1);

    float tnear = s2.Dot3(e2)* det;
    float u = s1.Dot3(r.getOrigin() - v0)*det;
    float v =s2.Dot3(r.getDirection())*det;

    if (tnear >=tmin-EPSILON && u >= -EPSILON && v >=-EPSILON && (u+v) <= 1+EPSILON)
    {
        h.set(tnear, material,normal, r);
        return true;
    } 
    
    return false;
}

void Triangle::paint()
{
    material->glSetMaterial();
    glBegin(GL_TRIANGLES);
    glNormal3f(normal.x(), normal.y(), normal.z());
    glVertex3f(v0.x(), v0.y(), v0.z());
    glVertex3f(v1.x(), v1.y(), v1.z());
    glVertex3f(v2.x(), v2.y(), v2.z());
    glEnd();
}