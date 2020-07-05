#include "LScene.h"

LScene::LScene(){
	this->mNodes.push_back(LSceneNode("ROOT"));
	this->mNodes.front().setNodeNumber(0);
	mNrNodes++;
}

LScene::~LScene(){
}

void LScene::printScene() {
	this->printNode(this->mNodes.front(), 0);
}

void LScene::addNode(std::string _name) {
	this->mNodes.push_back(LSceneNode(_name));
	this->mNodes.back().setParent(0);
	this->mNodes.back().setNodeNumber(this->mNrNodes);
	mNrNodes++;
	this->mNodes.at(0).addChild(this->mNodes.back().getNodeNumber());
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
	this->mNodes.at(this->mNodes.at(a).getParent()).removeChild(a);
	this->mNodes.at(a).setParent(b);
	this->mNodes.at(b).addChild(a);
}

void LScene::printNode(LSceneNode _node, int _level) {
	std::cout << std::setw(_level * 4) << _node.getName() << " : " << _node.getNodeNumber() << std::endl;
 	if (_node.getChildren().size() > 0) {
		for (int i = 0; i < _node.getChildren().size(); i++) {
			this->printNode(this->mNodes.at(_node.getChildren().at(i)), _level + 1);
		}
	}
	
}
