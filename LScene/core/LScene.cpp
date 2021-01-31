#include "LScene.h"

LScene::LScene(){
	this->mNodes.push_back(LSceneNode("ROOT", LS_DUMMY_NODE));
	this->mNodes.front().setNodeNumber(0);
	mNrNodes++;
}

LScene::~LScene(){
}

void LScene::printScene() {
	this->printNode(this->mNodes.front(), 0);
}
void LScene::addNode(std::string _name) {
	addNode(_name, 0, LS_DUMMY_NODE);
}
void LScene::addNode(std::string _name, unsigned int _nodenr) {
	addNode(_name, _nodenr, LS_DUMMY_NODE);
}
void LScene::addNode(std::string _name, NODETYPE _nodeType) {
	addNode(_name, 0, _nodeType);
}
void LScene::addNode(std::string _name, unsigned int _nodenr, NODETYPE _nodeType) {
	this->mNodes.push_back(LSceneNode(_name, _nodeType));
	this->mNodes.back().setParent(_nodenr);
	this->mNodes.back().setNodeNumber(this->mNrNodes);
	mNrNodes++;
	this->mNodes.at(_nodenr).addChild(this->mNodes.back().getNodeNumber());
}

void LScene::addSphere(std::string _name, unsigned int _nodenr, LUtils::LMath::Vec3_f _pos, float _radius) {
	LSObjectSphere sphere(_radius, _pos);
	this->mObjects.push_back(sphere);
	addNode(_name, _nodenr, LS_OBJECT);
	this->mNodes.back().addData(this->mObjects.size());
}

std::vector<LSObject> LScene::getObjects() {
	return this->mObjects;
}

std::vector<LSceneNode> LScene::getNodes() {
	return this->mNodes;
}

void LScene::deleteNode(int _node) {
	if (_node == 0) {
		std::cout << "YOU CAN NOT REMOVE ROOT" << std::endl;
		return;
	}
	for (int i = 0; i < this->mNodes.at(_node).getChildren().size(); i++) {
		this->mNodes.at(this->mNodes.at(_node).getParent()).addChild(this->mNodes.at(_node).getChildren().at(i));
		this->mNodes.at(this->mNodes.at(_node).getChildren().at(i)).setParent(this->mNodes.at(_node).getParent());
	}
	this->mNodes.at(this->mNodes.at(_node).getParent()).removeChild(_node);
}

void LScene::moveNode(int a, int b) {
	if (a == 0) {
		std::cout << "YOU CAN NOT MOVE ROOT" << std::endl;
		return;
	}
	if (a == b) {
		std::cout << "YOU CAN NOT MOVE A NODE UNDER ITSELF" << std::endl;
		return;
	}
	if (b > this->mNrNodes){
		std::cout << "This Node does not exist so nodes can not be moved under it" << std::endl;
		return;
	}
	if (a > this->mNrNodes) {
		std::cout << "This Node does not exist so it can not be moved" << std::endl;
		return;
	}
	this->mNodes.at(this->mNodes.at(a).getParent()).removeChild(a);
	this->mNodes.at(a).setParent(b);
	this->mNodes.at(b).addChild(a);
}

void LScene::printNode(LSceneNode _node, int _level) {
	std::cout << std::setw(_level * 4) << _node.printNode() << std::endl;
 	if (_node.getChildren().size() > 0) {
		for (int i = 0; i < _node.getChildren().size(); i++) {
			this->printNode(this->mNodes.at(_node.getChildren().at(i)), _level + 1);
		}
	}
	
}
