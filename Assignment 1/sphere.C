#include "sphere.h"

bool Sphere::intersect(const Ray &r, Hit &h, float tmin) {
    Vec3f vec_oc =  center -r.getOrigin();
    float a = r.getDirection().Dot3(r.getDirection());
    float b = vec_oc.Dot3(r.getDirection());
    float c = vec_oc.Dot3(vec_oc) - radius * radius;

    if (fabs(c) < EPSILON)
    {
        //if (0<tmin-EPSILON) return false;
        h.set(0,material,r);
        return true;
    }  
    
    float delta = b * b - c;  
    if (delta < -EPSILON) {
        return false;
    }
    float t0 =  b - sqrt(delta);
    /*if (t0 < 0)
        t0 = b + sqrt(delta);
    if (t0 < 0)
        return false;  
    */
    if (t0 < 0) 
        return false;
    h.set(t0, material, r);
    return true;
}