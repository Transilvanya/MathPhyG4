#include "BSP.h"
#include "Plan.h"



BSP::BSP(vector<RigidBody*> bodys)
{
	root = Node();
	root.addRigidBodys(bodys);
}



Node* BSP::orderByCenter(Node* root, int iteration)
{
    iteration++;
    int maxDepth = 10;

    //init
    Node* pRight = new Node(root);
    Node* pLeft = new Node(root);

    std::vector<RigidBody*> points = vector<RigidBody*>(root->bodys); //liste de points à traité

    //recursion
    if (iteration < maxDepth && root->bodys.size() > 1) {
        std::vector<RigidBody*> fp = furthestPoints(points);
        Plan cuttingPlan(fp.at(0), fp.at(1));
        for (auto point : points) {
            cuttingPlan.isAreaOnPositiveSide(point);
            if (cuttingPlan.isPointOnPositiveSide(point)) {
                pRight->addRigidBody(point);
            }
            else {
                pLeft->addRigidBody(point);
            }
        }
        root->bodys.clear();
        root->setRightChild(pRight);
        root->setLeftChild(pLeft);
        orderByCenter(pRight, iteration);
        orderByCenter(pLeft, iteration);
    }

    //sortie
    return root;
}

Node* BSP::orderByArea(Node* root, int iteration)
{
    iteration++;
    int maxDepth = 10;

    //init
    Node* pRight = new Node(root);
    Node* pLeft = new Node(root);

    std::vector<RigidBody*> rigidBodies = vector<RigidBody*>(root->bodys); //liste de points à traité

    //recursion
    if (iteration < maxDepth && root->bodys.size() > 1) {
        std::vector<RigidBody*> fp = furthestPoints(rigidBodies);
        Plan cuttingPlan(fp.at(0), fp.at(1));
        for (auto rigidBody : rigidBodies) {
            if (cuttingPlan.isAreaOnPositiveSide(rigidBody)==2) {
                pRight->addRigidBody(rigidBody);
                pLeft->addRigidBody(rigidBody);
            }
            else if (cuttingPlan.isAreaOnPositiveSide(rigidBody)) {
                pRight->addRigidBody(rigidBody);
            }
            else {
                pLeft->addRigidBody(rigidBody);
            }
        }
        root->bodys.clear();
        root->setRightChild(pRight);
        root->setLeftChild(pLeft);
        orderByCenter(pRight, iteration);
        orderByCenter(pLeft, iteration);
    }

    //sortie
    return root;
}

list<pair<RigidBody*,RigidBody*>> BSP::getPotentialCollision()
{
    orderByArea(&root, 0);
    list<pair<RigidBody*, RigidBody*>> potentialCollision = list<pair<RigidBody*, RigidBody*>>();
    potentialCollision = parcoursPrefixe(&root);
    return potentialCollision;
}

std::vector<RigidBody*> BSP::furthestPoints(const std::vector<RigidBody*>& bodys)
{

    std::vector<RigidBody*> furthestPoints;

    float max_distance = 0;


    for (int it1 = 0; it1 < bodys.size(); it1++) {
        for (int it2 = 0; it2 < bodys.size(); it2++) {
            float dist = distance(bodys.at(it1), bodys.at(it2));
            if (dist > max_distance) {
                max_distance = dist;
                furthestPoints.clear();
                furthestPoints.push_back(bodys.at(it1));
                furthestPoints.push_back(bodys.at(it2));
            }
        }
    }





	return furthestPoints;
}

float BSP::distance(RigidBody *r1, RigidBody* r2)
{
    Vector3D position1 = r1->getPosition();
    Vector3D position2 = r2->getPosition();

	return sqrt(pow((position1.getX() - position2.getX()), 2) + 
		pow((position1.getY() - position2.getY()), 2) + 
		pow((position1.getZ() - position2.getZ()), 2));

	
}

list<RigidBody*> BSP::getSameAndLowerLevelChild(Node* child)
{

    list<RigidBody*> childs = list<RigidBody*>();
    
    if (child->parent == nullptr) return childs;
    
    Node* parent = child->parent;
    Node* otherChild;

    if (parent->left == child) otherChild = parent->right;
    else otherChild = parent->left;

    vector<RigidBody*> bodys = otherChild->bodys; // get and RigidBody list
  
    // two case if empty continue get lower in tree than add bodys to childs
    if (bodys.size() == 0) {

        for (RigidBody * body : getAllRigidBody(otherChild)) {
            childs.push_back(body);
        }


    }
    else {
        for (RigidBody* body : bodys) {
            childs.push_back(body);
        }
    }

    return childs;
}

list<RigidBody*> BSP::getAllRigidBody(Node* parent)
{
    list<RigidBody*> childs = list<RigidBody*>();

    Node* left = parent->left;
    Node* right = parent->right;
    if (parent->bodys.size() != 0) {
        for (RigidBody* body : getAllRigidBody(left)) {
            childs.push_back(body);
        }
    }
    else {
        for (RigidBody* body : left->bodys) {
            childs.push_back(body);
        }
    }

    if (right->bodys.size() == 0) {
        for (RigidBody* body : getAllRigidBody(right)) {
            childs.push_back(body);
        }
    }
    else {
        for (RigidBody* body : right->bodys) {
            childs.push_back(body);
        }
    }

    return childs;
}


list<pair<RigidBody*, RigidBody*>> BSP::parcoursPrefixe(Node* root) {
    list<pair<RigidBody*, RigidBody*>> returnValue = list<pair<RigidBody*, RigidBody*>>();

    for (RigidBody * rootRigidBodies : root->bodys) {
        for (RigidBody * pairRigidBodies : getSameAndLowerLevelChild(root)) {

            pair<RigidBody*, RigidBody*> pairs = pair<RigidBody*, RigidBody*>(rootRigidBodies, pairRigidBodies);

            returnValue.push_back(pairs);
        }
    }


    if (root->left != nullptr) {
        list<pair<RigidBody*, RigidBody*>> leftValue = list<pair<RigidBody*, RigidBody*>>();
        leftValue = parcoursPrefixe(root->left);   // Parcours du sous-arbre gauche
        for (pair<RigidBody*, RigidBody*> p : leftValue) {
            
            
            bool isPresent = false;
            for (pair<RigidBody*, RigidBody*> r : returnValue) {
                if ((p.second == r.second && p.first == r.first) || (p.first == r.second && p.second == r.first)) isPresent = true;
            }
            if (!isPresent)returnValue.push_back(p);
        }
    }
    if (root->right != nullptr) {
        list<pair<RigidBody*, RigidBody*>> rightValue = list<pair<RigidBody*, RigidBody*>>();
        rightValue = parcoursPrefixe(root->right);  // Parcours du sous-arbre droit

        for (pair<RigidBody*, RigidBody*> p : rightValue) {
            bool isPresent = false;
            for (pair<RigidBody*, RigidBody*> r : returnValue) {
                if ((p.second == r.second && p.first == r.first) || (p.first == r.second && p.second == r.first)) isPresent = true;
            }
            if (!isPresent)returnValue.push_back(p);
        }


    }
    return returnValue;
}