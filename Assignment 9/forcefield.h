#ifndef ASSIGNMENT9_FORCEFIELD_H
#define ASSIGNMENT9_FORCEFIELD_H

#include "vectors.h"

class ForceField {
    public:
        virtual Vec3f getAcceleration(const Vec3f &position, float mass, float t) const = 0;
};

class GravityForceField : public ForceField {
    public:
        GravityForceField(Vec3f gravity) {
            this->gravity = gravity;
        }

        Vec3f getAcceleration(const Vec3f &position, float mass, float t) const override {
            return gravity;
        }

    private:
        Vec3f gravity;
};

class ConstantForceField : public ForceField {
    public:
        ConstantForceField(Vec3f force) {
            this->force = force;
        }

        Vec3f getAcceleration(const Vec3f &position, float mass, float t) const override{
            return force * (1/mass);
        }


    private:
        Vec3f force;
};

class RadialForceField : public ForceField {
    public:
        RadialForceField(float magnitude) {
            this->magnitude = magnitude;
        }

        Vec3f getAcceleration(const Vec3f &position, float mass, float t) const override {
            auto dir = position;
            dir.Normalize();
            dir.Scale(-magnitude / mass, -magnitude / mass, -magnitude / mass);
            return dir ;
        }
    private:
        float magnitude;
};

class VerticalForceField : public ForceField {
    public:
        VerticalForceField(float magnitude) {
            this->magnitude = magnitude;
        }

        Vec3f getAcceleration(const Vec3f &position, float mass, float t) const override {
            return Vec3f(0, -magnitude*position.y(), 0);
        }

    private:
        float magnitude;
};

#endif