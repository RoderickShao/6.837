#ifndef ASSIGNMENT2_GLOBAL_H
#define ASSIGNMENT2_GLOBAL_H

extern const float EPSILON;

extern bool gouraud,gui,shadeback,shadows;

extern bool visualizeGrid;

extern bool randomSampler, uniformSampler, jitteredSampler;

extern bool boxFilter, tentFilter, gaussianFilter;

extern bool stats;

extern int thetaSteps, phiSteps;

extern int nx,ny,nz;

extern int width, height;
extern int maxBounces;

extern int numSamples;
extern int sampleZoom;
extern int filterZoom;
extern float radius;
extern float sigma;

extern float depthMin, depthMax;
extern float cutoffWeight;

extern char* sampleFile;
extern char* filterFile;


#endif