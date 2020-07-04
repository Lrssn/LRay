#pragma once
#include <vector>
#include <string>
enum NODETYPE {
	LS_MODEL, LS_OBJECT, LS_LIGHT, LS_CAMERA //polygonmodel, explicit model?
};

class LSceneNode{
public:
	LSceneNode();
	LSceneNode(std::string _name);
	~LSceneNode();
	
	void addChild(LSceneNode* _node);
	void moveNode(LSceneNode* _newParent);
	void removeChild(LSceneNode* _node);
	LSceneNode* getParent();
	std::vector<LSceneNode*> getChildren();

	void setName(std::string _name);
	std::string getName();

	void setChildNumber(int _n);

private:
	LSceneNode* mParent;
	std::vector<LSceneNode*> mChildren;
	std::string mName;
	int mChildNumber = 0;
};

