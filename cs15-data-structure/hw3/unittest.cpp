/*
 * Unittest.cpp
 * Comp15
 * Spring 2019
 * HW3
 *
 * Author : Mengqi Irina Wang
 * Date: 2/20/2019
 */

#include<gtest/gtest.h>
#include "MetroSim.h"

using namespace std;

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


// Test inserting passengers
TEST(MetroSim, InitPassenger){
    ifstream inFile;
    inFile.open("stations.txt");
    
    ofstream outFile;
    outFile.open("myoutfile.txt");

     MetroSim metrosim(inFile,outFile,cin);
     
     metrosim.InitPassenger((unsigned)2,(unsigned)5);
     EXPECT_EQ(metrosim.stations[1].passengerList[0].end, (unsigned)5);
     EXPECT_EQ(metrosim.stations[1].passengerList[0].ID, 1); //starts from 1

     metrosim.InitPassenger((unsigned)2,(unsigned)5); // add another 
     metrosim.InitPassenger((unsigned)2,(unsigned)10); // add another

     EXPECT_EQ(metrosim.stations[1].passengerList[2].ID, 3); // should be 3
} 

// Test Metro Commands
TEST(MetroSim, MetroCommands) {
    ifstream inFile;
    inFile.open("stations.txt");
    
    ofstream outFile;
    outFile.open("myoutfile.txt");

    MetroSim metrosim(inFile,outFile,cin);         
    
    metrosim.curr = 5;
    metrosim.mvforward = true;
    unsigned int recordCurr = metrosim.curr;
    metrosim.MetroCommands('M'); // check if case sensitive
    EXPECT_EQ(recordCurr+1,metrosim.curr);


    metrosim.MetroCommands('F');
    EXPECT_FALSE(metrosim.go_on); // exit the game and print "Thanks.."
}

// Test initializing stations
TEST(MetroSim, InitStation){
    ifstream inFile;
    inFile.open("stations.txt");
    
    ofstream outFile;
    outFile.open("myoutfile.txt");

    MetroSim metrosim(inFile,outFile,cin); 

    metrosim.InitStation();

    EXPECT_EQ(metrosim.stations.size(),(unsigned)26);

    EXPECT_EQ(metrosim.stations[11].name, "Copley");
    EXPECT_EQ(metrosim.stations[11].Station_NO, (unsigned)12);

}

// Test moving to the next station
TEST(MetroSim, nxtStation) {
    ifstream inFile;
    inFile.open("stations.txt");
    
    ofstream outFile;
    outFile.open("myoutfile.txt");

    MetroSim metrosim(inFile,outFile,cin);

    metrosim.curr = 5;

    unsigned int recordCurr = metrosim.curr;
    metrosim.mvforward = true;
    metrosim.nxtStation();
    EXPECT_EQ(recordCurr+1,metrosim.curr);

    recordCurr = metrosim.curr;
    metrosim.mvforward = false;
    metrosim.nxtStation();
    EXPECT_EQ(recordCurr-1,metrosim.curr);
}

// Test moving forward      
TEST(MetroSim, forward){
    ifstream inFile;
    inFile.open("stations.txt");
    
    ofstream outFile;
    outFile.open("myoutfile.txt");

    MetroSim ms(inFile,outFile,cin);

    ms.InitStation(); // size should be 26
   
    ms.curr = 5;
    ms.forward();
    EXPECT_TRUE(ms.mvforward);

    ms.curr = ms.stations.size()-1;
    ms.forward();
    EXPECT_FALSE(ms.mvforward);

    ms.curr = 0;
    ms.forward();
    EXPECT_TRUE(ms.mvforward);
}

// Test checkOnTrain       
TEST(MetroSim,checkOnTrain){
    ifstream inFile;
    inFile.open("stations.txt");
    
    ofstream outFile;
    outFile.open("myoutfile.txt");

    MetroSim metrosim(inFile,outFile,cin);         
    
    metrosim.curr = 0; // at station 1

    metrosim.checkOnTrain();
    EXPECT_EQ(metrosim.listOnTrain.size(), (unsigned)0);

    metrosim.InitPassenger((unsigned)2,(unsigned)5); // ID = 1
    metrosim.InitPassenger((unsigned)2,(unsigned)5); // ID = 2
    metrosim.InitPassenger((unsigned)2,(unsigned)5); // ID = 3
    metrosim.InitPassenger((unsigned)2,(unsigned)7); // ID = 4
    metrosim.InitPassenger((unsigned)2,(unsigned)4); // ID = 5
    metrosim.InitPassenger((unsigned)2,(unsigned)10);// ID = 6
    metrosim.InitPassenger((unsigned)3,(unsigned)8); // ID = 7

    metrosim.checkOnTrain();
    EXPECT_EQ(metrosim.listOnTrain.size(), (unsigned)6); //p7 up, p5 off

    metrosim.curr = 3; // at station 4
    metrosim.checkOnTrain();
    EXPECT_EQ(metrosim.listOnTrain.size(), (unsigned)3); 

}

