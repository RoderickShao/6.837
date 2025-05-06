# include "camera.h"
# include "vectors.h"

# include <cmath>

Ray OrthographicCamera::generateRay(Vec2f point)
{
    point -= Vec2f(0.5, 0.5);
    point *= size;
    return {center + point.x() * horizontal + point.y() * up, direction};
}

float OrthographicCamera::getTMin() const
{
    return -FP_INFINITE ;
}

Ray PerspectiveCamera::generateRay(Vec2f point)
{
    auto pScr = center + direction +
            horizontal * (point.x() - 0.5f) * side + up * (point.y() - 0.5f) * side;
    auto dir = pScr - center;
    dir.Normalize();
    return {center, dir};
}

float PerspectiveCamera::getTMin() const
{
    return 0.0f;
}