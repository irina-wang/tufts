#include <iostream>
#include <fstream>
#include <string>
#include "MetroSim.h"
using namespace std;

const int MAX_ARGC = 4; // argc counts the file name as one as well
const int MIN_ARGC = 3;

int main(int argc, char* argv[]){
    if((argc  != MAX_ARGC) && (argc != MIN_ARGC)){
        cerr << "Usage: MetroSim stationFile passFile [commands]" << endl;
        exit(1); //quit
    }
    ifstream inFile; 
    ofstream outFile; // passFile
    inFile.open(argv[1]); // stationfile
    outFile.open(argv[2]);
    if(!inFile) { // if fail to open infile
        cerr << "Fail to open " << argv[1] << endl;
        exit(1);
    }
    if(!outFile){ // if fail to open outfile
        cerr << "Fail to open " << argv[2] << endl;
        exit(1);
    }
    if(argc == MIN_ARGC) { // Read command in from cin
        MetroSim metro(inFile,outFile,cin);
        metro.ReadInCommand();
    } else if(argc == MAX_ARGC) { // Read command in from the file
        ifstream CommandFile; 
        CommandFile.open(argv[3]);
        if(!CommandFile) { // if fail to open commandfile
            cerr << "Fail to open " << argv[3] << endl;
            exit(1);
        }
        MetroSim metrosim(inFile,outFile,CommandFile);
        metrosim.ReadInCommand();
    } return 0;
}
