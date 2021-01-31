#include <iostream>
#include "Renderer/IO.h"
#include "Renderer/vec3.h"
#include "Renderer/ray.h"
#include "Renderer/hitable_list.h"
#include "Renderer/sphere.h"
#include "Renderer/camera.h"
#include "Renderer/math.h"
#include "Renderer/material.h"

#include <float.h>
#include <stdlib.h>



vec3 GetColor(const ray& _ray, hitable* _world, int _depth) {
    hitRecord rec;
    if (_world->hit(_ray, 0.001f, infinity, rec)) {
        ray scattered;
        vec3 attenuation;
        if (_depth < 50 && rec.matPtr->scatter(_ray, rec, attenuation, scattered)) {
            return attenuation * GetColor(scattered, _world, _depth + 1);
        } else {
            return vec3(0.0f, 0.0f, 0.0f);
        }
    } else {
        vec3 unitDirection = unitVector(_ray.direction());
        float t = 0.5f * (unitDirection.y() + 1.0f);
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }

}

int main(){
    std::vector<int> color;
    int nx = 200, ny = 100, ns = 10;
    camera cam;
    hitable *objList[5];
    objList[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, new lambertian(vec3(0.8f, 0.3f, 0.3f)));
    objList[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, new lambertian(vec3(0.8f, 0.8f, 0.0f)));
    objList[2] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f), 1.0f));
    objList[3] = new sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, new dielectric(1.5f));
    objList[4] = new sphere(vec3(-1.0f, 0.0f, -1.0f), -0.45f, new dielectric(1.5f));
    hitable* world = new hitableList(objList, 5);
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < ns; s++) {
                float u = float(i + randomDouble()) / float(nx);
                float v = float(j + randomDouble()) / float(ny);
                ray r = cam.createRay(u, v);
                col += GetColor(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            color.push_back(int(255.99 * col[0]));
            color.push_back(int(255.99 * col[1]));
            color.push_back(int(255.99 * col[2]));

        }
    }
    writeppm(nx, ny, color, "helloworld");
    std::cout << "Ray!\n";
}
