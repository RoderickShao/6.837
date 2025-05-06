# include "triangle.h"
# include "material.h"
# include "matrix.h"
# include "grid.h"
# include <windows.h>

bool Triangle::intersect (const Ray &r, Hit &h, float tmin)
{
    Vec3f e1 = v1 - v0;
    Vec3f e2 = v2 - v0;
    Vec3f s1,s2;
    Vec3f::Cross3(s1,r.getDirection(), e2);
    Vec3f::Cross3(s2,r.getOrigin()-v0, e1);

    float det = 1/s1.Dot3(e1);

    float tnear = s2.Dot3(e2)* det;
    float u = s1.Dot3(r.getOrigin() - v0)*det;
    float v =s2.Dot3(r.getDirection())*det;

    if (tnear >=tmin-EPSILON && u >= -EPSILON && v >=-EPSILON && (u+v) <= 1+EPSILON)
    {
        h.set(tnear, material,normal, r);
        return true;
    } 
    
    return false;
}

void Triangle::paint()
{
    material->glSetMaterial();
    glBegin(GL_TRIANGLES);
    glNormal3f(normal.x(), normal.y(), normal.z());
    glVertex3f(v0.x(), v0.y(), v0.z());
    glVertex3f(v1.x(), v1.y(), v1.z());
    glVertex3f(v2.x(), v2.y(), v2.z());
    glEnd();
}

void Triangle::insertIntoGrid(Grid *g, Matrix *m)
{
    int nx, ny, nz;
    std::tie(nx, ny, nz) = g->getGridSize();
    Vec3f voxel = g->getVoxelSize();
    Vec3f ta = v0, tb = v1, tc = v2;
    Vec3f pMin = g->getMin();
    if (m != nullptr)
    {
        m->Transform(ta);
        m->Transform(tb);
        m->Transform(tc);
    }

    auto min = Vec3f(std::min({ta.x(), tb.x(), tc.x()}),
                     std::min({ta.y(), tb.y(), tc.y()}),
                     std::min({ta.z(), tb.z(), tc.z()})),
        max = Vec3f(std::max({ta.x(), tb.x(), tc.x()}),
                    std::max({ta.y(), tb.y(), tc.y()}),
                    std::max({ta.z(), tb.z(), tc.z()}));
    auto iMin = (int) floor((min.x() - pMin.x()) / voxel.x()),
            iMax = (int) ceil((max.x() - pMin.x()) / voxel.x()),
            jMin = (int) floor((min.y() - pMin.y()) / voxel.y()),
            jMax = (int) ceil((max.y() - pMin.y()) / voxel.y()),
            kMin = (int) floor((min.z() - pMin.z()) / voxel.z()),
            kMax = (int) ceil((max.z() - pMin.z()) / voxel.z());
    for (int i = std::max(iMin, 0); i <= std::min(iMax, nx - 1); i++) {
        for (int j = std::max(jMin, 0); j <= std::min(jMax, ny - 1); j++) {
            for (int k = std::max(kMin, 0); k <= std::min(kMax, nz - 1); k++) {
                g->insertObject(i, j, k, this);
            }
        }
    }
}