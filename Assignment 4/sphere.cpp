#include "sphere.h"
# include <GL/glut.h>
# include "material.h"
# include "global.h"

# define PI 3.1415927

bool Sphere::intersect(const Ray &r, Hit &h, float tmin) {
    Vec3f vec_oc =  r.getOrigin()-center;
    float a = r.getDirection().Dot3(r.getDirection());
    float b = vec_oc.Dot3(r.getDirection());
    float c = vec_oc.Dot3(vec_oc) - radius * radius;

    if (fabs(c) < EPSILON)
    {
        //if (0<tmin-EPSILON) return false;
        vec_oc.Normalize();
        h.set(0,material,vec_oc,r);
        return true;
    }  
    
    float delta = b * b - c;  
    if (delta < -EPSILON) {
        return false;
    }
    float t0 =  -b - sqrt(delta);
    if (t0 < 0)
        t0 = -b + sqrt(delta);
    /*
    if (t0 < 0)
        return false;  
    */
    if (t0 < tmin) 
        return false;
    Vec3f vec_normal = r.getOrigin() + r.getDirection() * t0 - center;
    vec_normal.Normalize();
    h.set(t0, material,vec_normal,r);
    return true;
}

Vec3f Sphere::getPoint(float phi, float theta) {
    float x = radius * cos(phi) * cos(theta);
    float y = radius * cos(phi) * sin(theta);
    float z = radius * sin(phi);
    return Vec3f(x, y, z) + center;

}

void Sphere::paint() {
   float deltaPhi = M_PI / phiSteps,
            deltaTheta = 2 * M_PI / thetaSteps;

    material->glSetMaterial();
    glBegin(GL_TRIANGLES);
    // phi from -90 to 90
    for (int iPhi = 1; iPhi <= phiSteps; iPhi++) {
        // theta from 0 to 360
        for (int iTheta = 1; iTheta <= thetaSteps; iTheta++) {
            float phi = -M_PI / 2 + iPhi * deltaPhi,
                    lastPhi = -M_PI / 2 + (iPhi - 1) * deltaPhi;
            float theta = iTheta * deltaTheta,
                    lastTheta = (iTheta - 1) * deltaTheta;

            // compute appropriate coordinates & normals
            Vec3f p1 = getPoint(lastPhi, lastTheta),
                    p2 = getPoint(lastPhi, theta),
                    p3 = getPoint(phi, lastTheta),
                    p4 = getPoint(phi, theta);
            Vec3f n1, n2, n3, n4;
            if (!gouraud) { // facet normal
                Vec3f::Cross3(n1, p2 - p1, p3 - p1);
                n1.Normalize();
                Vec3f::Cross3(n2, p4 - p2, p3 - p2);
                n2.Normalize();
            } else {
                n1 = p1 - center; n1.Normalize();
                n2 = p2 - center; n2.Normalize();
                n3 = p3 - center; n3.Normalize();
                n4 = p4 - center; n4.Normalize();
            }

            // send gl vertex commands
            if (!gouraud) {
                if ((p1 - p2).Length() > EPSILON) {
                    glNormal3f(n1.x(), n1.y(), n1.z());
                    glVertex3f(p1.x(), p1.y(), p1.z());
                    glVertex3f(p2.x(), p2.y(), p2.z());
                    glVertex3f(p3.x(), p3.y(), p3.z());
                }
                if ((p3 - p4).Length() > EPSILON) {
                    glNormal3f(n2.x(), n2.y(), n2.z());
                    glVertex3f(p2.x(), p2.y(), p2.z());
                    glVertex3f(p3.x(), p3.y(), p3.z());
                    glVertex3f(p4.x(), p4.y(), p4.z());
                }
            } else {
                if ((p1 - p2).Length() > EPSILON) {
                    glNormal3f(n1.x(), n1.y(), n1.z());
                    glVertex3f(p1.x(), p1.y(), p1.z());
                    glNormal3f(n2.x(), n2.y(), n2.z());
                    glVertex3f(p2.x(), p2.y(), p2.z());
                    glNormal3f(n3.x(), n3.y(), n3.z());
                    glVertex3f(p3.x(), p3.y(), p3.z());
                }
                if ((p3 - p4).Length() > EPSILON) {
                    glNormal3f(n2.x(), n2.y(), n2.z());
                    glVertex3f(p2.x(), p2.y(), p2.z());
                    glNormal3f(n3.x(), n3.y(), n3.z());
                    glVertex3f(p3.x(), p3.y(), p3.z());
                    glNormal3f(n4.x(), n4.y(), n4.z());
                    glVertex3f(p4.x(), p4.y(), p4.z());
                }
            }
        }
    }
    glEnd();

}