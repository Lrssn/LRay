#pragma once
#include <float.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include "Renderer/IO.h"
#include "Renderer/vec3.h"
#include "Renderer/ray.h"
#include "Renderer/hitable_list.h"
#include "Renderer/sphere.h"
#include "Renderer/bvhNode.h"
#include "Renderer/movingSphere.h"
#include "Renderer/rectangle.h"
#include "Renderer/triangle.h"
#include "Renderer/constantVolume.h"
#include "Renderer/camera.h"
#include "Renderer/math.h"
#include "Renderer/material.h"


class LRay {
public:
    LRay(camera _cam, int _sizeX, int _sizeY, int _nrOfRays){
        mCam = _cam;
        mSizeX = _sizeX;
        mSizeY = _sizeY;
        mNrOfRays = _nrOfRays;
        mTotal = _sizeX * _sizeY;
    }

    void render(hitable* _world, bool nolight = false) {
        int current = 0;
        float percent = 0.0f;
        std::cout << std::setprecision(5) << percent << "% finished" << std::endl;
        for (int j = mSizeY - 1; j >= 0; j--) {
            for (int i = 0; i < mSizeX; i++) {
                vec3 col(0.0f, 0.0f, 0.0f);
                for (int s = 0; s < mNrOfRays; s++) {
                    float u = float(i + randomDouble()) / float(mSizeX);
                    float v = float(j + randomDouble()) / float(mSizeY);
                    ray r = mCam.createRay(u, v);
                    if (nolight)
                        col += GetColorNoLight(r, _world, 0);
                    else
                        col += GetColor(r, _world, 0);
                }
                col /= float(mNrOfRays);
                col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
                mPixels.push_back(int(255.99 * col[0]));
                mPixels.push_back(int(255.99 * col[1]));
                mPixels.push_back(int(255.99 * col[2]));
                current += 1;
                
                if (current % 1000 == 0) {
                    percent = 100.0f * (float(current) / mTotal);
                    system("CLS");
                    std::cout << std::setprecision(5) << percent << "% finished" << std::endl;
                }
            }
        }
        std::cout << std::setprecision(5) << 100.000f << "% finished" << std::endl;
    };

    vec3 GetColor(const ray& _ray, hitable* _world, int _depth) {
        hitRecord rec;
        if (_world->hit(_ray, 0.001f, infinity, rec)) {
            ray scattered;
            vec3 attenuation;
            vec3 emitted = rec.matPtr->emitted(rec.u, rec.v, rec.p);
            if (_depth < 50 && rec.matPtr->scatter(_ray, rec, attenuation, scattered)) {
                return emitted + attenuation * GetColor(scattered, _world, _depth + 1);
            } else {
                return emitted;
            }
        } else {
            return vec3(0.0f, 0.0f, 0.0f);
        }
    }

    vec3 GetColorNoLight(const ray& _ray, hitable* _world, int _depth) {
        hitRecord rec;
        if (_world->hit(_ray, 0.001f, infinity, rec)) {
            ray scattered;
            vec3 attenuation;
            //vec3 emitted = rec.matPtr->emitted(rec.u, rec.v, rec.p);
            if (_depth < 50 && rec.matPtr->scatter(_ray, rec, attenuation, scattered)) {
                return attenuation * GetColorNoLight(scattered, _world, _depth + 1);
            } else {
                return vec3(0.0f, 0.0f, 0.0f);
            }
        } else {
            vec3 unitDirection = unitVector(_ray.direction());
            float t = 0.5 * (unitDirection.y() + 1.0);
            return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
        }
    }

    std::vector<unsigned char> getPixels(){
        return mPixels;
    }
private:
    camera mCam;
    std::vector<unsigned char> mPixels;
    int mSizeX, mSizeY, mNrOfRays, mTotal;
};