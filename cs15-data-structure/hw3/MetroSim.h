/* 
 * MetroSim.h
 * Comp15
 * Spring 2019
 * HW3
 *
 * Author : Mengqi Irina Wang
 * Date : 2/20/2019
 */


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#ifndef _METROSIM_H_
#define _METROSIM_H_


struct Passenger
{
    int ID;
    unsigned int start; // integer not string
    unsigned int end; // integer not string
};


struct Station 
{
    string name;
    unsigned int Station_NO;
    vector<Passenger> passengerList;
};


class MetroSim{
	public:
    MetroSim(ifstream &infile, ofstream &Passfile, istream &where2readfrom);
                 // constructor
    ~MetroSim(); // destructor

    // Functions run commands
    void ReadInCommand();
    void MetroCommands(char move);
    void ChangingFile();
    void PsgrCommand();

    // Initializing functions
    void InitStation();
    void InitPassenger(int start, int end);
    
    // Print functions
    void printStation(int i);
    void checkOnTrain();
    void printMap();
    void printPassFile(int i, int endStation);

	private:
    // crossed out when doing unit test

    vector<Station> stations; 
    unsigned int curr; // keep track of the train's current pos index

    int IDcount; // keep track of the IDs assigned

    vector<Passenger> listOnTrain;

    istream &where2readfrom;
    ifstream &inFile;
    ofstream &passfile;
    
    bool go_on;
    bool mvforward; // keep track of the direction the metro is moving
    void forward(); // determine if the metro is moving forward or not
    void nxtStation(); // get next station
};

#endif
