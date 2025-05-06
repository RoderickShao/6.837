# include "transform.h"

bool Transform::intersect(const Ray &r, Hit &h, float tmin) {
    Vec3f ori = r.getOrigin();
    Vec3f dir = r.getDirection();
    Vec4f ori1(ori.x(), ori.y(), ori.z(), 1);
    Vec4f dir1(dir.x(), dir.y(), dir.z(), 0);
    mInv.Transform(ori1);
    mInv.Transform(dir1);
    
    dir = Vec3f(dir1.x(), dir1.y(), dir1.z());
    float dir_len =  dir.Length();
    dir.Normalize();
    Ray r1(Vec3f(ori1.x()/ori1.w(), ori1.y()/ori1.w(), ori1.z()/ori1.w()), dir);  
    bool intersect = object->intersect(r1, h, tmin);
    float t = h.getT()/dir_len;
    if (intersect) {
        Vec4f normal(h.getNormal().x(), h.getNormal().y(), h.getNormal().z(), 0);
        mInvT.Transform(normal);
        Vec3f n = Vec3f(normal.x(), normal.y(), normal.z());
        n.Normalize();
        h.set(t, h.getMaterial(),n, r);
    }
    return intersect;
}