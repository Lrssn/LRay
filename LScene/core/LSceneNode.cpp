#include "LSceneNode.h"
LSceneNode::LSceneNode(){
}

LSceneNode::LSceneNode(std::string _name) {
}

LSceneNode::~LSceneNode(){
}

void LSceneNode::addChild(LSceneNode* _node) {
	this->mChildren.push_back(_node);
	_node->setChildNumber(this->mChildren.size());
}

void LSceneNode::moveNode(LSceneNode* _newParent) {
	this->mParent->removeChild(this);
	this->mParent = _newParent;
	_newParent->addChild(this);
}

void LSceneNode::removeChild(LSceneNode* _node) {
	this->mChildren.erase(mChildren.begin() + this->mChildNumber - 1);
}

LSceneNode* LSceneNode::getParent() {
	return this->mParent;
}

std::vector<LSceneNode*> LSceneNode::getChildren() {
	return this->mChildren;
}

void LSceneNode::setName(std::string _name){
	this->mName = _name;
}

std::string LSceneNode::getName()
{
	return this->mName;
}

void LSceneNode::setChildNumber(int _n) {
	this->mChildNumber = _n;
}
