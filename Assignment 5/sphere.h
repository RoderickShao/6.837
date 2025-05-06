#ifndef ASSIGNMENT2_SPHERE_H
#define ASSIGNMENT2_SPHERE_H

#include "object3d.h"
#include "grid.h"

class Sphere : public Object3D {
public:
    Sphere(const Vec3f &center, float radius,Material *m) : 
            center(center), radius(radius),Object3D(m) {

        Vec3f min = center - Vec3f(radius, radius, radius);
        Vec3f max = center + Vec3f(radius, radius, radius);
        boundingBox = new BoundingBox(min, max);
    }
    Sphere(): Sphere(Vec3f(),0,nullptr){}

    Vec3f getCenter() const { return center; }
    float getRadius() const { return radius; }

    void paint() override; 

    bool intersect(const Ray &r, Hit &h, float tmin) override;

    void insertIntoGrid(Grid *g, Matrix *m) override;

protected:
    Vec3f getPoint(float phi, float theta);
    Vec3f center;
    float radius;
};
#endif