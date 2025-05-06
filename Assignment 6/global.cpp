#include "global.h"

const float EPSILON = 1e-6;

int thetaSteps = 100, phiSteps = 100;

bool gouraud=false, gui=false, shadeback=false, shadows=false;

bool visualizeGrid = false;

bool stats = false;

int width = 100, height = 100;

int nx=0;
int ny=0;
int nz=0;

int maxBounces = 1;

float depthMin = 0, depthMax = 1;
float cutoffWeight = 0;