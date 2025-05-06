#ifndef ASSIGNMENT_2_PLANE_H
#define ASSIGNMENT_2_PLANE_H

# include "object3d.h"

class Plane : public Object3D {
    public:
        Plane(const Vec3f &normal, float d, Material *m):
            normal(normal), d(d), Object3D(m) {
                boundingBox = NULL;
            }
        Plane(): Plane(Vec3f(),0,nullptr){}

        Vec3f getNormal() const { return normal; }
        float getD() const {return d;}

        void paint() override;

        bool intersect(const Ray &r, Hit &h, float tmin) override;

    private:
        Vec3f normal;
        float d;
};


#endif
