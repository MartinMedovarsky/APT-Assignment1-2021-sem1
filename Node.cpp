#include "Node.h"
#include <iostream>
#include <cmath>


Node::Node(int row, int col, int dist_traveled):
    row(row),
    col(col),
    dist_traveled(dist_traveled)
{
    // TODO
}

//Custom Method
//Create copy of a node (for nodelist)
Node::Node(Node &other):
    row(other.row),
    col(other.col),
    dist_traveled(other.dist_traveled)
{

}

Node::~Node(){
    // TODO
}

int Node::getRow(){
    // TODO
    return row;
}

int Node::getCol(){
    // TODO
    return col;
}

int Node::getDistanceTraveled(){
    // TODO
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    // TODO
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    // TODO
    //First must calculate manhattan distance
    //Abs method gives absolute values
    int colDiff = std::abs(col - goal->getCol());
    int rowDiff = std::abs(row - goal->getRow());
    int manHat = colDiff + rowDiff;

    //Add dist_traveled and manhattan distance to find estimated dist
    return dist_traveled + manHat;
}
    
//--------------------------------                             