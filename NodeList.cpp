#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    //Length of the NodeList is set to the starting index of 0
    length = 0;
}

NodeList::~NodeList(){
    //Loops through the NodeList and calls the Node deconstructer for each Node
    int len = this->getLength();
    for(int i=0; i<len; i++){
        delete(this->getNode(i));
    }
}

NodeList::NodeList(NodeList& other){
    //Loops through NodeList and makes a deep copy of each node. 
    length = 0;
    int len = other.getLength();
    for (int i = 0; i < len; i++ ){
        nodes[i] = new Node(*other.getNode(i));
        length++;
    }
}

int NodeList::getLength(){
    return this->length;
}

void NodeList::addElement(Node* newPos){
    //Adds new node and increases the node count (length) by 1
    nodes[length] = new Node(*newPos);

    length++;
}

Node* NodeList::getNode(int i){
    return nodes[i];
}