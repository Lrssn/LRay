#include <float.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include "Renderer/IO.h"
#include "Renderer/vec3.h"
#include "Renderer/ray.h"
#include "Renderer/hitable_list.h"
#include "Renderer/sphere.h"
#include "Renderer/movingSphere.h"
#include "Renderer/camera.h"
#include "Renderer/math.h"
#include "Renderer/material.h"





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

hitable* randomScene(int _nrOfSpheres) {
    std::vector<hitable*> objList;
    objList.push_back(new sphere(vec3(0.0f, -1000.0f, -1.0f), 1000.0f, new lambertian(vec3(0.5f, 0.5f, 0.5f))));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float chooseMat = randomDouble();
            vec3 center(a + 0.9f * randomDouble(), 0.2f, b + 0.9 * randomDouble());
            if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
                if (chooseMat < 0.5f) { //diffuse
                    objList.push_back(new movingSphere(center, center+vec3(0.0f, 0.5f*randomDouble(), 0.0f), 0.0f, 1.0f,  0.2f, new lambertian(vec3(randomDouble(), randomDouble(), randomDouble()))));
                } else if (chooseMat < 0.8f) { //diffuse
                    objList.push_back(new sphere(center, 0.2f, new lambertian(vec3(randomDouble(), randomDouble(), randomDouble()))));
                } else if (chooseMat < 0.95f) { //metal
                        objList.push_back(new sphere(center, 0.2f, new metal(vec3(0.5f*(1+randomDouble()), 0.5f * (1 + randomDouble()), 0.5f * (1 + randomDouble())), 0.5f * (1 + randomDouble()))));
                } else { //glass
                    objList.push_back(new sphere(center, 0.2f, new dielectric(1.5f)));
                }
                
            }
        }
    }
    objList.push_back(new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new dielectric(1.5f)));
    objList.push_back(new sphere(vec3(-4.0f, 1.0f, 0.0f), 1.0f, new lambertian(vec3(0.4f, 0.2f, 0.1f))));
    objList.push_back(new sphere(vec3(4.0f, 1.0f, 0.0f), 1.0f, new metal(vec3(0.7f, 0.6f, 0.5f), 0.0f)));

    return new hitableList(objList, objList.size());
}

int main(){
    std::vector<int> color;
    int nx = 1280, ny = 720, ns = 50;
    vec3 lookfrom(13.0f, 2.0f, 3.0f);
    vec3 lookat(0.0f, 0.0f, 0.0f);
    float disttofocus = 10.0f;
    float aperture = 0.0f;
    camera cam(lookfrom, lookat, vec3(0.0f, 1.0f, 0.0f), 20.0f, float(nx)/float(ny), aperture, disttofocus, 0.0f, 1.0f);

    hitable* world = randomScene(500);
    int current = 0;
    float percent = 0.0f, total = nx * ny;
    std::cout << std::setprecision(5) << percent << "% finished" << std::endl;
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
            current += 1;
            if (current % 1000 == 0) {
                percent = 100.0f*(float(current) / total);
                system("CLS");
                std::cout << std::setprecision(5) << percent << "% finished" << std::endl;
            }
        }
    }
    writeppm(nx, ny, color, "helloworld");
    std::cout << "Ray!\n";
}
