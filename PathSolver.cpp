#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
}

PathSolver::~PathSolver(){
    delete this->nodesExplored;
    delete this->solution;
}

void PathSolver::forwardSearch(Env env){
    // Setting up vars for start and goal
    int startX = 0, startY = 0, goalX = 0, goalY = 0;

    //Calling method to find start and goal
    findStartGoal(env, &startX, &startY, &goalX, &goalY);

    //Creating nodes for start and goal
    Node* start = new Node(startY, startX, 0);
    Node* goal = new Node(goalY, goalX, 0);

    //Creating openList to store accessible nodes
    NodeList* openList = new NodeList();
    //Adding the start to the openList
    openList->addElement(start);

    //Creating the closedList to store visited node
    NodeList* closedList = new NodeList();

    bool reachedGoal = false;

    //While Loop contains logic used to search for adjacent nodes and add
    //them to the closed and open lists as needed
    while(reachedGoal == false){
        
        //Represents the node that is being 
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
                delete adjacent;
            }
        }

        //adding the visited node to the closedList
        closedList->addElement(nextNode);

        //Checking if the goal node has been reached, and if so ending loop
        if (nodeEquals(nextNode, goal)){
            reachedGoal = true;
        }

    }

    //Setting nodes explored to point to the closed list. 
    this->nodesExplored = new NodeList(*closedList);

    delete start;
    delete goal;
    delete openList;
    delete closedList;
}

void PathSolver::findStartGoal(Env env, int *sX, int *sY, int *gX, int *gY){

    //Loop to find start and goal
    for(int y=0; y < 20; y++){
        for(int x=0; x < 20; x++){

            //Checks if the env position is a start or goal and gives the values
            //of start / goal to pointers. sX refers to start x coordinate.
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

    //inialising the smallest with the greatest possible distance.
    int smallestDist = NODE_LIST_ARRAY_MAX_SIZE;
    int nextNodeIndex = 0;
    
    //Checks if only goal is present, and returns the goal
    if (oList->getLength() == 1){
        return oList->getNode(0);
    } else {

        //Loops through openList and finds the most suitable next node
        for (int i=0; i<openLen; i++){

            //stores the currently itereated node
            Node* openNode = oList->getNode(i);
            
            //stores the values of next potential node with smallest distance
            //This is done instead of immidately replacing if as the node
            //needs to pass further checks (make sure its not in closed list)
            int tempSmallestDist = smallestDist;
            int tempNextNodeIndex = nextNodeIndex;
            bool present = false;

            for (int l=0; l<closedLen; l++){
                Node* closedNode = cList->getNode(l);

                //Checking that 
                if (nodeEquals(openNode, closedNode) != true){
                    if (openNode->getEstimatedDist2Goal(goal) < smallestDist){
                        tempSmallestDist= openNode->getEstimatedDist2Goal(goal);
                        tempNextNodeIndex = i;
                    }
                } else {
                    present = true; 
                }
            }
            
            //Sets the smallest node values after the loop has concluded
            if (present == false){
                smallestDist = tempSmallestDist;
                nextNodeIndex = tempNextNodeIndex;
            }

        }
    }

    return oList->getNode(nextNodeIndex);
 
}

bool PathSolver::nodeEquals(Node* openNode, Node* closedNode){
    //Checks if columns are same then if rows are too
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

                    if(nodeEquals(currentNode,adjacent)){
                        if (currentNode->getDistanceTraveled() < smallestDist){
                            nextNode = currentNode;
                            smallestDist = currentNode->getDistanceTraveled();
                        }
                    } 
                }
                delete adjacent;
            }
        }
        BWsolution->addElement(nextNode);

        //ending the loop when the shortest path reaches the start
        if(nodeEquals(nextNode,nodesExplored->getNode(0))){
                unsolved = false;
        }

    }

    //New nodeList with correct ordering
    this->solution = new NodeList();

    int bwLen = BWsolution->getLength();
    //Loop through the BWsolution backwards and add each node to solution
    for(int i=bwLen-1; i >= 0; i--){
        solution->addElement(BWsolution->getNode(i));
    }

    delete BWsolution;

    return new NodeList(*solution);
}