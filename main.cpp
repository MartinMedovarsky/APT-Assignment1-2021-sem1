//Description and Analysis:
//When attempting this assignment I used a systematic approach, analyising each
//task one by one, and breaking down large problems into smaller subsets.
//This can be seen through the way in which I created multiple helper methods in
//NodeList.cpp in order to make the process of the forward search more semantic
//and easier to understand. An example of a helper method used multiple times
//was NodeEquals(), which is given two nodes, compares them and returns a 
//boolean value depending on if they have the same coordinates.
//While programming I encountered several minor issues, often being syntactic
//errors where accidently compared similar but incorrect values (eg. col 
//instead of row) or off by one errors. I also encountered some code duplication
//issues with the logic used to find adjacent nodes. Code was modified and
//repurposed later for a slightly different use, however creating a method to
//help reduce code duplication may have been advantageous.

//NOTE THAT ML4_large.env IS A TEST FOR MILESTONE 4 WHICH I HAVE NOT IMPLEMENTED


#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

//Importing elements from namespace for more succinct code
using std::cout;
using std::endl;
using std::cin;
using std::string;

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    
    //testNode();
    //testNodeList();
    //std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    //NodeList to stores the env solution, is used to help cout the soultion
    NodeList* solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete exploredPositions;
    delete solution;
    delete pathSolver;

}

void readEnvStdin(Env env){
    //variable used to temporarily store each line of input
    string line;
    
    //Reads through input, stores maze into env
    for(int y=0; y < 20; y++){
        getline(cin, line);
        for(int x=0; x < 20; x++){
            env[y][x] = line[x];
        }
    }
}

void printEnvStdout(Env env, NodeList* solution) {

    //shorthand storage of the solution's NodeList length
    int len = solution->getLength();

    //variables storing a node and the following node in the solution
    Node* current = solution->getNode(1);
    Node* next = solution->getNode(2);

    //Loops through solutions and edits ENV with arrows to display solution
    for(int i=0; i<len-1; i++){
        if(next->getCol() > current->getCol()){
            env[current->getRow()][current->getCol()] = '>';
        } else if (next->getCol() < current->getCol()){
            env[current->getRow()][current->getCol()] = '<';
        } else if (next->getRow() > current->getRow()){
            env[current->getRow()][current->getCol()] = 'v';
        } else {env[current->getRow()][current->getCol()] = '^';}

        //checks where the loop is upto and prevents accessing non-existent node
        if (i == len-1){   
        } else {

            //Changing nodes to represent next iteration in the solution
            current = next;
            next = solution->getNode(i+2);
        }
    }

    //Array size constants
    const int lineLen = 20;
    const int lastLine = 19;

    //Prints out edited env which displays solution
    for(int y=0; y < lineLen; y++){
        for(int x=0; x < lineLen; x++){
            cout << env[y][x];
        }
        
        //Checks if loop has reached last line, stops newline being added
        if (y == lastLine){
        } else {
            cout << endl;
        }
    }

}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST:" << std::endl;
    int leng = nodeList->getLength();
    for (int i=0; i < leng; i++){
        Node* current = nodeList->getNode(i);
        std::cout << "Node " << i << ": " << std::endl;
        std::cout << "Row: " << current->getRow() << ", ";
        std::cout << "Col: " << current->getCol() << ", ";
        std::cout << "DisTrav: " << current->getDistanceTraveled() << std::endl;
        std::cout << "----------------------------" << std::endl;
    }

    delete b1;
    delete b2;
    delete nodeList;

}