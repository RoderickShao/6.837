#include "material.h"
#include <windows.h>
#include <gl/GL.h>


 Vec3f PhongMaterial::Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const 
 {
    Vec3f n = hit.getNormal();
    Vec3f Ld = lightColor * diffuseColor * n.Dot3(dirToLight);

    Vec3f direction = ray.getDirection();
    direction.Scale(-1,-1,-1);
    Vec3f h = dirToLight + direction;
    h.Normalize();
    Vec3f Ls = lightColor * specularColor * pow(n.Dot3(h), exponent);

    return Ld + Ls;
 }

void PhongMaterial::glSetMaterial() const {

    GLfloat one[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat zero[4] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat specular[4] = {
            specularColor.r(),
            specularColor.g(),
            specularColor.b(),
            1.0};
    GLfloat diffuse[4] = {
            diffuseColor.r(),
            diffuseColor.g(),
            diffuseColor.b(),
            1.0};

    // NOTE: GL uses the Blinn Torrance version of Phong...
    float glexponent = exponent;
    if (glexponent < 0) glexponent = 0;
    if (glexponent > 128) glexponent = 128;

#if !SPECULAR_FIX

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &glexponent);

#else

    // OPTIONAL: 3 pass rendering to fix the specular highlight
  // artifact for small specular exponents (wide specular lobe)

  if (SPECULAR_FIX_WHICH_PASS == 0) {
    // First pass, draw only the specular highlights
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &glexponent);

  } else if (SPECULAR_FIX_WHICH_PASS == 1) {
    // Second pass, compute normal dot light
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, one);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);
  } else {
    // Third pass, add ambient & diffuse terms
    assert (SPECULAR_FIX_WHICH_PASS == 2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);
  }

#endif
}

bool odd (int i, int j, int k)
{
  return (i + j + k) % 2;
}

Vec3f Checkerboard::Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const 
{
    Vec3f p = hit.getIntersectionPoint();
    return getMaterialByPoint(p)->Shade(ray, hit, dirToLight, lightColor);
}

Vec3f Noise::Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const 
{ 
    Vec3f p = hit.getIntersectionPoint();
    m->Transform(p);
    float N =0;
    for (int i = 0; i < octaves; i++)
    {
        float oct = pow(2, i);
        N += PerlinNoise::noise(p.x() * oct, p.y() * oct, p.z() * oct) / oct;
    }
    
    return mat1->Shade(ray, hit, dirToLight, lightColor) * (N) + mat2->Shade(ray, hit, dirToLight, lightColor) * (1-N);
}

Vec3f Marble::Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const 
{
    Vec3f p = hit.getIntersectionPoint();
    m->Transform(p);
    float N;
    for (int i = 0; i < octaves; i++)
    {
        float oct = pow(2, i);
        N += PerlinNoise::noise(p.x() * oct, p.y() * oct, p.z() * oct) / oct;
    }
    float M = sin(frequency * p.x() + amplitude * N) ;

    M = (M+1)/2;

    return mat1->Shade(ray, hit, dirToLight, lightColor) * M + mat2->Shade(ray, hit, dirToLight, lightColor) * (1-M);
}

Vec3f Wood::Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const 
{
    Vec3f p = hit.getIntersectionPoint();
    m->Transform(p);
    float N;
    for (int i = 0; i < octaves; i++)
    {
        float oct = pow(2, i);
        N += PerlinNoise::noise(p.x() * oct, p.y() * oct, p.z() * oct) / oct;
    }

    float l = sqrt(p.x() * p.x() + p.z() * p.z());

    float M = sin(frequency * l + amplitude * N) ;

    M = (M+1)/2;

    return mat1->Shade(ray, hit, dirToLight, lightColor) * M + mat2->Shade(ray, hit, dirToLight, lightColor) * (1-M);    
}