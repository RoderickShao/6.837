# ifndef ASSIGNMENT_2_TRIANGLE_H
# define ASSIGNMENT_2_TRIANGLE_H

#include "object3d.h"
#include <algorithm>

class Triangle : public Object3D {
    public:
        Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m) : Object3D(m) {
            v0 = a;
            v1 = b;
            v2 = c;
            Vec3f::Cross3(normal, v1 - v0, v2 - v0);
            normal.Normalize();

            Vec3f min = Vec3f(std::min(std::min(v0.x(), v1.x()), v2.x()), 
                            std::min(std::min(v0.y(), v1.y()), v2.y()), 
                            std::min(std::min(v0.z(), v1.z()), v2.z()));
            Vec3f max = Vec3f(std::max(std::max(v0.x(), v1.x()), v2.x()),
                            std::max(std::max(v0.y(), v1.y()), v2.y()),     
                            std::max(std::max(v0.z(), v1.z()), v2.z()));
            boundingBox = new BoundingBox(min, max);
        }

        void paint() override;
        bool intersect(const Ray &r, Hit &h, float tmin) override;

        void insertIntoGrid(Grid *g, Matrix *m) override;

    private:
        Vec3f v0, v1, v2;
        Vec3f normal;
};

# endif