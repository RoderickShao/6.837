# ifndef ASSIGNMENT2_TRANSFORM_H
# define ASSIGNMENT2_TRANSFORM_H

# include "object3d.h"
# include "matrix.h"

class Transform : public Object3D {
    public:
        Transform(Matrix m,Object3D *object) : object(object), m(m) {
            m.Inverse(mInv);
            mInv.Transpose(mInvT);
        }
        bool intersect (const Ray &r, Hit &h, float tmin) override;
    private:
        Object3D *object;
        Matrix m,mInv,mInvT;
};

# endif