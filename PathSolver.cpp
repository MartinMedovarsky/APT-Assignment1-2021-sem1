#include "PathSolver.h"
#include <iostream>
using std::cout;
using std::endl;

PathSolver::PathSolver(){
}

PathSolver::~PathSolver(){
}

void PathSolver::forwardSearch(Env env){
    // Setting up vars for start and goal
    int startX = 0, startY = 0, goalX = 0, goalY = 0;

    //Calling method to find start and goal
    findStartGoal(env, &startX, &startY, &goalX, &goalY);

    //Creating nodes for start and goal
    Node* start = new Node(startY, startX, 0);
    Node* goal = new Node(goalY, goalX, 0);

    NodeList* openList = new NodeList();
    openList->addElement(start);

    NodeList* closedList = new NodeList();

    bool reachedGoal = false;

    while(reachedGoal == false){
        
        Node* nextNode = nextOpenNode(goal, openList, closedList);

        //Arrays of coords for adjacent nodes (up,right,down,left)
        //Adjacent Postion X / Y
        const int adjCount = 4; 
        int adjPosX[adjCount] = {nextNode->getCol(), nextNode->getCol()+1,
        nextNode->getCol(), nextNode->getCol()-1};

        int adjPosY[adjCount] = {nextNode->getRow()-1, nextNode->getRow(),
        nextNode->getRow()+1 ,nextNode->getRow()};
        
        //Looping through adjacent env elements.
        for(int i=0; i < adjCount; i++){
            char possibleNode = env[adjPosY[i]][adjPosX[i]];
            //Checking that char is accessible 
            if (possibleNode != '='){
                Node* adjacent = new Node(adjPosY[i], adjPosX[i],
                nextNode->getDistanceTraveled() + 1);

                //Checking that the adjacent node isn't already in the openList
                int len = openList->getLength();
                bool present = false;
                for (int l=0; l<len; l++){
                    Node* openNode = openList->getNode(l);

                    if (nodeEquals(adjacent, openNode)){
                        present = true;
                    }
                }
                
                //Adds node if not already in openList
                if (present != true){
                    openList->addElement(adjacent);
                }
            }
        }
        closedList->addElement(nextNode);

        if (nodeEquals(nextNode, goal)){
            reachedGoal = true;
        }

    }

    //Setting nodes explored to point to the closed list. 
    this->nodesExplored = new NodeList();
    this->nodesExplored = closedList;

    //delete openList;
    //delete closedList;
}

void PathSolver::findStartGoal(Env env, int *sX, int *sY, int *gX, int *gY){

    //Loop to find start and goal
    for(int y=0; y < 20; y++){
        for(int x=0; x < 20; x++){
            //Gives the values of start / goal to pointers
            if (env[y][x] == 'S'){
                *sX = x;
                *sY = y;
            } else if (env[y][x] == 'G'){
                *gX = x;
                *gY = y;
            }
        }
    }
}

Node* PathSolver::nextOpenNode(Node* goal, NodeList* oList, NodeList* cList){
    //Setting variables with the lengths of each list
    int openLen = oList->getLength();
    int closedLen = cList->getLength();

    int smallestDist = NODE_LIST_ARRAY_MAX_SIZE;
    int nextNodeIndex = 0;
    
    //special case for first method call
    if (oList->getLength() == 1){
        return oList->getNode(0);
    } else {

        //Loops through open list and 
        for (int i=0; i<openLen; i++){
            Node* openNode = oList->getNode(i);
            
            int tempSmallestDist = smallestDist;
            int tempNextNodeIndex = nextNodeIndex;
            bool present = false;

            for (int l=0; l<closedLen; l++){
                Node* closedNode = cList->getNode(l);

                if (nodeEquals(openNode, closedNode) != true){
                    if (openNode->getEstimatedDist2Goal(goal) < smallestDist){
                        tempSmallestDist= openNode->getEstimatedDist2Goal(goal);
                        tempNextNodeIndex = i;
                    }
                } else {
                    present = true; 
                }
            }

            if (present == false){
                smallestDist = tempSmallestDist;
                nextNodeIndex = tempNextNodeIndex;
            }

        }
    }

    return oList->getNode(nextNodeIndex);
 
}

bool PathSolver::nodeEquals(Node* openNode, Node* closedNode){
    //Checks if columns are same then if rows are
    if(openNode->getCol() == closedNode->getCol()){
        if(openNode->getRow() == closedNode->getRow()){
            return true;
        }
    }
    return false;
}

NodeList* PathSolver::getNodesExplored(){
    return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env){
    NodeList* nodesExplored = getNodesExplored();
    int len = nodesExplored->getLength();

    //Backwards solution, gets path nodes added to it
    NodeList* BWsolution = new NodeList();

    Node* nextNode = nodesExplored->getNode(len-1);
    BWsolution->addElement(nextNode);

    int smallestDist = nextNode->getDistanceTraveled();

    bool unsolved = true;
    while (unsolved) {
        //Arrays of coords for adjacent nodes (up,right,down,left)
        //Adjacent Postion X / Y
        const int adjCount = 4; 
        int adjPosX[adjCount] = {nextNode->getCol(), nextNode->getCol()+1,
        nextNode->getCol(), nextNode->getCol()-1};

        int adjPosY[adjCount] = {nextNode->getRow()-1, nextNode->getRow(),
        nextNode->getRow()+1 ,nextNode->getRow()};

        //Looping through adjacent env elements.
        for(int i=0; i < adjCount; i++){
            char possibleNode = env[adjPosY[i]][adjPosX[i]];
            //Checking that char is accessible 
            if (possibleNode != '='){
                Node* adjacent = new Node(adjPosY[i], adjPosX[i],
                nextNode->getDistanceTraveled()-1);

                //Loop through nodesExplored backwards
                for(int l = len-1; l >= 0; l--){
                    //Checks that the adjacent node is present in nodesExplored
                    Node* currentNode = nodesExplored->getNode(l);

                    cout << adjacent->getCol() << ", " << adjacent->getRow() << endl;

                    if(nodeEquals(currentNode,adjacent)){
                        if (currentNode->getDistanceTraveled() < smallestDist){
                            nextNode = currentNode;
                            smallestDist = currentNode->getDistanceTraveled();
                        }
                    } 
                }
            }
        }
        BWsolution->addElement(nextNode);

        if(nodeEquals(nextNode,nodesExplored->getNode(0))){
                unsolved = false;
        }

    }

    //New nodeList with correct ordering
    NodeList* solution = new NodeList();

    int bwLen = BWsolution->getLength();
    //Loop through the BWsolution backwards and add each node to solution
    for(int i=bwLen-1; i >= 0; i--){
        solution->addElement(BWsolution->getNode(i));
    }

    return new NodeList(*solution);
}