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