# include "ray_tracer.h"
# include "group.h"
# include "material.h"
# include "global.h"
# include "light.h"
# include "rayTree.h"


Vec3f mirrorDirection(const Vec3f &normal, const Vec3f &incoming)
{
    return incoming - 2 * normal.Dot3(incoming) * normal;
}

bool transmittedDirection(const Vec3f &normal, const Vec3f &incoming, float index_i, float index_t, Vec3f &transmitted)
{
    float cosi = -normal.Dot3(incoming);
    float eta = index_i / index_t;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0) {
        return false;
    }
    transmitted = eta * incoming + (eta * cosi - sqrtf(k)) * normal;
    return true;
}


Vec3f RayTracer::traceRay(Ray &ray, float tmin, int bounces, float weight, 
                 float indexOfRefraction, Hit & intersection) const
{
    if (bounces > maxBounces || weight < cutoffWeight) {
        return Vec3f(0, 0, 0);
    }
    bool is_inter = group -> intersect(ray, intersection, tmin);
    auto material = dynamic_cast<PhongMaterial *>(intersection.getMaterial());

    if (!is_inter) {
        return scene -> getBackgroundColor();
    }
    if (weight == 1 )
        RayTree::SetMainSegment(ray, 0, intersection.getT());

    Vec3f color = scene -> getAmbientLight()* material -> getDiffuseColor();

    //局部光照
    for (int ilight = 0; ilight < scene -> getNumLights(); ilight++)
    {
        Light *light = scene -> getLight(ilight);
        Vec3f dirToLight, lightColor;
        float disToLight;
        light -> getIllumination(intersection.getIntersectionPoint(), dirToLight, lightColor, disToLight);
        Ray lightray = Ray(intersection.getIntersectionPoint()-ray.getDirection()*0.001f, dirToLight);
        Hit lightHit;
        if (shadows && group -> intersect(lightray, lightHit, 0.001f) && lightHit.getT() < disToLight) {
            RayTree::AddShadowSegment(lightray, 0, lightHit.getT());
            continue;
        }
        if (shadows) {
            RayTree::AddShadowSegment(lightray, 0, disToLight);
        }
        color += material -> Shade(ray, intersection, dirToLight, lightColor);
    }

    Vec3f hitpoint = intersection.getIntersectionPoint();
    Vec3f normal = intersection.getNormal();
    Vec3f incoming = ray.getDirection();
    
    auto reflectionColor = material -> getreflectiveColor();
    if (reflectionColor.Length() > 0)
    {
        //计算反射项
        Vec3f reflectionDirection = mirrorDirection(normal, incoming);
        Vec3f reflectionRayOrig = intersection.getIntersectionPoint() - ray.getDirection() * 0.001;
        Ray reflectionRay(reflectionRayOrig, reflectionDirection);
        Hit reflectionHit;
        Vec3f reflectColor = traceRay(reflectionRay, 0, bounces + 1, weight * material -> getreflectiveColor().Length(), indexOfRefraction, reflectionHit);
        float reflectT = EPSILON;
        if (reflectionHit.getMaterial()!= nullptr)
            reflectT = reflectionHit.getT();
        RayTree::AddReflectedSegment(reflectionRay, 0, reflectT);
        color += reflectColor*reflectionColor;
    }

    auto refractionColor = material -> gettransparentColor();
    if (refractionColor.Length()>0)
    {
        float index_i = indexOfRefraction;
        float index_t = material -> getindexOfRefraction();

        //如果打到了背面，那么把法向量反向
        if (shadeback && normal.Dot3(incoming) > 0)
        {
            normal.Negate();
            index_t = 1;
        }
        //计算折射项
        Vec3f transimittedDirection;
        bool is_refract = transmittedDirection(normal, incoming, index_i, index_t, transimittedDirection);
        if(is_refract)
        {
            Vec3f refractionRayOrig = intersection.getIntersectionPoint() + ray.getDirection() * 0.001;
            Ray refractionRay(refractionRayOrig, transimittedDirection);
            Hit refractionHit;
            Vec3f refractColor = traceRay(refractionRay, 0, bounces + 1, weight * material -> gettransparentColor().Length(), material -> getindexOfRefraction(), refractionHit) ;
            float refractT = EPSILON;
            if (refractionHit.getMaterial()!= nullptr)
                refractT = refractionHit.getT();
            RayTree::AddTransmittedSegment(refractionRay, 0, refractT);
            color += refractColor*refractionColor;     
        }
    }
    return color;
}