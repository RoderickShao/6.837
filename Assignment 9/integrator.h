#ifndef ASSIGNMENT9_INTEGRATOR_H
#define ASSIGNMENT9_INTEGRATOR_H

# include "particle.h"
# include "forcefield.h"

class Integrator {
    public:
        virtual void Update(Particle *p, ForceField *forcefield, float t, float dt) = 0;

        virtual Vec3f getColor() = 0;
};

class EulerIntegrator : public Integrator {
    public:
        void Update(Particle *p, ForceField *forcefield, float t, float dt);

        Vec3f getColor() { return Vec3f(1, 0, 0); }
};

class MidpointIntegrator : public Integrator {
    public:
        void Update(Particle *p, ForceField *forcefield, float t, float dt);

        Vec3f getColor() { return Vec3f(0, 1, 0);}    
};

class RungeKuttaIntegrator : public Integrator {
    public:
        void Update(Particle *p, ForceField *forcefield, float t, float dt);

        Vec3f getColor() { return Vec3f(0, 0, 1); }
};

#endif