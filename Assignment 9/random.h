#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <random>    // 包含随机数生成器的头文件
#include "vectors.h" // 假设 Vec3f 定义在这个头文件中

class Random {

public:

    // 使用 std::mt19937 作为随机数生成器
    Random(int seed = 0) : rng(seed), dist(0.0f, 1.0f) {}

    ~Random() {}

    // 返回一个在 0 到 1 之间的随机浮点数
    float next() {
        return dist(rng);
    }

    // 返回一个每个分量在 -1 到 1 之间的随机 Vec3f 向量
    Vec3f randomVector() {
        float x = next() * 2.0f - 1.0f;
        float y = next() * 2.0f - 1.0f;
        float z = next() * 2.0f - 1.0f;
        return Vec3f(x, y, z);
    }

private:

    std::mt19937 rng;          // 随机数生成器
    std::uniform_real_distribution<float> dist; // 分布对象，生成 0 到 1 之间的浮点数
};

#endif // _RANDOM_H_