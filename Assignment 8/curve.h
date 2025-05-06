# ifndef ASSIGNMENT8_CURVE_H
# define ASSIGNMENT8_CURVE_H

#include "spline.h"
#include "matrix.h"

class Curve : public Spline {
    public:
        Curve (int num_vertices): Spline(), numVertices(num_vertices) {
            vertices = new Vec3f[numVertices];
        }

        void Paint(ArgParser *args) override;

        int getNumVertices() override{
            return numVertices;
        }

        Vec3f getVertex(int i) override{
            return vertices[i];
        }

        int getNumCurves() {
            return numCurves;
        }

        void moveControlPoint(int selectedPoint, float x, float y) override{
            vertices[selectedPoint] = Vec3f(x, y, 0);
        }

        virtual Vec3f* tessellate(ArgParser *args)=0;

        void set (int i, Vec3f v){
            vertices[i] = v;
        }

    protected:
        int numCurves;
        int numVertices;
        Vec3f *vertices;
        Matrix mat;
};

class BezierCurve : public Curve {
    public:
        void InitializeMatrix()
        {
            float Bezier[] = {
                -1, 3, -3, 1,
                3, -6, 3, 0,
                -3, 3, 0, 0,
                1, 0, 0, 0
            };
            float BSpilne[] = {
                -1, 3, -3, 1,
                3, -6, 0, 4,
                -3, 3, 3, 1,
                1, 0, 0, 0
            };
            Matrix matBezier(Bezier);
            Matrix matBSpline(BSpilne);
            mat = matBezier;
            matBSpline*= (1.0/6);
            matBSpline.Inverse(matBSpline, 0.0001);
            matInver = mat*matBSpline;
        }
        BezierCurve (int num_vertices): Curve(num_vertices){
            InitializeMatrix();
            numCurves = (num_vertices-1)/3;
        }

        Vec3f* tessellate(ArgParser *args);

        void addControlPoint(int selectedPoint, float x, float y) override{
            numVertices++;
            numCurves = (numVertices-1)/3;
            Vec3f* newVertices = new Vec3f[numVertices];
            for (int i = 0; i < selectedPoint; i++){
                newVertices[i] = vertices[i];
            }
            newVertices[selectedPoint] = Vec3f(x, y, 0);
            for (int i = selectedPoint + 1; i < numVertices; i++){
                newVertices[i] = vertices[i - 1];
            }
            delete[] vertices;
            vertices = newVertices;
        }

        void deleteControlPoint(int selectedPoint) override{
            numVertices--;
            numCurves = (numVertices-1)/3;
            Vec3f* newVertices = new Vec3f[numVertices];
            for (int i = 0; i < selectedPoint; i++){
                newVertices[i] = vertices[i];
            }
            for (int i = selectedPoint; i < numVertices; i++){
                newVertices[i] = vertices[i + 1];
            }
            delete[] vertices;
            vertices = newVertices;
        }

        void OutputBezier(FILE *file);
        void OutputBSpline(FILE *file);

    private:
        Matrix matInver;
};

class BSplineCurve : public Curve {
    public:

        void InitializeMatrix()
        {
            float Bezier[] = {
                -1, 3, -3, 1,
                3, -6, 3, 0,
                -3, 3, 0, 0,
                1, 0, 0, 0
            };
            float BSpilne[] = {
                -1, 3, -3, 1,
                3, -6, 0, 4,
                -3, 3, 3, 1,
                1, 0, 0, 0
            };

            Matrix matBezier(Bezier);
            Matrix matBSpline(BSpilne);
            mat = matBSpline*(1.0/6);
            matBezier.Inverse(matBezier, 0.0001);
            matInver = mat*matBezier;
        }
        BSplineCurve (int num_vertices): Curve(num_vertices){
            InitializeMatrix();
            numCurves = num_vertices-3;
        }

        Vec3f* tessellate(ArgParser *args);

        void addControlPoint(int selectedPoint, float x, float y) override{
            numVertices++;
            numCurves = numVertices-3;
            Vec3f* newVertices = new Vec3f[numVertices];
            for (int i = 0; i < selectedPoint; i++){
                newVertices[i] = vertices[i];
            }
            newVertices[selectedPoint] = Vec3f(x, y, 0);
            for (int i = selectedPoint + 1; i < numVertices; i++){
                newVertices[i] = vertices[i - 1];
            }
            delete[] vertices;
            vertices = newVertices;
        }

        void deleteControlPoint(int selectedPoint) override{
            numVertices--;
            numCurves = numVertices-3;
            Vec3f* newVertices = new Vec3f[numVertices];
            for (int i = 0; i < selectedPoint; i++){
                newVertices[i] = vertices[i];
            }
            for (int i = selectedPoint; i < numVertices; i++){
                newVertices[i] = vertices[i + 1];
            }
            delete[] vertices;
            vertices = newVertices;
        }

        void OutputBezier(FILE *file) override;
        void OutputBSpline(FILE *file) override;

    private:
        Matrix matInver;
};

# endif