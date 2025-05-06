# include "grid.h"
# include "rayTree.h" 


void Grid::paint() {
    auto bMin = boundingBox->getMin();
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (!occupied(i, j, k)) continue;
                std::array<Vec3f, 8> vertices = getVoxelVertices(i, j, k);
                Vec3f p1 = vertices[0];
                Vec3f p2 = vertices[1];
                Vec3f p3 = vertices[2];
                Vec3f p4 = vertices[3];
                Vec3f p5 = vertices[4];
                Vec3f p6 = vertices[5];
                Vec3f p7 = vertices[6];
                Vec3f p8 = vertices[7];

                glBegin(GL_QUADS);

                
                if (k == 0 || !occupied(i, j, k - 1))
                {
                    glNormal3f(0, 0, -1);
                    glVertex3f(p1.x(), p1.y(), p1.z());
                    glVertex3f(p2.x(), p2.y(), p2.z());
                    glVertex3f(p3.x(), p3.y(), p3.z());
                    glVertex3f(p4.x(), p4.y(), p4.z());
                }

                if (k == nz - 1 || !occupied(i, j, k + 1))
                {
                    glNormal3f(0, 0, 1);
                    glVertex3f(p5.x(), p5.y(), p5.z());
                    glVertex3f(p6.x(), p6.y(), p6.z());
                    glVertex3f(p7.x(), p7.y(), p7.z());
                    glVertex3f(p8.x(), p8.y(), p8.z());
                }

                if (j == 0 || !occupied(i, j - 1, k))
                {
                    glNormal3f(0, -1, 0);
                    glVertex3f(p1.x(), p1.y(), p1.z());
                    glVertex3f(p2.x(), p2.y(), p2.z());
                    glVertex3f(p6.x(), p6.y(), p6.z());
                    glVertex3f(p5.x(), p5.y(), p5.z());
                }

                if (j == ny - 1 || !occupied(i, j + 1, k))
                {
                    glNormal3f(0, 1, 0);
                    glVertex3f(p3.x(), p3.y(), p3.z());
                    glVertex3f(p4.x(), p4.y(), p4.z());
                    glVertex3f(p8.x(), p8.y(), p8.z());
                    glVertex3f(p7.x(), p7.y(), p7.z());
                }

                if (i == 0 || !occupied(i - 1, j, k))
                {
                    glNormal3f(-1, 0, 0);
                    glVertex3f(p1.x(), p1.y(), p1.z());
                    glVertex3f(p4.x(), p4.y(), p4.z());
                    glVertex3f(p8.x(), p8.y(), p8.z());
                    glVertex3f(p5.x(), p5.y(), p5.z());
                }

                if (i == nx - 1 || !occupied(i + 1, j, k))
                {
                    glNormal3f(1, 0, 0);
                    glVertex3f(p2.x(), p2.y(), p2.z());
                    glVertex3f(p3.x(), p3.y(), p3.z());
                    glVertex3f(p7.x(), p7.y(), p7.z());
                    glVertex3f(p6.x(), p6.y(), p6.z());
                }

                glEnd();
                //glFlush();
            }
        }
    }
}

void Grid::hitFace (BoundingBox *bb, MarchingInfo &mi, int ret,
                    Vec3f &p1, Vec3f &p2, Vec3f &p3, Vec3f &p4, Vec3f &normal)
{
    
    Vec3f min = bb->getMin();
    int i = mi.i, j = mi.j, k = mi.k;
    if (ret == 0)
    {
        if (mi.signX < 0) i++;
        p1 = min + Vec3f(i*dx, j*dy, k*dz);
        p2 = min + Vec3f(i*dx, j*dy, (k+1)*dz);
        p3 = min + Vec3f(i*dx, (j+1)*dy, (k+1)*dz);
        p4 = min + Vec3f(i*dx, (j+1)*dy, k*dz);
        normal.Set(1,0,0);
    }
    else if (ret == 1)
    {
        if (mi.signY < 0) j++;
        p1 = min + Vec3f(i*dx, j*dy, k*dz);
        p2 = min + Vec3f((i+1)*dx, j*dy, k*dz);
        p3 = min + Vec3f((i+1)*dx, j*dy, (k+1)*dz);
        p4 = min + Vec3f(i*dx, j*dy, (k+1)*dz);
        normal.Set(0,1,0);
    }
    else if (ret == 2)
    {
        if (mi.signZ < 0) k++;
        p1 = min + Vec3f(i*dx, j*dy, k*dz);
        p2 = min + Vec3f((i+1)*dx, j*dy, k*dz);
        p3 = min + Vec3f((i+1)*dx, (j+1)*dy, k*dz);
        p4 = min + Vec3f(i*dx, (j+1)*dy, k*dz);
        normal.Set(0,0,1);
    }
    
}

int Grid::initializeRayMarch(MarchingInfo &mi, const Ray &r, float tmin) const
{
    int ret; //代表光线从哪个方向的面进入
    Vec3f rayDir = r.getDirection();
    Vec3f rayOrigin = r.getOrigin();

    Vec3f pMin = boundingBox->getMin();
    Vec3f pMax = boundingBox->getMax();

    //平行的情况
    for (int i = 0; i < 3; i++)
    {
        if(rayDir[i] == 0 && (rayOrigin[i] < pMin[i] || rayOrigin[i] > pMax[i]))
        {
            mi.valid = false;
            return -1;
        }
    }

    float tNear,tFar;
    for (int i = 0; i < 3; i++)
    {
        float t1 = (pMin[i] - rayOrigin[i]) / rayDir[i];
        float t2 = (pMax[i] - rayOrigin[i]) / rayDir[i];
        if(t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }
        if (i == 0 || tNear < t1)
        {
            tNear = t1;
            ret = i;
        }
        if (i == 0 || tFar > t2)
        {
            tFar = t2;
        }
    }

    if (tNear > tFar || tFar < tmin)
    {
        mi.valid = false;
        return -1;
    }

    mi.valid = true;

    mi.dTx = std::abs(dx / rayDir.x());
    mi.dTy = std::abs(dy / rayDir.y());
    mi.dTz = std::abs(dz / rayDir.z());

    mi.signX = rayDir.x() < 0 ? -1 : 1;
    mi.signY = rayDir.y() < 0 ? -1 : 1;
    mi.signZ = rayDir.z() < 0 ? -1 : 1;

    //光线起始点在外面
    if (tNear > tmin)
    {
        mi.tMin = tNear;
    }
    //光线起始点在内部
    else
    {
        mi.tMin = tmin;
        ret = -1;
    }

    Vec3f p = rayOrigin + mi.tMin * rayDir - pMin;
    mi.i = std::min((int) (p.x() / dx), nx - 1);
    mi.j = std::min((int) (p.y() / dy), ny - 1);
    mi.k = std::min((int) (p.z() / dz), nz - 1);

    mi.tNextX  = ((mi.i + (mi.signX < 0 ? 0 : 1)) * dx + pMin.x() - rayOrigin.x()) / rayDir.x();
    mi.tNextY  = ((mi.j + (mi.signY < 0 ? 0 : 1)) * dy + pMin.y() - rayOrigin.y()) / rayDir.y();
    mi.tNextZ  = ((mi.k + (mi.signZ < 0 ? 0 : 1)) * dz + pMin.z() - rayOrigin.z()) / rayDir.z();

    mi.grid = const_cast<Grid*>(this);

    return ret;
}

int MarchingInfo::nextCell()
{
    int ret;
    tMin = std::min({tNextX, tNextY, tNextZ});
    if (tMin == tNextX)
    {
        tNextX += dTx;
        i += signX;
        ret = 0;
    }
    else if (tMin == tNextY)
    {
        tNextY += dTy;
        j += signY;
        ret = 1;
    }
    else 
    {
        tNextZ += dTz;
        k += signZ;
        ret = 2;
    }

    int nx, ny, nz;
    std::tie(nx, ny, nz) = grid->getGridSize();
    //auto [nx, ny, nz] = grid->getGridSize();
    if ((i < 0 || i >= nx) || (j < 0 || j >= ny) || (k < 0 || k >= nz))
    {
        valid = false;
    }
    return ret;
}

bool Grid::intersect(const Ray &r, Hit &h, float tMin)
{
    Material* m = new PhongMaterial(
        {1,1,1},{0,0,0},1,
        {0,0,0},{0,0,0},1
    );
    MarchingInfo mi;
    int ret = initializeRayMarch(mi, r, tMin);
    while (mi.valid && !occupied(mi.i, mi.j, mi.k))
    {
        Vec3f p1, p2, p3, p4, normal;
        hitFace(boundingBox, mi, ret, p1, p2, p3, p4, normal);
        if (r.getDirection().Dot3(normal) > 0)  normal.Negate();
        
        RayTree::AddHitCellFace(p1, p2, p3, p4, normal, m);
        ret = mi.nextCell();
    }
    if (mi.valid)
    {
        Vec3f p1, p2, p3, p4, normal;
        hitFace(boundingBox, mi, ret, p1, p2, p3, p4, normal);
        if (r.getDirection().Dot3(normal) > 0)  normal.Negate();
        m->setDiffuseColor(getColor(mi.i, mi.j, mi.k));
        RayTree::AddEnteredFace(p1, p2, p3, p4, normal, m);
        h.set(mi.tMin, m, normal,r);
        return true;
    }
    return false;
}