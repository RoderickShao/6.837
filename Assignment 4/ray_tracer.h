#ifndef _RAY_TRACER_H_
#define _RAY_TRACER_H_

#include "scene_parser.h"
#include "ray.h"
#include "hit.h"

class RayTracer {
    public:
        RayTracer(SceneParser *s, int max_bounces, float cutoff_weight)
        {
            scene = s;
            group = s->getGroup();
            maxBounces = max_bounces;
            cutoffWeight = cutoff_weight;
        }

        Vec3f traceRay(Ray &ray, float tmin, int bounces, float weight, 
                 float indexOfRefraction, Hit &hit) const;

    private:
        SceneParser *scene;
        Group *group;
        int maxBounces;
        float cutoffWeight;
};

#endif