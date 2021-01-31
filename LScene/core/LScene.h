#pragma once
#include <iostream>
#include <iomanip>
#include "LSceneNode.h"
#include "LUtils/LUtils.cpp"

class LScene{
public:
	LScene();
	~LScene();
	
	//nodenr = parent node
	void printScene();
	void addNode(std::string _name);
	void addNode(std::string _name, unsigned int _nodenr);
	void addNode(std::string _name, NODETYPE _nodeType);
	void addNode(std::string _name, unsigned int _nodenr, NODETYPE _nodeType);

	void addSphere(std::string _name, unsigned int _nodenr, LUtils::LMath::Vec3_f _pos, float _radius);
	
	void deleteNode(int _node);
	void moveNode(int a, int b);

	std::vector<LSObject> getObjects();
	std::vector<LSceneNode> getNodes();

private:
	void printNode(LSceneNode _node, int _level);
	std::vector<LSceneNode> mNodes;
	int mNrNodes = 0;
	std::vector<LSObject> mObjects;
};



