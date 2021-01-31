#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "../objects/LSObjectSphere.h"
enum NODETYPE {
	LS_DUMMY_NODE, LS_MODEL, LS_OBJECT, LS_LIGHT, LS_CAMERA  //set in getTypeName()
};

class LSceneNode{
public:
	LSceneNode();
	LSceneNode(std::string _name, NODETYPE _type );
	~LSceneNode();
	
	void addChild(int _node);
	void removeChild(int _node);
	void moveNode(int _newParent);
	
	int getParent();
	void setParent(int _parent);
	std::vector<int> getChildren();

	void setName(std::string _name);
	std::string getName();

	NODETYPE getType();
	std::string getTypeName();

	void setNodeNumber(int _n);
	int getNodeNumber();

	std::string printNode();
	void addData(unsigned int _data);
	unsigned int getData();

private:
	unsigned int mData;
	int mParent = -1;
	std::vector<int> mChildren;
	std::string mName;
	NODETYPE mType;
	int mNodeNumber = -1;
};

