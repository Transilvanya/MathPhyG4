#pragma once
#include <vector>
#include "../../RigidBody/RigidBody.h"


class Node
{
public: 
    Node();
    explicit Node(Node* _parent);



    void setParent(Node* _parent);
    void setLeftChild(Node* leftChild);
    void setRightChild(Node* rightChild);
    void addRigidBody(RigidBody* r);
    void addRigidBodys(std::vector<RigidBody *> _bodys);

    Node* parent;
    Node* right;
    Node* left;
    std::vector<RigidBody*> bodys;

    void Display();
};

