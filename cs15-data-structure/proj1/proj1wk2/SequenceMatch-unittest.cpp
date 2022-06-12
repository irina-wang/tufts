/*
 * SequenceMatch-unittest.cpp
 * COMP15
 * Spring 2019
 * 
 * Small unit test for the SequenceMatch class using google Test 
 * Modified by Irina Mengqi Wang
 * Date 03/13/2019
 */

#include "SequenceMatch.h"
#include <gtest/gtest.h>
#include <limits>
#include <fstream>

using namespace std;


// Test for insert, partially testing numOfnodes
TEST(SequenceMatch, insert) {
        ifstream cmd;
        ofstream passFile;
        cmd.open("command.txt");
        passFile.open("ut-output.txt");
        SequenceMatch seq(cmd,passFile);
        
        // We start testng an edge case: find the numOfnodes for a empty tree
        EXPECT_EQ(seq.numOfnodes(), 0);

        seq.insert("A");
        EXPECT_EQ(seq.numOfnodes(), 2);

        seq.insert("C");
        EXPECT_EQ(seq.numOfnodes(), 4);

        // we insert a sequence that's partically in the list
        seq.insert("AC");
        EXPECT_EQ(seq.numOfnodes(), 6);
        
        seq.insert("ACTG");
        EXPECT_EQ(seq.numOfnodes(), 9);

        // shouldn't change the total num : "A" already in list
        seq.insert("A");
        EXPECT_EQ(seq.numOfnodes(), 9);

        EXPECT_ANY_THROW(seq.insert("ACTH")); // not a sequence
}

// Test for clear, partially testing numOfnodes
TEST(SequenceMatch, clear) {
        ifstream cmd;
        ofstream passFile;
        cmd.open("commands.txt");
        passFile.open("ut-output.txt");
        SequenceMatch seq(cmd,passFile);
        
        // We start testng an edge case: find the numOfnodes for a empty tree
        EXPECT_EQ(seq.numOfnodes(), 0);

        // insert different sequences                    
        seq.insert("ATATATATATATATTATAT");
        seq.insert("GTATATC");
        seq.insert("CCGGT");
        seq.insert("ACCGGT");
        seq.insert("ATCCGGT");
        seq.insert("C");
        
        seq.clear();
        EXPECT_EQ(seq.numOfnodes(), 0);
        // should also print there are 0 nodes in the database;
}


// Test for remove, partially testing numOfnodes
TEST(SequenceMatch, remove) {
        ifstream cmd;
        ofstream passFile;
        cmd.open("commands.txt");
        passFile.open("ut-output2.txt");
        SequenceMatch seq(cmd,passFile);
        
        // We start testng an edge case: find the numOfnodes for a empty tree
        EXPECT_EQ(seq.numOfnodes(), 0);

        seq.insert("A");
        seq.remove("A");
        EXPECT_EQ(seq.numOfnodes(), 0);

        // insert different sequences
        seq.insert("ATATATATATATATTATAT");
        seq.insert("GTATATC");
        seq.insert("CCGGT");
        seq.insert("ACCGGT");
        seq.insert("ATCCGGT");
        seq.insert("C");
        
        // removing sequences
        seq.remove("C"); // should print "C removed"
        seq.remove("ATCCGGT"); // should print "ATCCGGT removed"
        seq.remove("AC"); // should print "AC : No match found"

        // remove something with letters other than ATGC
        EXPECT_ANY_THROW(seq.remove("HHHHHHHHHH"));

        // remove all
        seq.remove("ATATATATATATATTATAT");
        seq.remove("GTATATC");
        seq.remove("CCGGT");
        seq.remove("ACCGGT");

        EXPECT_EQ(seq.numOfnodes(), 0);
}


// Test for print
TEST(SequenceMatch, print) {
        ifstream cmd;
        ofstream passFile;
        cmd.open("command.txt");
        passFile.open("print.txt");
        SequenceMatch seq(cmd,passFile);
        
        seq.insert("ATATATATATATATTATAT");
        seq.insert("GTATATC");
        seq.insert("CCGGT");
        seq.insert("ACCGGT");
        seq.insert("ATCCGGT");
        seq.insert("C");
        
        seq.print(); // should print in order
}

// Test for prefix_query
TEST(SequenceMatch, prefix_query) {
        ifstream cmd;
        ofstream passFile;
        cmd.open("command.txt");
        passFile.open("pfx.txt");
        SequenceMatch seq(cmd,passFile);
        
        seq.insert("ATATATATATATATTATAT");

        EXPECT_FALSE(seq.prefix_query("A")); // [sequence]: No match found"
        EXPECT_TRUE(seq.prefix_query("ATATATATATATATTATAT"));

        // insert more sequences
        seq.insert("ATATATATATATATTATATAA");
        seq.insert("ATATATATATATATTATATC");
        seq.insert("ATATATATATATATTATATG");
        seq.insert("ATATATATATATATTATATTT");
        seq.insert("ATATATATATATATTATATATCT");
        seq.insert("ATC");
        seq.insert("ATA");

        EXPECT_TRUE(seq.prefix_query("ATATATATATATATTATAT"));
        //should print 5 strings in alphabetical order, without ATC
}

// Test for query
TEST(SequenceMatch, query) {
        ifstream cmd;
        ofstream passFile;
        cmd.open("command.txt");
        passFile.open("ut-output.txt");
        SequenceMatch seq(cmd,passFile);
        
        // insert more sequences
        seq.insert("AC");
        seq.insert("ATATATATATATATTATAT");
        seq.insert("ATATATATATATATTATATAA");
        seq.insert("ATATATATATATATTATATC");
        seq.insert("ATATATATATATATTATATG");
        seq.insert("ATATATATATATATTATCTTT");
        seq.insert("ATATATATATATATTATATATCT");
        seq.insert("ATATATATATATATTATATC");
        seq.insert("ATATATATATATATTATCTGCC");

        EXPECT_EQ(seq.query("A"), "AC"); 

        // should return the first one in alphabetical order
        EXPECT_EQ(seq.query("ATATATATATATATTATA"), "ATATATATATATATTATAT");

        // should return the shorter one
        EXPECT_EQ(seq.query("ATATATATATATATTATC"), "ATATATATATATATTATCTTT");
}
