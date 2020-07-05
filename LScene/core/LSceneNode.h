#pragma once
#include <vector>
#include <string>
enum NODETYPE {
	LS_MODEL, LS_OBJECT, LS_LIGHT, LS_CAMERA 
};

class LSceneNode{
public:
	LSceneNode();
	LSceneNode(std::string _name);
	~LSceneNode();
	
	void addChild(int _node);
	void removeChild(int _node);
	void moveNode(int _newParent);
	
	int getParent();
	void setParent(int _parent);
	std::vector<int> getChildren();

	void setName(std::string _name);
	std::string getName();

	void setNodeNumber(int _n);
	int getNodeNumber();
private:
	int mParent = -1;
	std::vector<int> mChildren;
	std::string mName;
	int mNodeNumber = -1;
};

