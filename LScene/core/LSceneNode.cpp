#include "LSceneNode.h"
LSceneNode::LSceneNode(){
}

LSceneNode::LSceneNode(std::string _name, NODETYPE _type = LS_DUMMY_NODE) {
	this->mName = _name;
	this->mType = _type;
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
NODETYPE LSceneNode::getType() {
	return this->mType;
}
std::string LSceneNode::getTypeName() {
	if (this->mType == LS_MODEL)
		return "LS_MODEL";
	else if (this->mType == LS_OBJECT)
		return "LS_OBJECT";
	else if (this->mType == LS_LIGHT)
		return "LS_LIGHT";
	else if (this->mType == LS_CAMERA)
		return "LS_CAMERA";
	else if (this->mType == LS_DUMMY_NODE)
		return "LS_DUMMY_NODE";
	else
		return "COULD NOT FIND TYPE";
}

std::string LSceneNode::printNode() {
	std::string data = "";
	if (this->mType == LS_MODEL)
		data = "LS_MODEL";
	else if (this->mType == LS_OBJECT)
		data = "LS_OBJECT";
	else if (this->mType == LS_LIGHT)
		data = "LS_LIGHT";
	else if (this->mType == LS_CAMERA)
		data = "LS_CAMERA";
	return this->mName + ": " + this->getTypeName() + ": " + std::to_string(this->mNodeNumber) + ": " + data;
}

void LSceneNode::setNodeNumber(int _n) {
	this->mNodeNumber = _n;
}

int LSceneNode::getNodeNumber() {
	return this->mNodeNumber;
}

void LSceneNode::addData(unsigned int _data) {
	this->mData = _data;
}

unsigned int LSceneNode::getData() {
	return this->mData;
}