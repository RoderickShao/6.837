# ifndef ASSIGNMENT2_RENDERER_h
# define ASSIGNMENT2_RENDERER_h

#include "image.h"
#include "scene_parser.h"
#include "hit.h"
#include "ray_tracer.h"

class Renderer {
    public:
        Renderer(Image *image, SceneParser *scene): image(image), scene(scene) {
            assert(scene);
            camera = scene->getCamera();
            group = scene->getGroup();
            width = image->Width();
            height = image->Height();
        }
        virtual void Render(){
            assert(image);
            image->SetAllPixels(scene->getBackgroundColor());
        }
    protected:
        Image *image;
        SceneParser *scene;
        Camera *camera;
        Group *group;
        int width, height;
};

//深度图的渲染
class DepthRenderer : public Renderer {
    public:
        DepthRenderer(Image *image = nullptr, SceneParser *scene = nullptr,
                      float depthMin = -FP_INFINITE, float depthMax = FP_INFINITE
                      ): Renderer(image, scene),depthMin(depthMin),depthMax(depthMax) {}
        void Render() override;
    protected:
        float depthMin,depthMax;
};

//带颜色的图的渲染
class ColorRenderer : public Renderer {
    public:
        ColorRenderer(Image *image = nullptr, SceneParser *scene = nullptr):
                      Renderer(image, scene) {}
        void Render() override;
};

class NormalRenderer : public Renderer {
    public:
        NormalRenderer(Image *image = nullptr, SceneParser *scene = nullptr):
                      Renderer(image, scene) {}
        void Render() override;
};

class DiffuseRenderer : public Renderer {
    public:
        DiffuseRenderer(Image *image = nullptr, SceneParser *scene = nullptr, bool shadeBack=false):
                      Renderer(image, scene),shadeBack(shadeBack) {}
        void Render() override;
    protected:
        bool shadeBack;
};

class RayTracerRenderer : public Renderer {
    public:
        RayTracerRenderer(Image *image = nullptr, SceneParser *scene = nullptr):
                      Renderer(image, scene){}
        void Render() override;
};
# endif