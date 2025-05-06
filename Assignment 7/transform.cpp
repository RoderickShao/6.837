# include "transform.h"
# include <GL/gl.h>

float min_4 (float a, float b, float c, float d) { 
    float t = a < b ? a : b;
    float s = c < d ? c : d;
    return (s < t ? s : t);
}

float max_4 (float a, float b, float c, float d) {
    float t = a > b ? a : b;
    float s = c > d ? c : d;
    return (s > t ? s : t);
}

float min_8 (float a, float b, float c, float d, float e, float f, float g, float h) {
    float t = min_4(a,b,c,d);
    float s = min_4(e,f,g,h);
    return (s < t ? s : t);
}

float max_8 (float a, float b, float c, float d, float e, float f, float g, float h) {
    float t = max_4(a,b,c,d);
    float s = max_4(e,f,g,h);
    return (s > t ? s : t);
}

Vec3f Transform::transformPosition(const Vec3f &v, const Matrix m) const {
    Vec4f v1(v.x(), v.y(), v.z(), 1);
    m.Transform(v1);
    return Vec3f(v1.x()/v1.w(), v1.y()/v1.w(), v1.z()/v1.w());
}

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

void Transform::paint() {
    glPushMatrix();
    GLfloat *glMatrix = m.glGet();
    glMultMatrixf(glMatrix);
    delete[] glMatrix;
    object->paint();
    glPopMatrix();
}