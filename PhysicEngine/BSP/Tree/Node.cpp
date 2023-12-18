#include "Node.h"

void Node::addRigidBody(RigidBody* r) {
    bodys.push_back(r);
}

void Node::addRigidBodys(std::vector<RigidBody*> _bodys)
{
    bodys.insert(bodys.end(), _bodys.begin(), _bodys.end());
}

Node::Node() {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    bodys = vector<RigidBody*>{};
}

Node::Node(Node* _parent) {
    parent = _parent;
    left = nullptr;
    right = nullptr;
    bodys = vector<RigidBody*>{};
}

void Node::Display() {
    // Display information about the node
    std::cout << "Node Information:" << std::endl;
    std::cout << "-----------------" << std::endl;

    if (bodys.empty()) {
        std::cout << "Le vecteur bodys est vide." << std::endl;
    }
    else {
        std::cout << "Le vecteur bodys n'est pas vide." << std::endl;
    }

    std::cout << "-----------------" << std::endl;
}

void Node::setParent(Node* _parent) {
    this->parent = _parent;
}

void Node::setRightChild(Node* rightChild) {
    right = rightChild;
}

void Node::setLeftChild(Node* leftChild) {
    left = leftChild;
}
