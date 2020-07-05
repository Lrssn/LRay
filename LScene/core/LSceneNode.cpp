#include "LSceneNode.h"
LSceneNode::LSceneNode(){
}

LSceneNode::LSceneNode(std::string _name) {
	this->mName = _name;
}

LSceneNode::~LSceneNode(){
}

void LSceneNode::addChild(int _node) {
	this->mChildren.push_back(_node);
}

void LSceneNode::removeChild(int _node) {
	for (int i = 0; i < this->mChildren.size(); i++) {
		if (this->mChildren.at(i) == _node) {
			this->mChildren.erase(mChildren.begin() + i);
		}
	}
}

void LSceneNode::moveNode(int _newParent) {

	this->mParent = _newParent;
}

int LSceneNode::getParent() {
	return this->mParent;
}

void LSceneNode::setParent(int _parent) {
	this->mParent = _parent;
}

std::vector<int> LSceneNode::getChildren() {
	return this->mChildren;
}

void LSceneNode::setName(std::string _name){
	this->mName = _name;
}

std::string LSceneNode::getName()
{
	return this->mName;
}

void LSceneNode::setNodeNumber(int _n) {
	this->mNodeNumber = _n;
}

int LSceneNode::getNodeNumber() {
	return this->mNodeNumber;
}
