#pragma once
#include "LSceneNode.h"
class LScene
{
public:
	LScene();
	~LScene();
	void printScene();
	void printNode(LSceneNode* _node);
private:
	std::vector<LSceneNode> mNodes;
	LSceneNode mRootNode;
};



