# include "sampler.h"

Vec2f RandomSampler::getSamplePosition (int n) {
    float x = (float)rand() / (float)RAND_MAX;
    float y = (float)rand() / (float)RAND_MAX;
    return Vec2f(x, y);
}

Vec2f UniformSampler::getSamplePosition (int n) {
    int i = n / nPerSide;
    int j = n % nPerSide;
    return {(i + 0.5f)*gap, (j + 0.5f)*gap};
}

Vec2f JitteredSampler::getSamplePosition (int n) {
    int i = n / nPerSide;
    int j = n % nPerSide;
    return {(i + rand() / (float)RAND_MAX)*gap, (j + rand() / (float)RAND_MAX)*gap};
}