#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    //Method used to find coods of start and goal
    //Returns information through call by address
    void findStartGoal(Env env, int *sX, int *sY, int *gX, int *gY);

    //Method used to find the node with the smallest estimated distance
    //in the open list but not in the closed list
    Node* nextOpenNode(Node* goal, NodeList* oList, NodeList* cList);

    //Method given two nodes and compares the node values to see if they are
    //equivalent to each other.
    bool nodeEquals(Node* openNode, Node* closedNode);


private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    // Nodes representing solution from start to goal
    NodeList* solution;
    
};




#endif //COSC_ASSIGN_ONE_PATHSOLVER