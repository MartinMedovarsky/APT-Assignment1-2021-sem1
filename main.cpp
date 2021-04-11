#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

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
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    //std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
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

    NodeList* solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete exploredPositions;
    delete solution;
    delete pathSolver;

}

void readEnvStdin(Env env){
    //variable used to temporarily store each line of input
    string line;
    
    //Reads through input, stores into env
    for(int y=0; y < 20; y++){
        getline(cin, line);
        for(int x=0; x < 20; x++){
            env[y][x] = line[x];
        }
    }
}

void printEnvStdout(Env env, NodeList* solution) {
    //TODO

    int len = solution->getLength();

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
            current = next;
            next = solution->getNode(i+2);
        }
    }

    //Prints out edited env which displays solution
    for(int y=0; y < 20; y++){
        for(int x=0; x < 20; x++){
            cout << env[y][x];
        }
        cout << endl;
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