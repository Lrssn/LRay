#define STB_IMAGE_IMPLEMENTATION

#include <float.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include "Lray.h"

#include "Externals/stb_image.h"


hitable* randomScene(int _nrOfSpheres, int _sizex, int _sizey, int _sizez, float _time0, float _time1) {
    hitableList objList;
    texture* checker = new checkerTexture(new constantTexture(vec3(1.0f, 1.0f, 1.0f)), new constantTexture(vec3(0.0f, 1.0f, 0.0f)));
    objList.add(new sphere(vec3(0.0f, -1000.0f, -1.0f), 1000.0f, new lambertian(checker)));
    std::vector<material*> mats;
    mats.push_back(new dielectric(new constantTexture(vec3(1.0f, 0.0f, 1.0f)), 0.5f, 1.5f));
    mats.push_back(new metal(new constantTexture(vec3(1.0f, 0.2f, 0.1f)), 1.0f));
    int i = 1;
    float diffx = float(_sizex) / _nrOfSpheres;
    float diffz = float(_sizez) / _nrOfSpheres;
    for (int a = -(_nrOfSpheres / 2); a < _nrOfSpheres / 2; a++) {
        for (int b = -_nrOfSpheres / 2; b < _nrOfSpheres / 2; b++) {
            float chooseMat = randomDouble();
            vec3 center(a*diffx + 0.2f * randomDouble(), _sizey*randomDouble(), b*diffz + 0.2 * randomDouble());
            if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
                if (chooseMat < 0.5f) { //diffuse
                    objList.add(new movingSphere(center, center+vec3(0.0f, 0.5f*randomDouble(), 0.0f), _time0, _time1,  0.2f, new lambertian(new constantTexture(vec3(randomDouble(), randomDouble(), randomDouble())))));
                } else if (chooseMat < 0.8f) { //diffuse
                    objList.add(new sphere(center, 0.2f, new lambertian(new constantTexture(vec3(randomDouble(), randomDouble(), randomDouble())))));
                } else if (chooseMat < 0.95f) { //metal
                    objList.add(new sphere(center, 0.2f, new metal(new constantTexture(vec3(0.5f*(1+randomDouble()), 0.5f * (1 + randomDouble()), 0.5f * (1 + randomDouble()))), 0.5f * (1 + randomDouble()))));
                } else { //glass
                    objList.add(new sphere(center, 0.2f, new dielectric(new constantTexture(vec3(1.0f, 1.0f, 1.0f)), 0.5f, 1.5f)));
                }
            }
        }
    }
    objList.add(new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new dielectric(new constantTexture(vec3(1.0f, 1.0f, 1.0f)), 1.0f, 1.5f)));
    objList.add(new sphere(vec3(-4.0f, 1.0f, 0.0f), 1.0f, new lambertian(new constantTexture(vec3(0.4f, 0.2f, 0.1f)))));
    objList.add(new sphere(vec3(4.0f, 1.0f, 0.0f), 1.0f, new metal(new constantTexture(vec3(0.7f, 0.6f, 0.5f)), 0.5f)));
    objList.add(new sphere(vec3(0.0f, 7.0f, 0.0f), 2.0f, new diffuseLight(new constantTexture(vec3(4.0f)))));
    auto a = new bvhNode(objList, 0.0f, 1.0f);
    return new hitableList(a);
}
hitable* oneSphere() {
    hitableList objList;
    texture* checker = new checkerTexture(new constantTexture(vec3(1.0f)), new constantTexture(vec3(0.0f)));

    objList.add(new sphere(vec3(0.0f, -1001.0f, 0.0f), 1000.0f, new lambertian(checker)));
    std::vector<material*> mats;
    mats.push_back(new dielectric(new constantTexture(vec3(0.4f, 0.2f, 0.1f)), 1.0f, 1.5f));
    mats.push_back(new metal(new constantTexture(vec3(1.0f, 0.2f, 0.1f)), 0.5f));
    objList.add(new sphere(vec3(0.0f, 0.0f, 0.0f), 1.0f, new multiMaterial(mats, checker)));
    objList.add(new sphere(vec3(0.0f, 4.0f, 0.0f), 2.0f, new diffuseLight(new constantTexture(vec3(7.0f)))));
    auto a = new bvhNode(objList, 0.0f, 1.0f);
    return new hitableList(a);
}
hitable* twoSpheres() {
    hitableList objList;
    texture* checker = new checkerTexture(new constantTexture(vec3(1.0f, 1.0f, 1.0f)), new constantTexture(vec3(0.0f, 1.0f, 0.0f)));
    int nx, ny, nn;
    //unsigned char* tex_data = stbi_load("earthmap.png", &nx, &ny, &nn, 3);
    objList.add(new sphere(vec3(0.0f, -1000.0f, -1.0f), 1000.0f, new lambertian(checker)));
    objList.add(new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new lambertian(checker)));
    auto a = new bvhNode(objList, 0.0f, 1.0f);
    return new hitableList(a);
}
hitable* fourSpheres() {
    hitableList objList;
    texture* checker = new checkerTexture(new constantTexture(vec3(1.0f, 1.0f, 1.0f)), new constantTexture(vec3(0.0f, 1.0f, 0.0f)));
    int nx, ny, nn;
    //unsigned char* tex_data = stbi_load("earthmap.png", &nx, &ny, &nn, 3);
    objList.add(new sphere(vec3(0.0f, -1000.0f, -1.0f), 1000.0f, new lambertian(checker)));
    objList.add(new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new lambertian(checker)));
    objList.add(new sphere(vec3(2.0f, 1.0f, 1.0f), 1.0f, new lambertian(checker)));
    objList.add(new sphere(vec3(2.0f, 1.0f, -3.0f), 1.0f, new lambertian(checker)));
    auto a = new bvhNode(objList, 0.0f, 1.0f);
    return new hitableList(a);
}
hitable* simpleLight() {
    hitableList objList;
    texture* checker = new checkerTexture(new constantTexture(vec3(1.0f, 1.0f, 1.0f)), new constantTexture(vec3(0.0f, 1.0f, 0.0f)));
    texture* pertext = new noiseTexture(4);
    objList.add(new sphere(vec3(0.0f, -1000.0f, -1.0f), 1000.0f, new lambertian(pertext)));
    objList.add(new sphere(vec3(0.0f, 2.0f, 0.0f), 2.0f, new lambertian(pertext)));
    objList.add(new sphere(vec3(0.0f, 7.0f, 0.0f), 2.0f, new diffuseLight(new constantTexture(vec3(4.0f, 4.0f, 4.0f)))));
    objList.add(new rectangleXY(3.0f, 5.0f, 1.0f, 3.0f, -2.0f, new diffuseLight(new constantTexture(vec3(4.0f)))));

    auto a = new bvhNode(objList, 0.0f, 1.0f);
    return new hitableList(a);
}
hitable* triangleSet() {
    hitableList objList;
    vertex v0, v1, v2, v3;
    v0.pos = vec3(-1.0f, 0.0f, 0.0f);
    v1.pos = vec3(-1.0f, 1.0f, 0.0f);
    v2.pos = vec3(1.0f, 1.0f, 0.0f);
    v3.pos = vec3(1.0f, 0.0f, 0.0f);
    objList.add(new triangle(v0, v1, v2, new lambertian(new constantTexture(vec3(1.0f, 0.0f, 0.0f)))));
    objList.add(new triangle(v0, v3, v2, new lambertian(new constantTexture(vec3(0.0f, 1.0f, 0.0f)))));
    //objList.add(new sphere(vec3(0.0f, -1000.0f, -1.0f), 1000.0f, new lambertian(new constantTexture(vec3(1.0f, 1.0f, 1.0f)))));
    
    //objList.add(new sphere(vec3(0.0f, 6.0f, 2.0f), 2.0f, new diffuseLight(new constantTexture(vec3(16.0f)))));
    auto a = new bvhNode(objList, 0.0f, 1.0f);
    a->getbox().writebox();
    return new hitableList(a);
}
hitable* smoke() {
    hitableList objList;
    texture* checker = new checkerTexture(new constantTexture(vec3(1.0f, 1.0f, 1.0f)), new constantTexture(vec3(0.0f, 1.0f, 0.0f)));
    int nx, ny, nn;
    //unsigned char* tex_data = stbi_load("earthmap.png", &nx, &ny, &nn, 3);

    objList.add(new sphere(vec3(0.0f, 4.0f, 0.0f), 2.0f, new diffuseLight(new constantTexture(vec3(4.0f)))));
    objList.add(new sphere(vec3(0.0f, -1000.0f, -1.0f), 1000.0f, new lambertian(checker)));
    hitable* vol = new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new lambertian(checker));
    objList.add(new constantVolume(vol, 0.1f, new constantTexture(vec3(1.0f))));
    auto a = new bvhNode(objList, 0.0f, 1.0f);
    return new hitableList(a);
}

int main(){
    //highres
    //int nx = 3840, ny = 2160, ns = 100;
    //test
    int nx = 720, ny = 640, ns = 30;

    //camera setup
    vec3 lookfrom(7.0f, 3.0f, 0.0f);
    vec3 lookat(0.0f, 0.0f, 0.0f);
    float disttofocus = 10.0f;
    float aperture = 0.0f;
    camera cam(lookfrom, lookat, vec3(0.0f, 1.0f, 0.0f), 50.0f, float(nx)/float(ny), aperture, disttofocus, 0.0f, 1.0f);

    //hitable* world = randomScene(25, 25, 1, 25, 0.0f, 1.0f);
    //hitable* world = twoSpheres();
    //hitable* world = fourSpheres();
    //hitable* world = oneSphere();
    hitable* world = smoke();
    //hitable* world = simpleLight();
    //hitable* world = triangleSet();
    
    LRay ray(cam, nx, ny, ns);
    ray.render(world);
    
    writeppm(nx, ny, ray.getPixels(), "helloworld");
    std::cout << "Ray!\n";
}
