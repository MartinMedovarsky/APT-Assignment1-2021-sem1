#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    // TODO
    length = 0;
}

NodeList::~NodeList(){
    // TODO
}

NodeList::NodeList(NodeList& other){
    // TODO
    length = 0;
    int len = other.getLength();
    for (int i = 0; i < len; i++ ){
        nodes[i] = new Node(*other.getNode(i));
        length++;
    }
}

int NodeList::getLength(){
    // TODO
    return this->length;
}

void NodeList::addElement(Node* newPos){
    // TODO
    nodes[length] = new Node(*newPos);

    length++;
}

Node* NodeList::getNode(int i){
    // TODO
    return nodes[i];
}