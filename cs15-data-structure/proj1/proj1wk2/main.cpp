/*
 * main.cpp
 * Comp15
 * Spring 2019
 * proj1
 *
 * Author : Mengqi Irina Wang
 * Date: 3/12/2019
 */

#include <iostream>
#include <fstream>
#include <string>
#include "SequenceMatch.h"
using namespace std;


int main(int argc, char* argv[]){
    if(argc != 3){
        cerr << "Usage:  ./SeqMatch [query file] [output location]" << endl;
        exit(1); //quit
    }

    ifstream inFile; 
    ofstream outFile; // passFile
    inFile.open(argv[1]); 
    outFile.open(argv[2]);
    if(!inFile) { // if fail to open infile
        cerr <<  "ERROR: File cannot be opened " << endl;
        exit(1);
    }
    if(!outFile){ // if fail to open outfile
        cerr << " ERROR: File cannot be opened " << endl;
        exit(1);
    }

    SequenceMatch sequencematch(inFile,outFile);
    sequencematch.command();
    return 0;
}

