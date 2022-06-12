/*
 * MetroSim.cpp
 * Comp15
 * Spring 2019
 * HW3
 *
 * Author : Mengqi Irina Wang
 * Date: 2/20/2019
 */


#include "SequenceMatch.h"

// Constructor
MetroSim::MetroSim(ifstream &infile, ofstream &Passfile,istream &Command) : 
    where2readfrom(Command),inFile(infile), passfile(Passfile)
{
    InitStation();
    curr = 0; // the index
    IDcount = 1; // ID should start at 1
    mvforward = true;
    go_on = true;
}


// Destructor 
MetroSim::~MetroSim(){
}


// ReadInCommand
//   The general function that takes in all the commands from cin or file
//
// Parameter : none
// Return    : none
// Does      : Distinguishes the command by its first char, and then calls 
//             the corresbonding functions to move the metro,end the game,
//             add a passenger or change an output file depending on the 
//             following chars, string or ints. 
// Note      : print "Command not found!" when the commands don't meet the
//             requirements; Commands are case sensitive
void MetroSim::ReadInCommand(){
    char determine_command, move;
    bool Command_Not_Found = true;

    printMap(); //print for the first time
    while(go_on) {
        cout << "Command: ";
        where2readfrom >> determine_command;
        // commands about Metro
        if(determine_command == 'm' or determine_command == 'M'){
            Command_Not_Found = false;
            where2readfrom >> move;
            MetroCommands(move); // function call
        }
        // adding passenger
        if(determine_command == 'p' or determine_command == 'P'){
            Command_Not_Found = false;
            PsgrCommand();
        }
        // changing file
        if(determine_command == 'f' or determine_command == 'F'){
            Command_Not_Found = false;
            ChangingFile();
        }
        // doesn't go into any loops above
        if(Command_Not_Found) 
            cout << "Command not found!" << endl;
    }
}
    

// MetroCommands
//   Does commands regarding the metro
//
// Parameter : char move, takes in command about what to do
// Returns   : none
// Does      : moves the metro to the next station if takes in a 'm'
//             ends the game if takes in a 'f', and otherwise print
//             "command not found!"
// Note      : print "Command not found!" if commands don't meet the 
//             requirements; called when determine_command is 'm'
void MetroSim::MetroCommands(char move) {
    if ( move == 'm' or move == 'M'){ // move the metro 
        checkOnTrain();
        printMap();
    } else if (move == 'f' or move == 'F'){ // quit the game
        go_on = false;
        cout << "Thanks for playing MetroSim. Have a nice day!" 
             << endl;
    } else 
        cout << "Command not found!" << endl;
}


// ChangingFile
//   changes the output file from one to another
//
// Parameter : none
// Returns   : none
// Does      : chanegs the output file from one to another if clients 
//             request to do so
// Note      : print "Command not found!" if the commands don't meet the
//             requirement; called when determine_command is 'f'
void MetroSim::ChangingFile(){
    string filename;
    if(where2readfrom >> filename) { // successfully read in
        passfile.close();
        passfile.open(filename);
    } else
        cout << "Command not found!" << endl;
}


// InitStation
//   read stations from a file and store them
//
// Parameter : none
// Returns   : none
// Does      : read in station line by line from the existing file, assign
//             Station_NO and then  stores them into the Station vector
// Note      : curr equals to 0 - starts from the first station
void MetroSim::InitStation(){
    string stationname;
    while(getline(inFile,stationname)) {
        Station s;
        s.name = stationname;
        s.Station_NO = stations.size()+1; 
        stations.push_back(s);
    }
}


// InitPassenger
//   initialize the passengers
// 
// Parameter : int start and end, marking the start and end  station's 
//             NO(not index in the array)
// Returns   : none
// Does      : initialize a new passenger with start station number, end
//             station number, ID number and status of on train or not.
//             and then being pushed back to the passengers vector
// Note      : called by PsgrCommand
void MetroSim::InitPassenger(int start, int end) {
    Passenger p;
    p.start = start;
    p.end = end;
    p.ID = IDcount++;
    stations[p.start-1].passengerList.push_back(p);
}
    

// nxtStation
//   moves the metro to the next station depending on the direction it is
// moving towards
// 
// Parameter : none
// Returns   : none
// Does      : add 1 to curr if metro is moving forward and subtract 1 if 
//             the metro is moving backwards
// Note      : none
void MetroSim::nxtStation() {
    if(mvforward)
        curr++;
    else
        curr--;
}


// PsgrCommand
//   Does commands regarding the passengers
//
// Parameter : none
// Returns   : none
// Does      : initializes the passenger and adds the passenger to the map
// Note      : print "Command not found!" if the commands don't meet the
//             requirement; called when determine_command is 'p'
void MetroSim::PsgrCommand(){
    int start, end;
    if (where2readfrom >> start >> end){ // successfully read in
        InitPassenger(start,end);
        printMap();
    } else
        cout << "Command not found!" << endl;
}


// printPassenger
//   prints passenger as required
//
// Parameter : int i, determines which passenger to print
// Returns   : none
// Does      : print the passenger's ID, start station number and end 
//             station number in the format required
// Note      : none
void MetroSim::printStation(int j){
    if(curr == (unsigned) j)  // Train is at the station
        cout << "TRAIN: ";
    else
        cout << "       ";
         
    cout << "[" << stations[j].Station_NO << "] " 
         << stations[j].name << " {";
    for(unsigned int i = 0; i < stations[j].passengerList.size(); i++) {
        cout << "[" << stations[j].passengerList[i].ID << ", " 
            << stations[j].passengerList[i].start << "->" 
            << stations[j].passengerList[i].end << "]";
       // if(stations[j].passengerList[i].start == stations[curr].Station_NO){
         //   passengers[i].OnTrain = true;  
           // listOnTrain.push_back(passengers[i]);        
    }     
    cout << "}" << endl;    
}


// checkOnTrain
//   check if the passenger is on 

// Parameter : none
// Returns   : none
// Does      : prints to outfile when the passenger leaves the metro, and 
//             deletes him
// Note      : consider the different situations depends on the direction 
//             the metro moves
void MetroSim::checkOnTrain(){
    for (unsigned i = 0; i < stations[curr].passengerList.size();) {
        listOnTrain.push_back(stations[curr].passengerList[i]);
        stations[curr].passengerList.erase(stations[curr].passengerList.begin() + i);
    }

    forward(); // check if we should move forward or back
    nxtStation();

    for (unsigned i = 0; i < listOnTrain.size(); i++) {
        if (listOnTrain[i].end == stations[curr].Station_NO) {
            printPassFile(listOnTrain[i].ID, listOnTrain[i].end);
            listOnTrain.erase(listOnTrain.begin() + i);
            i--;
        }
    }
}
     

// printMap
//   print the map
//
// Parameter : none
// Returns   : none
// Does      : prints the whole map
// Note      : calls "checkOnTrain"
void MetroSim::printMap(){
    
    cout << "Passengers on the train: {";
    for(unsigned int i = 0; i < listOnTrain.size(); i++){
        cout << "[" << listOnTrain[i].ID << ", " 
            << listOnTrain[i].start << "->" 
            << listOnTrain[i].end << "]";
    }  // print the passengers on the train
    cout << "}" << endl;
    
    for(unsigned int j = 0; j < stations.size(); j++){
        printStation(j);
    }
}
            

// forward
//   keep track of the direction the metro is moving towards
// 
// Parameter : none
// Returns   : none
// Does      : keep track of the direction the metro is moving towards
// Note      : only changes direction when at the first or last station
void MetroSim::forward() {
    if(curr == stations.size()-1)
        mvforward = false;
    else if(curr == 0)
        mvforward = true;
    else 
        return; // no need to change
} 
        
    
// printPassFile
//   print to passfile when passenger get out of the metro
// 
// Parameter : int i, which passenger             
//             int endStation, the station the passenger leaves
// Returns   : none
// Does      : print to passfile when passenger get out of the metro
// Note      : none
void MetroSim::printPassFile(int i, int endStation){
    passfile << "Passenger " << i << " left train at station " 
         << endStation << endl;
}

