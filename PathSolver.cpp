#include "PathSolver.h"
#include <iostream>
using std::cout;
using std::endl;

PathSolver::PathSolver(){
    // TODO
}

PathSolver::~PathSolver(){
    // TODO
}

void PathSolver::forwardSearch(Env env){
    // TODO 
    // Setting up vars for start and goal
    int startX = 0, startY = 0, goalX = 0, goalY = 0;

    //Calling method to find start and goal
    findStartGoal(env, &startX, &startY, &goalX, &goalY);

    //REMOVE LATER
    //cout << startX << ", " << startY << " | " << goalX << ", " << goalY << endl;
    //exit(EXIT_SUCCESS);
    //REMOVE ^^^
    //SOMETHING IS BACKWARDS WITH FINDING START / GOAL

    //Creating nodes for start and goal
    Node* start = new Node(startY, startX, 0);
    Node* goal = new Node(goalY, goalX, 0);

    NodeList* openList = new NodeList();
    openList->addElement(start);

    NodeList* closedList = new NodeList();

    // bool unsolved = true;
    // while (unsolved){

    // }

    //Need to find node from open not in closed
    //and smallest estimated distance

    //TESTING REMOVE LATER
    cout << "start: " << start->getRow() << ", " << start->getCol() << endl;
    cout << "goal: " << goal->getRow() << ", " << goal->getCol() << endl;

    cout << "testing nextOpenNode function" << endl;

    bool reachedGoal = false;

    while(reachedGoal == false){
        
        Node* nextNode = nextOpenNode(goal, openList, closedList);

        cout << "nextNode: " << nextNode->getCol() << ", " << nextNode->getRow() 
        << endl;

        //Arrays of coords for adjacent nodes (up,right,down,left)
        //Adjacent Postion X / Y
        const int adjCount = 4; 
        int adjPosX[adjCount] = {nextNode->getCol(), nextNode->getCol()+1,
        nextNode->getCol(), nextNode->getCol()-1};

        int adjPosY[adjCount] = {nextNode->getRow()-1, nextNode->getRow(),
        nextNode->getRow()+1 ,nextNode->getRow()};

        //TESTING REMOVE
        cout << "PRINTING ADJACENT NODES: " << endl;
        
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
        cout << "--------------CLOSED LIST UPDATED----------------" << endl;

        if (nodeEquals(nextNode, goal)){
            reachedGoal = true;
        }

    }

    //Setting nodes explored to point to the closed list. 
    this->nodesExplored = new NodeList();
    this->nodesExplored = closedList;
    //cout << "Lengtha: " << this->nodesExplored->getLength() << endl;

    Node* bigtester = nodesExplored->getNode(1);

    cout << "NODESEXPLORED TEST:" << bigtester->getCol() << ", " << bigtester->getRow() << endl;
    cout << "LENGTH: " << nodesExplored->getLength();

    //TESTING MUST DELETE WHOLE BLOCK Print out the NodeList
    cout << "PRINTING OUT OPENLIST:" << endl;
    int len = openList->getLength();
    for (int i=0; i < len; i++){
        Node* current = openList->getNode(i);
        cout << "Node " << i << ": " << endl;
        cout << "Row: " << current->getRow() << ", ";
        cout << "Col: " << current->getCol() << ", ";
        cout << "DisTrav: " << current->getDistanceTraveled() << endl;
        cout << "----------------------------" << endl;
    }

    cout << "PRINTING OUT CLOSEDLIST:" << endl;
    len = closedList->getLength();
    for (int i=0; i < len; i++){
        Node* current = closedList->getNode(i);
        cout << "Node " << i << ": " << endl;
        cout << "Row: " << current->getRow() << ", ";
        cout << "Col: " << current->getCol() << ", ";
        cout << "DisTrav: " << current->getDistanceTraveled() << endl;
        cout << "----------------------------" << endl;
    }

    //delete openList;
    //delete closedList;
}

void PathSolver::findStartGoal(Env env, int *sX, int *sY, int *gX, int *gY){

    //Loop to find start and goal
    for(int y=0; y < 20; y++){
        for(int x=0; x < 20; x++){
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
    int openLen = oList->getLength();
    int closedLen = cList->getLength();

    int smallestDist = NODE_LIST_ARRAY_MAX_SIZE;
    int nextNodeIndex = 0;
    
    if (oList->getLength() == 1){
        return oList->getNode(0);
    } else {

        for (int i=0; i<openLen; i++){
            Node* openNode = oList->getNode(i);
            cout << "printing open List: " << openNode->getCol() 
            << ", " << openNode->getRow() << ", " << openNode->getDistanceTraveled() << endl;
            cout << "EST DIST TO GOAL: " << openNode->getEstimatedDist2Goal(goal) << endl;

            int tempSmallestDist = smallestDist;
            int tempNextNodeIndex = nextNodeIndex;
            bool present = false;

            for (int l=0; l<closedLen; l++){
                Node* closedNode = cList->getNode(l);

                //NEED TO EXIT LOOP IF CONDITION IS MET STOOOGE
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

    cout << "smallest dist: " << smallestDist << "next node" << nextNodeIndex << endl;
    return oList->getNode(nextNodeIndex);
 
}

bool PathSolver::nodeEquals(Node* openNode, Node* closedNode){
    if(openNode->getCol() == closedNode->getCol()){
        if(openNode->getRow() == closedNode->getRow()){
            cout << "Match found!" << endl;
            return true;
        }
    }
    return false;
}

NodeList* PathSolver::getNodesExplored(){
    //TODO
    //TEMP RETURN VVV
    Node* tester = new Node(*nodesExplored->getNode(1));
    cout << "EGSIODFSGV: " << tester->getCol() << ", " << tester->getRow() << endl;

    return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env){
    // TODO
    //TEMP RETURN VVV
    return new NodeList();
}

//-----------------------------