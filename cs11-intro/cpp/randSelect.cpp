////////////////////////////////////////////////////////////////////////////
//.   Tufts University, Comp 160 randSelect coding assignment  
//    randSelect.cpp
//    randomized selection
//
//    includes functions provided and function students need to implement
//
//     Modified by Mengqi Irina Wang
//                              1278675
//
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <vector>

#include "randSelect.h"

// function declarations
void printVector(std::vector<int> v);
int partition(std::vector<int> * v);
int randSelect(std::vector<int> v, int rankIndex);


// Does      : print out all elems in vector in the required format
// Parameter : int vector, v
// Return    : none
void printVector(std::vector<int> v) {
    std::cout << "[ ";
    for (int i : v)
        std::cout << i << " ";
    std::cout << "]\n";
}


// Does      : pick a pivot at random, partition around the pivot,        
//                                            and return the rank of the pivot
// Parameter : pointer to an int vector, v
// Return    : int, the rank of the pivot
int partition(std::vector<int> * v){
    // printing the pre-partitioned array
    printVector(*v); 

    // generate rand pivot
    srand(time(0));
    int pivot = rand() % (int)v->size();
    std::swap((*v)[pivot], (*v)[v->size()-1]);
    pivot = v->size()-1;

    // print out pivot info
    std::cout << "Selected " << (*v)[pivot] << " as the pivot; "; 

    // start in place partition
    int i = 0;
    for (int j = 0; j < (int) v->size()-1 ; j++){
        if((*v)[j] <= (*v)[pivot]){
            std::swap((*v)[i], (*v)[j]);
            i = i + 1;
        }
    }
    std::swap((*v)[i], (*v)[v->size()-1]);

    // print the rank info of the pivot
    std::cout << "its rank is " << i << "; ";

    // return the rank of the pivot
    return i;
}

// Does      : Use randSelect method to find the element of rankIndex
// Parameter : int vector, v, and int, rankIndex
// Return    : int, the number in the vector of rankIndex
// Note      : calls partition
int randSelect(std::vector<int> v, int rankIndex) {
    // print out prompt info about the rank that we are searching
    std::cout << "Looking for value with rank " << rankIndex 
                                                    << " in the array\n";
    // partition
    int pos = partition(&v);

    // compare pos to expected rankIndex
    if ( pos == rankIndex ){ 
        std::cout << "Thus, we recurse on nothing. We are done. \n";
        return v[pos];
    }
    if ( pos > rankIndex ){ // partition on the lower part
        std::vector<int> v1 = std::vector<int>(v.begin(), v.begin() + pos);
        std::cout << "Thus, we recurse on left. \n";
        return randSelect(v1, rankIndex);
    }
    if ( pos < rankIndex ){ // partition on the larger part
        std::vector<int> v2 = std::vector<int>(v.begin() + pos + 1 , v.end());
        std::cout << "Thus, we recurse on right. \n";
        return randSelect(v2, rankIndex - pos - 1 );
    }

    // fail to find one
    return -1;
}



