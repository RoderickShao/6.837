# ifndef ASSIGNMENT8_SURFACE_H
# define ASSIGNMENT8_SURFACE_H

# include "spline.h"
# include "matrix.h"
# include "curve.h"

class Surface : public Spline {
    public:
        Surface (): Spline(){}
};



class SurfaceOfRevolution : public Surface {
    public:
        SurfaceOfRevolution (Curve* curve): Surface(){
            this->curve = curve;
        }

        TriangleMesh* OutputTriangles(ArgParser *args);

        int getNumVertices() override {
            return curve->getNumVertices();
        }
    
        Vec3f getVertex(int i) override {
            return curve->getVertex(i);
        }

        void Paint(ArgParser *args)
        {
            curve->Paint(args);
        }

        void moveControlPoint(int selectedPoint, float x, float y) override {
            curve->moveControlPoint(selectedPoint, x, y);
        }
    
        void addControlPoint(int selectedPoint, float x, float y) override {
            curve->addControlPoint(selectedPoint, x, y);
        }
    
        void deleteControlPoint(int selectedPoint) override {
            curve->deleteControlPoint(selectedPoint);
        }

        void OutputBezier(FILE *file) override {
            fprintf(file, "surface_of_revolution\n");
            curve->OutputBezier(file);
        }
    
        void OutputBSpline(FILE *file) override {
            fprintf(file, "surface_of_revolution\n");
            curve->OutputBSpline(file);
        }
    
    private:
        Curve* curve;
};

class BezierPatch : public Surface {
    public:
        BezierPatch (): Surface(){
            vertices = new Vec3f[16]; 
        }

        void set(int i, Vec3f v){
            vertices[i] = v;
        }

        TriangleMesh* OutputTriangles(ArgParser *args);

        void Paint(ArgParser *args);
        
    private:
        Vec3f *vertices;
};

# endif