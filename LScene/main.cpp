#include <iostream>
#include "core/LScene.h"
#include "LUtils/LUtils.cpp"


int main()
{
    std::cout << "scene\n";

    LScene scene = LScene();
    scene.addSphere("sphere1", 0, LUtils::LMath::Vec3_f(0, 0, 1), 1);
    scene.printScene();

    LUtils::LMath::Vec3_f rayo = LUtils::LMath::Vec3_f(0, 0, -1);
    LUtils::LMath::Vec3_f rayd = LUtils::LMath::Vec3_f(0, 0, -1);
    float rad = 1.0f;
    bool hit = scene.getObjects().at(scene.getNodes().back().getData()).getIntersection(rayo, rayd);
    if (hit)
        std::cout << "hit" << std::endl;
    else
        std::cout << "no hit" << std::endl;

    
}
