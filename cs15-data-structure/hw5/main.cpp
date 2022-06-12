/*
 * Filename: main.cpp
 * Contains: Driver for homework 5 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Spring 2019
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SixDegrees.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    
    SixDegrees sd;
    if(argc == 1)
        sd.run(cin, cout);   

    else if (argc == 2){
        ifstream file;
        file.open(argv[1]);

        if (!file.is_open()){
        cerr << "Could not open " << argv[1] << " for reading\n";
        exit(1); // 要exit吗
        } 
        sd.run(file, cout);
    }
  
    else
    {
        cerr << "Input not recognizable." << endl; // 需要写什么？
    }
    
    return 0;
}
