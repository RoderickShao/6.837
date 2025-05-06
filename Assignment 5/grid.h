# ifndef ASSIGNMENT5_GRID_H
# define ASSIGNMENT5_GRID_H

# include "object3d.h"
# include "object3dvector.h"

# include <tuple>
# include <array>
# include <algorithm>

class MarchingInfo;

class Grid : public Object3D {
    public:
        Grid(BoundingBox *bb, int nx, int ny, int nz){
            this->boundingBox = bb;
            this->nx = nx;
            this->ny = ny;
            this->nz = nz;
            dx = (bb->getMax().x() - bb->getMin().x()) / nx;
            dy = (bb->getMax().y() - bb->getMin().y()) / ny;
            dz = (bb->getMax().z() - bb->getMin().z()) / nz;
            
            //isopaque = new bool[nx * ny * nz];
            //for (int i = 0; i < nx * ny * nz; i++) {
            //    isopaque[i] = false;
            //}

            objects = new Object3DVector[nx * ny * nz];
        }

        ~Grid() {
            delete[] objects;
        }

        void insertObject(int x, int y, int z, Object3D *obj) {
            assert(x>=0&&x<nx);
            assert(y>=0&&y<ny);
            assert(z>=0&&z<nz);
            objects[x * ny * nz + y * nz + z].addObject(obj);
        }

        bool intersect(const Ray &r, Hit &h, float tMin) override;

        void paint() override;

        std::tuple<int, int, int> getGridSize() {
            return {nx, ny, nz};
        }

        Vec3f getVoxelSize() {
            return {dx, dy, dz};
        }

        Vec3f getVoxelCenter(int i, int j, int k) {
            return Vec3f(boundingBox->getMin().x() + (i + 0.5) * dx,
                         boundingBox->getMin().y() + (j + 0.5) * dy,
                         boundingBox->getMin().z() + (k + 0.5) * dz);
        }

        std::array<Vec3f, 8> getVoxelVertices(int i, int j, int k) {
            auto bMin = boundingBox->getMin();
            auto p1 = bMin + Vec3f(i * dx, j * dy, k * dz),
                    p2 = bMin + Vec3f((i + 1) * dx, j * dy, k * dz),
                    p3 = bMin + Vec3f((i + 1) * dx, (j + 1) * dy, k * dz),
                    p4 = bMin + Vec3f(i * dx, (j + 1) * dy, k * dz),
                    p5 = bMin + Vec3f(i * dx, j * dy, (k + 1) * dz),
                    p6 = bMin + Vec3f((i + 1) * dx, j * dy, (k + 1) * dz),
                    p7 = bMin + Vec3f((i + 1) * dx, (j + 1) * dy, (k + 1) * dz),
                    p8 = bMin + Vec3f(i * dx, (j + 1) * dy, (k + 1) * dz);
            return {p1, p2, p3, p4, p5, p6, p7, p8};
        }

        Vec3f getMin() const {
            return boundingBox->getMin();
        }

        int numObjects(int i, int j, int k) {
            assert(i >= 0 && i < nx);
            assert(j >= 0 && j < ny);
            assert(k >= 0 && k < nz);
            return objects[i * ny * nz + j * nz + k].getNumObjects();
        }

        Vec3f getColor(int i, int j, int k) {
            assert(i >= 0 && i < nx);
            assert(j >= 0 && j < ny);
            assert(k >= 0 && k < nz);
            int n = numObjects(i, j, k);
        
            switch (n) {
                case 1:
                    return Vec3f(1, 1, 1); // 白
                case 2:
                    return Vec3f(1, 0.9, 0.6); // 浅黄
                case 3:
                    return Vec3f(1, 0.7, 0.4); // 橙黄
                case 4:
                    return Vec3f(0.6, 0.4, 0.8); // 紫
                case 5:
                    return Vec3f(0.4, 0.6, 1); // 蓝
                case 6:
                    return Vec3f(0.4, 1, 1); // 青
                case 7:
                    return Vec3f(0.4, 1, 0.4); // 绿
                case 8:
                    return Vec3f(1, 1, 0.4); // 黄
                case 9:
                    return Vec3f(1, 0.6, 0.4); // 橙
                case 10:
                    return Vec3f(1, 0.4, 0.4); // 红
                case 11:
                    return Vec3f(0.9, 0.9, 0.9); // 浅灰
                case 12:
                    return Vec3f(0.8, 0.8, 0.2); // 浅黄绿
                case 13:
                    return Vec3f(0.6, 0.6, 0.2); // 橙黄绿
                case 14:
                    return Vec3f(0.5, 0.2, 0.5); // 深紫
                case 15:
                    return Vec3f(0.2, 0.2, 1); // 深蓝
                case 16:
                    return Vec3f(0.2, 1, 1); // 深青
                case 17:
                    return Vec3f(0.2, 1, 0.2); // 深绿
                case 18:
                    return Vec3f(1, 1, 0.2); // 浅黄
                case 19:
                    return Vec3f(1, 0.5, 0.2); // 浅橙
                case 20:
                    return Vec3f(1, 0.2, 0.2); // 浅红
                default:
                    return Vec3f(1, 0, 0); // 默认红色
            }
        }
        /*
        void setOpaque(int i, int j, int k) {
            isopaque[i * ny * nz + j * nz + k] = true;
        }

        bool isOpaque(int i, int j, int k) {
            return isopaque[i * ny * nz + j * nz + k];
        }
        */

        bool occupied(int i, int j, int k) {
            assert (i >=0 && i< nx);
            assert (j >=0 && j< ny);
            assert (k >=0 && k< nz);
            return objects[i * ny * nz + j * nz + k].getNumObjects()>0;

        }

        int initializeRayMarch(MarchingInfo &mi, const Ray &r, float tmin) const;

        void hitFace (BoundingBox *bb, MarchingInfo &mi, int ret,
                    Vec3f &p1, Vec3f &p2, Vec3f &p3, Vec3f &p4, Vec3f &normal);

    protected:
        int nx, ny, nz;
        float dx, dy, dz;
        //bool *isopaque;
        Object3DVector *objects;
};

class MarchingInfo{
public:
    float tMin;
    int i,j,k;
    float tNextX, tNextY, tNextZ;
    float dTx, dTy, dTz;
    int signX, signY, signZ;

    Grid* grid;
    bool valid;
    
    int nextCell();
};

# endif //ASSIGNMENT5_GRID