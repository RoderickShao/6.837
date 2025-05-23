//
// Created by kskun on 2021/10/4.
//

#ifndef ASSIGNMENT1_OBJECT3D_H
#define ASSIGNMENT1_OBJECT3D_H

#include <windows.h>
#include <GL/gl.h>

#include "material.h"
#include "ray.h"
#include "hit.h"
#include "boundingbox.h"
#include "raytracing_stats.h"

class Object3D {
public:
    explicit Object3D(Material *material, BoundingBox* boundingBox = nullptr) : 
        material(material) , boundingBox(boundingBox) {}  

    Object3D() : Object3D(nullptr) {}

    virtual ~Object3D() {
        delete boundingBox;
    }

    BoundingBox *getBoundingBox() { return boundingBox; }

    virtual bool intersect(const Ray &r, Hit &h, float tMin) = 0;

    virtual void paint() = 0;

    virtual void insertIntoGrid(Grid *g, Matrix *m) {}
    
protected:
    constexpr static const float EPSILON = 1e-8;
    Material *material;
    BoundingBox *boundingBox;
};

#endif //ASSIGNMENT1_OBJECT3D_H
