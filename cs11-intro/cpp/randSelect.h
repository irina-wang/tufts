////////////////////////////////////////////////////////////////////////////
//.   Tufts University, Comp 160 randSelect coding assignment  
//    randSelect.h
//    randomized selection
//
//    includes functions provided and function students need to implement
//
////////////////////////////////////////////////////////////////////////////


#pragma once

#include <vector>


// prints a vector to help debugging
// ie: prints "[1 2 3 4 5]" for a vector containing those values
void printVector(std::vector<int> v);


// function to be implemented
// MUST follow the function signature below
int randSelect(std::vector<int> v, int rankIndex);

int partition(std::vector<int> * v);