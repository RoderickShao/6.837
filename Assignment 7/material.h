#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vectors.h"
#include "glCanvas.h"
#include "ray.h"
#include "hit.h"
#include "matrix.h"
#include "perlin_noise.h"

// include glCanvas.h to access the preprocessor variable SPECULAR_FIX
#include "glCanvas.h"

#ifdef SPECULAR_FIX
// OPTIONAL:  global variable allows (hacky) communication
// with glCanvas::display
extern int SPECULAR_FIX_WHICH_PASS;
#endif

// ====================================================================
// ====================================================================

// You will extend this class in later assignments

class Material {

public:

  // CONSTRUCTORS & DESTRUCTOR
  Material(const Vec3f &d_color) { diffuseColor = d_color; }
  virtual ~Material() {}

  // ACCESSORS
  virtual Vec3f getDiffuseColor(const Vec3f &p) const { return diffuseColor; }

  virtual void setDiffuseColor(const Vec3f &color) { diffuseColor = color; }

  virtual void glSetMaterial(void) const = 0;

  virtual Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const = 0;

protected:

  // REPRESENTATION
  Vec3f diffuseColor;
  
};

// ====================================================================
// ====================================================================

class PhongMaterial : public Material {
  public:
    PhongMaterial(const Vec3f &diffuseColor, const Vec3f &specularColor, float exponent, const Vec3f &reflectiveColor,const Vec3f &transparentColor, float indexOfRefraction): Material(diffuseColor) {
        this->specularColor = specularColor;
        this->exponent = exponent;
        this->reflectiveColor = reflectiveColor;
        this->transparentColor = transparentColor;
        this->indexOfRefraction = indexOfRefraction;
    }

    ~PhongMaterial() {}

    void glSetMaterial(void) const override;
     
    virtual Vec3f getSpecularColor(const Vec3f &p) const { return specularColor; }

    virtual Vec3f getreflectiveColor(const Vec3f &p) const { return reflectiveColor; }

    virtual Vec3f gettransparentColor(const Vec3f &p) const { return transparentColor; }

    virtual float getindexOfRefraction(const Vec3f &p) const { return indexOfRefraction; }

    Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const override;

  protected:
    Vec3f specularColor;
    float exponent;
    Vec3f reflectiveColor;
    Vec3f transparentColor;
    float indexOfRefraction;
};

class Checkerboard : public PhongMaterial {
  public:
    Checkerboard(Matrix *m, Material *mat1, Material *mat2): 
    PhongMaterial(Vec3f(0, 0, 0), Vec3f(0, 0, 0), 0, Vec3f(0, 0, 0), Vec3f(0, 0, 0), 0),
      mat1(mat1), mat2(mat2), m(m) {}

    ~Checkerboard() { delete mat1; delete mat2; delete m; }

    Material *getMaterialByPoint(const Vec3f &_p) const {
      Vec3f p = _p;
      m->Transform(p);
      auto px = (int) floor(p.x()), py = (int) floor(p.y()), pz = (int) floor(p.z());
      auto oddCount = (px % 2) + (py % 2) + (pz % 2);
      if (oddCount % 2 == 0) {
          return mat1;
      } else {
          return mat2;
      }
    }

    Vec3f getDiffuseColor(const Vec3f &p) const override
    {
      Material *mat = getMaterialByPoint(p);
      return mat->getDiffuseColor(p);
    }

    Vec3f getSpecularColor(const Vec3f &p) const override
    {
      Material *mat = getMaterialByPoint(p);
      auto pMat = dynamic_cast<PhongMaterial *>(mat);
      if (pMat == nullptr) {
          return {0, 0, 0};
      } else {
          return pMat->getSpecularColor(p);
      }
    }

    Vec3f getreflectiveColor(const Vec3f &p) const override
    {
      Material *mat = getMaterialByPoint(p);
      auto pMat = dynamic_cast<PhongMaterial *>(mat);
      if (pMat == nullptr) {
          return {0, 0, 0};
      } else {
          return pMat->getreflectiveColor(p);
      }
    }

    Vec3f gettransparentColor(const Vec3f &p) const override
    {
      Material *mat = getMaterialByPoint(p);
      auto pMat = dynamic_cast<PhongMaterial *>(mat);
      if (pMat == nullptr) {
          return {0, 0, 0};
      } else {
          return pMat->gettransparentColor(p);
      }
    }

    float getindexOfRefraction(const Vec3f &p) const override
    {
      Material *mat = getMaterialByPoint(p);
      auto pMat = dynamic_cast<PhongMaterial *>(mat);
      if (pMat == nullptr) {
          return 1;
      } else {
          return pMat->getindexOfRefraction(p);
      }
    }

    void glSetMaterial(void) const override
    {
      mat1->glSetMaterial();
    }

    Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const override;

  private:
    Material* mat1;
    Material* mat2;
    Matrix* m;
};

class Noise : public Material {
  public:
    Noise(Matrix *m, Material *mat1, Material *mat2, int octaves): Material(mat1->getDiffuseColor(Vec3f(0, 0, 0))), 
      octaves(octaves), m(m), mat1(mat1), mat2(mat2) {}

    ~Noise() { delete mat1; delete mat2; delete m; }

    void glSetMaterial(void) const override
    {
      mat1->glSetMaterial();
    }

    Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const override;

  private:
    int octaves;
    Matrix *m;
    Material *mat1;
    Material *mat2;
};

class Marble : public Material{
  public:
    Marble(Matrix *m, Material *mat1, Material *mat2, int octaves, float frequency, float amplitude): Material(mat1->getDiffuseColor(Vec3f(0, 0, 0))), 
      octaves(octaves), frequency(frequency), amplitude(amplitude), m(m), mat1(mat1), mat2(mat2) {}
    
    void glSetMaterial(void) const override
    {
      mat1->glSetMaterial();
    } 

    Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const override;

  private:
    int octaves;
    float frequency;
    float amplitude;
    Matrix *m;
    Material *mat1;
    Material *mat2;
};

class Wood : public Material{
  public:
    Wood(Matrix *m, Material *mat1, Material *mat2, int octaves, float frequency, float amplitude): Material(Vec3f(0, 0, 0)), 
      octaves(octaves), frequency(frequency), amplitude(amplitude), m(m), mat1(mat1), mat2(mat2) {}
    
    void glSetMaterial(void)const override{
      mat1->glSetMaterial();
    }

    Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const override;
  
  private:
    int octaves;
    float frequency;
    float amplitude;
    Matrix *m;
    Material *mat1;
    Material *mat2;
};

#endif