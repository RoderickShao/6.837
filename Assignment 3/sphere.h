#ifndef ASSIGNMENT2_SPHERE_H
#define ASSIGNMENT2_SPHERE_H

#include "object3d.h"


class Sphere : public Object3D {
public:
    Sphere(const Vec3f &center, float radius,Material *m) : 
            center(center), radius(radius),Object3D(m) {}
    Sphere(): Sphere(Vec3f(),0,nullptr){}

    Vec3f getCenter() const { return center; }
    float getRadius() const { return radius; }

    void paint() override; 

    bool intersect(const Ray &r, Hit &h, float tmin) override;

protected:
    Vec3f getPoint(float phi, float theta);
    Vec3f center;
    float radius;
};
#endif