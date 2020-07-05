#include <iostream>
#include "core/LScene.h"


int main()
{
    std::cout << "scene\n";

    LScene scene = LScene();
    scene.addNode("A");
    scene.addNode("B"); 
    scene.addNode("C"); 
    scene.addNode("D"); 
    scene.addNode("E");

    scene.printScene();
    
}
