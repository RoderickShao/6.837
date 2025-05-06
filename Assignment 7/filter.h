# ifndef ASSIGNMENT7_FILTER_H
# define ASSIGNMENT7_FILTER_H

# include "vectors.h"
# include "film.h"


class Filter {
    public: 
        Filter(){}

        Vec3f getColor(int i, int j, Film *film);

        virtual float getWeight(float x, float y) = 0;

        virtual int getSupportRadius() = 0;
};

class BoxFilter : public Filter {
    public:
        BoxFilter(float radius) : Filter(){
            this->radius = radius;
        }

        float getWeight(float x, float y) override;

        int getSupportRadius() {
            return ceil(radius - 0.5f);
        }
    
    protected:
        float radius;
};

class TentFilter : public Filter {
    public:
        TentFilter(float radius) : Filter(){
            this->radius = radius;
        }

        float getWeight(float x, float y) override;

        int getSupportRadius() {
            return ceil(radius - 0.5f);
        }

        float radius;
};

class GaussianFilter : public Filter {
    public:
        GaussianFilter(float sigma) : Filter(){
            this->sigma = sigma;
        }

        float getWeight(float x, float y) override;

        int getSupportRadius() {
            return ceil(2*sigma - 0.5f);
        }
    
        float sigma;
};




# endif