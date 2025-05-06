# include "camera.h"
# include "vectors.h"
# include "matrix.h"

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

void OrthographicCamera::glInit(int w, int h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w > h)
    glOrtho(-size/2.0, size/2.0, -size*(float)h/(float)w/2.0, size*(float)h/(float)w/2.0, 0.5, 40.0);
  else
    glOrtho(-size*(float)w/(float)h/2.0, size*(float)w/(float)h/2.0, -size/2.0, size/2.0, 0.5, 40.0);
}

void OrthographicCamera::glPlaceCamera(void)
{
  gluLookAt(center.x(), center.y(), center.z(),
            center.x()+direction.x(), center.y()+direction.y(), center.z()+direction.z(),
            up.x(), up.y(), up.z());
}

void OrthographicCamera::dollyCamera(float dist)
{
  center += direction*dist;

  // ===========================================
  // ASSIGNMENT 3: Fix any other affected values
  // ===========================================


}

void OrthographicCamera::truckCamera(float dx, float dy)
{
  center += horizontal*dx + up*dy;

  // ===========================================
  // ASSIGNMENT 3: Fix any other affected values
  // ===========================================
}

void OrthographicCamera::rotateCamera(float rx, float ry)
{
  // Don't let the model flip upside-down (There is a singularity
  // at the poles when 'up' and 'direction' are aligned)
  float tiltAngle = acos(up.Dot3(direction));
  if (tiltAngle-ry > 3.13)
    ry = tiltAngle - 3.13;
  else if (tiltAngle-ry < 0.01)
    ry = tiltAngle - 0.01;

  Matrix rotMat = Matrix::MakeAxisRotation(up, rx);
  rotMat *= Matrix::MakeAxisRotation(horizontal, ry);

  rotMat.Transform(center);
  rotMat.TransformDirection(direction);
  
  // ===========================================
  // ASSIGNMENT 3: Fix any other affected values
  // ===========================================
  rotMat.TransformDirection(up);
  up.Normalize();
  rotMat.TransformDirection(horizontal);
  horizontal.Normalize();
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

void PerspectiveCamera::glInit(int w, int h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angle*180.0/3.14159, (float)w/float(h), 0.5, 40.0);
}

void PerspectiveCamera::glPlaceCamera(void)
{
  gluLookAt(center.x(), center.y(), center.z(),
            center.x()+direction.x(), center.y()+direction.y(), center.z()+direction.z(),
            up.x(), up.y(), up.z());
}

void PerspectiveCamera::dollyCamera(float dist)
{
  center += direction*dist;

  // ===========================================
  // ASSIGNMENT 3: Fix any other affected values
  // ===========================================


}

void PerspectiveCamera::truckCamera(float dx, float dy)
{
  //Vec3f horizontal;
  //Vec3f::Cross3(horizontal, direction, up);
  //horizontal.Normalize();

  //Vec3f screenUp;
 // Vec3f::Cross3(screenUp, horizontal, direction);

  center += horizontal*dx + up*dy;

  // ===========================================
  // ASSIGNMENT 3: Fix any other affected values
  // ===========================================


}

void PerspectiveCamera::rotateCamera(float rx, float ry)
{
  //Vec3f horizontal;
  //Vec3f::Cross3(horizontal, direction, up);
  //horizontal.Normalize();

  // Don't let the model flip upside-down (There is a singularity
  // at the poles when 'up' and 'direction' are aligned)
  float tiltAngle = acos(up.Dot3(direction));
  if (tiltAngle-ry > 3.13)
    ry = tiltAngle - 3.13;
  else if (tiltAngle-ry < 0.01)
    ry = tiltAngle - 0.01;

  Matrix rotMat = Matrix::MakeAxisRotation(up, rx);
  rotMat *= Matrix::MakeAxisRotation(horizontal, ry);

  rotMat.Transform(center);
  rotMat.TransformDirection(direction);
  direction.Normalize();

  // ===========================================
  // ASSIGNMENT 3: Fix any other affected values
  // ===========================================

  rotMat.TransformDirection(up);
  up.Normalize();
  rotMat.TransformDirection(horizontal);
  horizontal.Normalize();
}