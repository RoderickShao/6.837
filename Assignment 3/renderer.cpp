# include "renderer.h"
# include "camera.h"
# include "group.h"
# include "hit.h"
# include "light.h"
# include "material.h"

void DepthRenderer::Render()
{
    assert(image);
    image->SetAllPixels(Vec3f(0, 0, 0));
    auto camera = scene->getCamera();
    for (int i = 0; i < image->Width(); i++)
    {
        for (int j = 0; j < image->Height(); j++)
        {
            Ray ray = camera->generateRay(Vec2f((float)i / image->Width(),(float)j / image->Height()));
            Hit hit;
            auto interRes = group->intersect(ray, hit, camera->getTMin());
            if (interRes)
            {
                float depth = hit.getT();
                
                if (depth >= depthMin && depth <= depthMax) {
                    float depthCol = 1.0*(depthMax - depth) / (depthMax - depthMin);
                    image->SetPixel(i, j, Vec3f(depthCol, depthCol, depthCol));
                    //printf("depth: %f\n", depthMax);
                }
            }
        }
    }
}

void ColorRenderer::Render()
{
    Renderer::Render();
    auto camera = scene->getCamera();
    for (int i = 0; i < image->Width(); i++)
    {
        for (int j = 0; j < image->Height(); j++)
        {
            Ray ray = camera->generateRay(Vec2f((float)i / image->Width(),(float)j / image->Height()));
            Hit hit;
            auto interRes = group->intersect(ray, hit, camera->getTMin());
            if (interRes)
            {
                image->SetPixel(i, j, hit.getMaterial()->getDiffuseColor());
            }
        }
    }
}

void NormalRenderer::Render()
{
    assert(image);
    image->SetAllPixels(Vec3f(0, 0, 0));
    auto camera = scene->getCamera();
    for (int i = 0; i < image->Width(); i++)
    {
        for (int j = 0; j < image->Height(); j++)
        {
            Ray ray = camera->generateRay(Vec2f((float)i / image->Width(),(float)j / image->Height()));
            Hit hit;
            auto interRes = group->intersect(ray, hit, camera->getTMin());
            if (interRes)
            {
                auto n = hit.getNormal();
                n.Set(fabs(n.x()), fabs(n.y()), fabs(n.z()));
                image->SetPixel(i, j, n);
            }
        }
    }
}

void DiffuseRenderer::Render()
{
    Renderer::Render();
    auto camera = scene->getCamera();
    for (int i = 0; i < image->Width(); i++)
    {
        for (int j = 0; j < image->Height(); j++)
        {
            Ray ray = camera->generateRay(Vec2f((float)i / image->Width(),(float)j / image->Height()));
            Hit hit;
            auto interRes = group->intersect(ray, hit, camera->getTMin());
            if (!interRes) continue;
            Vec3f color = Vec3f(0, 0, 0);
            auto diffuseCol = hit.getMaterial()->getDiffuseColor();
            auto n = hit.getNormal();
            for (int k = 0; k < scene->getNumLights(); k++)
            {
                auto light = scene->getLight(k);
                Vec3f dir, col;
                float distanceToLight;
                light->getIllumination(hit.getIntersectionPoint(), dir, col, distanceToLight);
                color += hit.getMaterial()->Shade(ray, hit, dir, col);
            }
            auto ambientCol = scene->getAmbientLight();
            ambientCol.Scale(diffuseCol.x(), diffuseCol.y(), diffuseCol.z());
            color += ambientCol;
            color.Clamp();

            image->SetPixel(i, j, color);;
        }
    }
}