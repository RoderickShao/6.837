# include "plane.h"

bool Plane::intersect(const Ray &r, Hit &h, float tmin) {
    Vec3f normal = getNormal();
    
    //光线与平面几乎平行的情况
    if (fabs(normal.Dot3(r.getDirection())) <EPSILON) return false;

    float t =  (d-r.getOrigin().Dot3(normal)) / r.getDirection().Dot3(normal);

    if (t < tmin-EPSILON) return false;

    h.set(t,material,normal, r);
    return true;
}