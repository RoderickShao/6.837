# include "renderer.h"
# include "camera.h"
# include "group.h"
# include "hit.h"
# include "light.h"
# include "material.h"
# include "global.h"

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
                image->SetPixel(i, j, hit.getMaterial()->getDiffuseColor(hit.getIntersectionPoint()));
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
            auto diffuseCol = hit.getMaterial()->getDiffuseColor(hit.getIntersectionPoint());
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

            image->SetPixel(i, j, color);
        }
    }
}
void RayTracerRenderer::Render() {
    Renderer::Render(); // preparations
    auto tracer = new RayTracer(scene, maxBounces, cutoffWeight);

    Sampler* sampler;
    if (randomSampler) {
        sampler = new RandomSampler(numSamples);
    }  else if (jitteredSampler){
        sampler = new JitteredSampler(numSamples);
    } else  {
        sampler = new UniformSampler(numSamples);
    }

    Filter* filter = nullptr;
    if (boxFilter){
        filter = new BoxFilter(radius);
    } else if (tentFilter) {
        filter = new TentFilter(radius);
    } else if (gaussianFilter) {
        filter = new GaussianFilter(sigma);
    }

    if (nx*ny*nz != 0)
    {
        Grid* grid = tracer->getGrid();
        BoundingBox* bb = grid->getBoundingBox();
        int nx,ny,nz;
        std::tie(nx, ny, nz) = grid->getGridSize();
        RayTracingStats::Initialize(width, height, bb, nx, ny, nz);
    }
    else 
    {
        RayTracingStats::Initialize(width, height, group->getBoundingBox(), 1, 1, 1);
    }

    auto film = new Film(image->Width(), image->Height(), numSamples);

    for (int i = 0; i < image->Width(); i++) {
        for (int j = 0; j < image->Height(); j++) {
            for (int k = 0; k < numSamples; k++)
            {
                Vec2f offset = sampler->getSamplePosition(k);
                auto ray = camera->generateRay(Vec2f(
                    (offset.x() + i - image->Width() / 2.0f) / image->Width(),
                    (offset.y() + j - image->Height() / 2.0f) / image->Width()));
                Hit hit;
                Vec3f color;
                if (nx*ny*nz == 0)
                {
                    color = tracer->traceRay(ray, camera->getTMin(), 0, 1, 1, hit);
                }
                else
                {
                    color = tracer->traceRayFast(ray, camera->getTMin(), 0, 1, 1, hit);
                }

                film->setSample(i, j, k, offset, color);
            }
            
        }
    }

    if (sampleFile != nullptr) 
    {
        film->renderSamples(sampleFile, sampleZoom);
    }

    if (filterFile != nullptr)
    {
        film->renderFilter(filterFile, filterZoom, filter);
    }

    for (int i = 0; i < image->Width(); i++)
    {
        for (int j = 0; j < image->Height(); j++)
        {
            Vec3f color = film->getSample(i, j, 0).getColor();
            if (filter!=nullptr) color = filter->getColor(i, j, film);
            image->SetPixel(i, j, color);
        }
    }
        
    if(stats)
        RayTracingStats::PrintStatistics();

    delete sampler;
    delete filter;
    delete tracer;
}