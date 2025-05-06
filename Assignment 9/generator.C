#include "generator.h"
#include <chrono>
Particle* HoseGenerator::Generate(float current_time, float dt, int i){
    Random rand(int(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    Vec3f pos = position + rand.randomVector() * position_randomness;
    Vec3f vel = velocity + rand.randomVector() * velocity_randomness;
    Vec3f col = color + rand.randomVector() * colorRandomness;
    col.Clamp();
    Vec3f dead_col = deadColor + rand.randomVector() * colorRandomness;
    dead_col.Clamp();
    float m = mass + rand.next() * massRandomness;
    float lifespan = this->lifespan + rand.next() * lifespanRandomness;
    return new Particle(pos, vel, col, dead_col, m, lifespan);
}

Particle* RingGenerator::Generate(float current_time, float dt, int i){

    Random rand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    Vec3f col = color + rand.randomVector() * colorRandomness;
    col.Clamp();
    Vec3f dead_col = deadColor + rand.randomVector() * colorRandomness;
    dead_col.Clamp();
    float m = mass + rand.next() * massRandomness;
    float lifespan = this->lifespan + rand.next() * lifespanRandomness;

    float radius = current_time;
    int numP = numNewParticles(current_time, dt);
    float theta = float (i) * 2 * M_PI / numP;

    Vec3f pos = Vec3f(radius * cos(theta), 0, radius * sin(theta));
    pos += pos + rand.randomVector() * position_randomness;
    Vec3f vel = velocity + rand.randomVector() * velocity_randomness;

    return new Particle(pos, vel, col, dead_col, m, lifespan);
}