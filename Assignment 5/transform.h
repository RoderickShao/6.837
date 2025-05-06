# ifndef ASSIGNMENT2_TRANSFORM_H
# define ASSIGNMENT2_TRANSFORM_H

# include "object3d.h"
# include "matrix.h"

float min_4(float a, float b, float c, float d);
float max_4(float a, float b, float c, float d);
float min_8(float a, float b, float c, float d, float e, float f, float g, float h);
float max_8(float a, float b, float c, float d, float e, float f, float g, float h);

class Transform : public Object3D {
    public:
        Transform(Matrix m,Object3D *object) : object(object), m(m) {
            m.Inverse(mInv);
            mInv.Transpose(mInvT);

            BoundingBox* bbox = object->getBoundingBox();
            Vec3f v0 = Vec3f (bbox->getMin().x(), bbox->getMin().y(), bbox->getMin().z());
            Vec3f v1 = Vec3f (bbox->getMin().x(), bbox->getMin().y(), bbox->getMax().z());
            Vec3f v2 = Vec3f (bbox->getMin().x(), bbox->getMax().y(), bbox->getMin().z());
            Vec3f v3 = Vec3f (bbox->getMin().x(), bbox->getMax().y(), bbox->getMax().z());
            Vec3f v4 = Vec3f (bbox->getMax().x(), bbox->getMin().y(), bbox->getMin().z());
            Vec3f v5 = Vec3f (bbox->getMax().x(), bbox->getMin().y(), bbox->getMax().z());
            Vec3f v6 = Vec3f (bbox->getMax().x(), bbox->getMax().y(), bbox->getMin().z());
            Vec3f v7 = Vec3f (bbox->getMax().x(), bbox->getMax().y(), bbox->getMax().z());
            
            v0 = transformPosition(v0,m);
            v1 = transformPosition(v1,m);
            v2 = transformPosition(v2,m);
            v3 = transformPosition(v3,m);
            v4 = transformPosition(v4,m);
            v5 = transformPosition(v5,m);
            v6 = transformPosition(v6,m);
            v7 = transformPosition(v7,m);
            Vec3f min = Vec3f(min_8(v0.x(),v1.x(),v2.x(),v3.x(),v4.x(),v5.x(),v6.x(),v7.x()),
                              min_8(v0.y(),v1.y(),v2.y(),v3.y(),v4.y(),v5.y(),v6.y(),v7.y()),
                              min_8(v0.z(),v1.z(),v2.z(),v3.z(),v4.z(),v5.z(),v6.z(),v7.z()));
            Vec3f max = Vec3f(max_8(v0.x(),v1.x(),v2.x(),v3.x(),v4.x(),v5.x(),v6.x(),v7.x()),
                              max_8(v0.y(),v1.y(),v2.y(),v3.y(),v4.y(),v5.y(),v6.y(),v7.y()),
                              max_8(v0.z(),v1.z(),v2.z(),v3.z(),v4.z(),v5.z(),v6.z(),v7.z()));
            
            boundingBox = new BoundingBox(min,max);
        }

        Vec3f transformPosition(const Vec3f &v, const Matrix m) const;
        bool intersect (const Ray &r, Hit &h, float tmin) override;
        void paint() override;

        void insertIntoGrid(Grid *g, Matrix *m) override {
            auto nowmat = Matrix(this->m);
            if (m != nullptr) {
                nowmat = (*m) * nowmat;
            }
            object->insertIntoGrid(g, &nowmat);
        }
    private:
        Object3D *object;
        Matrix m,mInv,mInvT;
};

# endif