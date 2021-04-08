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
    std::cout << "len: " << len << std::endl;
    for (int i = 0; i < len; i++ ){
        nodes[i] = new Node(*other.getNode(i));
        length++;
        std::cout << "TESTING COPYCONSTRUCTYER" << std::endl;
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