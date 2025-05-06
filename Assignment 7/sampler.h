#ifndef ASSIGNMENT7_SAMPLER_h
#define ASSIGNMENT7_SAMPLER_h

#include "vectors.h"

class Sampler{
    public:
        Sampler(int num_samples){
            this->num_samples = num_samples;
        }

        virtual Vec2f getSamplePosition (int n) = 0;

    protected:
        int num_samples;
};

class RandomSampler : public Sampler{
    public:
        RandomSampler(int num_samples) : Sampler(num_samples) {}

        Vec2f getSamplePosition (int n) override;
        
};

class UniformSampler : public Sampler{
    public:
        UniformSampler(int num_samples) : Sampler(num_samples) {
            nPerSide = (int)sqrt(num_samples);
            gap = 1.0f / nPerSide;
        }

        Vec2f getSamplePosition (int n) override;
    
    protected:
        int nPerSide;
        float gap;
};

class JitteredSampler : public Sampler{
    public:
        JitteredSampler(int num_samples) : Sampler(num_samples) {
            nPerSide = (int)sqrt(num_samples);
            gap = 1.0f / nPerSide;
        }

        Vec2f getSamplePosition (int n) override;

    protected:
        int nPerSide;
        float gap;
};


#endif