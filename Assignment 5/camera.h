#ifndef ASSIGNMENT1_CAMERA_H
#define ASSIGNMENT1_CAMERA_H

#include "ray.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>

class Camera {
public:
    virtual Ray generateRay(Vec2f point) = 0;
    virtual float getTMin() const = 0;
    virtual void glInit(int w, int h) = 0;
    virtual void glPlaceCamera(void) = 0;
    virtual void dollyCamera(float dist) = 0;
    virtual void truckCamera(float dx, float dy) = 0;
    virtual void rotateCamera(float rx, float ry) = 0;
};

class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(const Vec3f &center, const Vec3f &direction, const Vec3f &up, float size)
        {
            this->center = center;

            this->direction = direction;
            this->direction.Normalize();
            
            Vec3f::Cross3(this->horizontal, direction, up);
                this->horizontal.Normalize();

            Vec3f::Cross3(this->up, this->horizontal, direction);
                this->up.Normalize();

            this->size = size;
        }
        Ray generateRay(Vec2f point) override;
        float getTMin() const override;
        
        void glInit(int w, int h) override;
        void glPlaceCamera(void) override;
        void dollyCamera(float dist) override;
        void truckCamera(float dx, float dy) override;
        void rotateCamera(float rx, float ry) override;

    private:
        Vec3f center,up,direction,horizontal;
        float size;
};

class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(const Vec3f &center, const Vec3f &direction, const Vec3f &up, float angle)
        {
            this->center = center;

            this->direction = direction;
            this->direction.Normalize();
            
            Vec3f::Cross3(this->horizontal, direction, up);
            this->horizontal.Normalize();

            Vec3f::Cross3(this->up, this->horizontal, direction);
            this->up.Normalize();

            this->angle = angle;

            side = tan(angle/2)*2;
        }

        Ray generateRay(Vec2f point) override;
        float getTMin() const override;
        void glInit(int w, int h) override;
        void glPlaceCamera(void) override;
        void dollyCamera(float dist) override;
        void truckCamera(float dx, float dy) override;
        void rotateCamera(float rx, float ry) override;

    private:
        Vec3f center,up,direction,horizontal;
        float angle,side;
};

#endif