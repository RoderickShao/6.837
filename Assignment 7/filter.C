# include "filter.h"

Vec3f Filter::getColor(int i, int j, Film *film)
{
    int r = getSupportRadius();
    int width = film->getWidth();
    int height = film->getHeight();
    int n = film->getNumSamples();

    Vec3f color(0,0,0);
    float weight = 0;

    for (int x = std::max(0, i - r); x <= std::min(width - 1, i + r); x++)
    {
        for (int y = std::max(0, j - r); y <= std::min(height - 1, j + r); y++)
        {
            for (int k = 0; k < n; k++)
            {
                Sample sample = film->getSample(x, y, k);
                Vec2f samplePosition = Vec2f(sample.getPosition().x()+x, sample.getPosition().y()+y);
                Vec2f offset = Vec2f(samplePosition.x()-i-0.5, samplePosition.y()-j-0.5);
                float w = getWeight(offset.x(), offset.y());
                weight += w;
                color += w * sample.getColor();
            }
        }
    }

    return {color.x()/weight, color.y()/weight, color.z()/weight};
}

float BoxFilter::getWeight(float x, float y) {
    float dist = std::max(std::abs(x), std::abs(y));
    if (dist <= radius)
        return 1;
    else return 0;
}

float TentFilter::getWeight(float x, float y) {
    float length = std::sqrt(x*x + y*y);
    float weight = 1 - length/radius;
    if (weight < 0)
        return 0;
    else return weight;
}

float GaussianFilter::getWeight(float x, float y) {
    float length = std::sqrt(x*x + y*y);
    return exp( -length*length/(2*sigma*sigma));
}