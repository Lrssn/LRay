#pragma once
#include <iostream>
#include <iomanip>

#include "LSceneNode.h"
class LScene{
public:
	LScene();
	~LScene();
	
	void printScene();

	void addNode(std::string _name);
	void deleteNode(int _node);
	void moveNode(int a, int b);
private:
	void printNode(LSceneNode _node, int _level);
	std::vector<LSceneNode> mNodes;
	int mNrNodes = 0;
};



