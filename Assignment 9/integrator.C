# include "integrator.h"

void EulerIntegrator::Update(Particle *p, ForceField *forcefield, float t, float dt)
{
    Vec3f pn = p->getPosition();
    Vec3f vn = p->getVelocity();
    Vec3f acceleration = forcefield->getAcceleration(pn, p->getMass(), t);
    Vec3f new_velocity = vn + acceleration * dt;
    Vec3f new_position = pn + vn * dt;
    p->setVelocity(new_velocity);
    p->setPosition(new_position);
    p->increaseAge(dt);
}

void MidpointIntegrator::Update(Particle *p, ForceField *forcefield, float t, float dt)
{
    Vec3f acceleration = forcefield->getAcceleration(p->getPosition(), p->getMass(), t);
    Vec3f m_velocity = p->getVelocity() + acceleration * dt * 0.5;
    Vec3f m_position = p->getPosition() + p->getVelocity() * dt * 0.5;
    acceleration = forcefield->getAcceleration(m_position, p->getMass(), t + dt * 0.5);
    Vec3f new_velocity = p->getVelocity() + acceleration * dt;
    Vec3f new_position = p->getPosition() + m_velocity * dt;

    p->setVelocity(new_velocity);
    p->setPosition(new_position);
    p->increaseAge(dt);
}
void RungeKuttaIntegrator::Update(Particle *p, ForceField *forcefield, float t, float dt)
{
    Vec3f pos = p->getPosition();
    Vec3f vel = p->getVelocity();
    float mass = p->getMass();

    // 计算加速度
    auto getAcceleration = [&](const Vec3f& position, const Vec3f& velocity, float time) {
        return forcefield->getAcceleration(position, mass, time);
    };

    // 计算 k1
    Vec3f k1_v = getAcceleration(pos, vel, t) * dt;
    Vec3f k1_x = vel * dt;

    // 计算 k2
    Vec3f k2_v = getAcceleration(pos + k1_x * 0.5f, vel + k1_v * 0.5f, t + dt * 0.5f) * dt;
    Vec3f k2_x = (vel + k1_v * 0.5f) * dt;

    // 计算 k3
    Vec3f k3_v = getAcceleration(pos + k2_x * 0.5f, vel + k2_v * 0.5f, t + dt * 0.5f) * dt;
    Vec3f k3_x = (vel + k2_v * 0.5f) * dt;

    // 计算 k4
    Vec3f k4_v = getAcceleration(pos + k3_x, vel + k3_v, t + dt) * dt;
    Vec3f k4_x = (vel + k3_v) * dt;

    // 更新位置和速度
    Vec3f new_position = pos + (k1_x + 2.0f * k2_x + 2.0f * k3_x + k4_x) *(1 / 6.0f);
    Vec3f new_velocity = vel + (k1_v + 2.0f * k2_v + 2.0f * k3_v + k4_v) *(1 / 6.0f);

    p->setPosition(new_position);
    p->setVelocity(new_velocity);
    p->increaseAge(dt);
}