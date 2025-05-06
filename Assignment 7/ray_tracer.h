#ifndef _RAY_TRACER_H_
#define _RAY_TRACER_H_

#include "global.h"
#include "group.h"
#include "scene_parser.h"
#include "ray.h"
#include "hit.h"
#include "grid.h"
#include "raytracing_stats.h"

class RayTracer {
    public:
        RayTracer(SceneParser *s, int max_bounces, float cutoff_weight)
        {
            scene = s;
            group = s->getGroup();
            maxBounces = max_bounces;
            cutoffWeight = cutoff_weight;
            if (nx*ny*nz!=0)
            {
                grid = new Grid(group->getBoundingBox(),nx, ny, nz);
                group->insertIntoGrid(grid, nullptr);
            }
            else 
                grid = nullptr;
        }

        ~RayTracer() {
            if (grid!=nullptr)
                delete grid;
        }

        Vec3f traceRay(Ray &ray, float tmin, int bounces, float weight, 
                 float indexOfRefraction, Hit &hit) const;
        
        Vec3f traceRayFast(Ray &ray, float tmin, int bounces, float weight,
                float indexOfRefraction, Hit &hit) const;

        Grid* getGrid() const
        {
            return grid;
        }

    private:
        SceneParser *scene;
        Group *group;
        Grid* grid;
        int maxBounces;
        float cutoffWeight;
};

#endif