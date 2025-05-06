# ifndef ASSIGNMENT_2_TRIANGLE_H
# define ASSIGNMENT_2_TRIANGLE_H

#include "object3d.h"

class Triangle : public Object3D {
    public:
        Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m) : Object3D(m) {
            v0 = a;
            v1 = b;
            v2 = c;
            Vec3f::Cross3(normal, v1 - v0, v2 - v0);
            normal.Normalize();
        }

        void paint() override;
        bool intersect(const Ray &r, Hit &h, float tmin) override;
    private:
        Vec3f v0, v1, v2;
        Vec3f normal;
};

# endif