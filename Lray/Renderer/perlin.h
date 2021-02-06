#pragma once
#include "vec3.h"
#include "math.h"

static float perlinInterpolation(vec3 _c[2][2][2], float _u, float _v, float _w);

class perlin {
public:
    perlin() {}     

    float noise(const vec3& _p) const {
        float u = _p.x() - floor(_p.x());
        float v = _p.y() - floor(_p.y());
        float w = _p.z() - floor(_p.z());
        int i = floor(_p.x());
        int j = floor(_p.y());
        int k = floor(_p.z());
        vec3 c[2][2][2];
        //float c[2][2][2];
        for(int di = 0; di < 2; di++){
            for (int dj = 0; dj < 2; dj++) {
                for (int dk = 0; dk < 2; dk++) {
                    //c[di][dj][dk] = mRanFloat[mPermX[(i + di) & 255] ^ mPermY[(j + dj) & 255] ^ mPermZ[(k + dk) & 255]];
                    c[di][dj][dk] = mRanVec[mPermX[(i + di) & 255] ^ mPermY[(j + dj) & 255] ^ mPermZ[(k + dk) & 255]];
                }
            }
        }
        //return trilinearInterpolation(c, u, v, w);
        return perlinInterpolation(c, u, v, w);
    }
    float turb(const vec3& _p, int depth = 7) const {
        float accum = 0.0f;
        vec3 temp = _p;
        float weight = 1.0f;
        for (int i = 0; i < depth; i++) {
            accum += weight * noise(temp);
            weight *= 0.5f;
            temp *= 2.0f;
        }
        return fabs(accum);
    }
    static vec3* mRanVec;
    static float* mRanFloat;
    static int* mPermX;
    static int* mPermY;
    static int* mPermZ;

    
};
static void permute(int* _p, int _n) {
    for (int i = _n - 1; i > 0; i--) {
        int target = randomInt(0, i);
        int tmp = _p[i];
        _p[i] = _p[target];
        _p[target] = tmp;
    }
}
static int* generatePerm() {
    int* p = new int[256];

    for (int i = 0; i < 256; i++)
        p[i] = i;

    permute(p, 256);

    return p;
}
static vec3* generatePerlin() {
    vec3* p = new vec3[256];
    for (int i = 0; i < 256; ++i) {
        p[i] = unitVector(vec3( randomDouble(), randomDouble(), randomDouble()));
    }
    return p;
}
static float* generatePerlinFloat() {
    float* p = new float[256];
    for (int i = 0; i < 256; ++i) {
        p[i] = randomDouble();
    }
    return p;
}


static float perlinInterpolation(vec3 _c[2][2][2], float _u, float _v, float _w) {
    float uu = _u * _u * (3 - 2 * _u);
    float vv = _v * _v * (3 - 2 * _v);
    float ww = _w * _w * (3 - 2 * _w);
    float accum = 0.0f;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                vec3 weight(_u - i, _v - j, _w - k);
                accum += (i * uu + (1 - i) * (1 - uu)) *
                    (j * vv + (1 - j) * (1 - vv)) *
                    (k * ww + (1 - k) * (1 - ww)) *
                    dot(_c[i][j][k], weight);
            }
        }
    }
    return accum;
}



vec3* perlin::mRanVec = generatePerlin();
float* perlin::mRanFloat = generatePerlinFloat();

int* perlin::mPermX = generatePerm();
int* perlin::mPermY = generatePerm();
int* perlin::mPermZ = generatePerm();