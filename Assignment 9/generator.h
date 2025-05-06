#ifndef ASSIGNMENT9_GENERATOR_H
#define ASSIGNMENT9_GENERATOR_H

#include <ctime>
#include <windows.h>
#include <GL/gl.h>

#include <random>
#include "random.h"
#include "particle.h"

class Generator {
    public:
        // initialization

        Generator(){
        
        }
        void SetColors(Vec3f color, Vec3f dead_color, float color_randomness)
        {
            this->color = color;
            this->deadColor = dead_color;
            this->colorRandomness = color_randomness;
        }

        void SetLifespan(float lifespan, float lifespan_randomness, int desired_num_particles)
        {
            this->lifespan = lifespan;
            this->lifespanRandomness = lifespan_randomness;
            this->desiredNumParticles = desired_num_particles;
        }

        void SetMass(float mass, float mass_randomness)
        {
            this->mass = mass;
            this->massRandomness = mass_randomness;
        }

        // on each timestep, create some particles
        virtual int numNewParticles(float current_time, float dt) const {
            return ceil(dt * desiredNumParticles / lifespan );
        }
        virtual Particle* Generate(float current_time, float dt, int i) = 0;

        // for the gui
        virtual void Paint() const{};
        void Restart()
        {}
            


    protected:
        Vec3f color, deadColor;
        float colorRandomness;
        float lifespan, lifespanRandomness;
        int desiredNumParticles;
        float mass, massRandomness;
};

class HoseGenerator : public Generator{
    public:
        HoseGenerator(Vec3f position, float position_randomness, Vec3f velocity, float velocity_randomness): 
            position(position), position_randomness(position_randomness), velocity(velocity), velocity_randomness(velocity_randomness){}

        Particle* Generate(float current_time, float dt, int i) override;

    private:
        Vec3f position;
        float position_randomness;
        Vec3f velocity;
        float velocity_randomness;
};

class RingGenerator : public Generator{
    public:
        RingGenerator(float position_randomness, Vec3f velocity, float velocity_randomness)
            : position_randomness(position_randomness), velocity(velocity), velocity_randomness(velocity_randomness){}

        int numNewParticles(float current_time, float dt) const override
        {
            return ceil(dt * desiredNumParticles / lifespan * current_time);
        }

        Particle* Generate(float current_time, float dt, int i) override;

        void Paint() const override {
            glBegin(GL_QUADS);
            glColor3f(1, 1, 1);
            glNormal3f(0, 0, -1);
            glVertex3f(-100.0f, -1.0f, -100.0f);
            glVertex3f(-100.0f, -1.0f, 100.0f);
            glVertex3f(100.0f, -1.0f, 100.0f);
            glVertex3f(100.0f, -1.0f, -100.0f);
            glEnd();
        }

    private:
        float position_randomness;
        Vec3f velocity;
        float velocity_randomness;
};

#endif