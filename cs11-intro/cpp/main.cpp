////////////////////////////////////////////////////////////////////////////
//.   Tufts University, Comp 160 randSelect coding assignment  
//    main.cpp
//    randomized selection
//
//    simple main to test randSelect
//    NOTE: this main is only for you to test randSelect. We will compile
//          your code against a different main in our autograder directory
//
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "randSelect.h"


int main(void) {
    std::vector<int> v = std::vector<int>{3, 4, 5, 1, 2};
    int rankWeWant = 3;
    int ourNumber = randSelect(v, rankWeWant);
    std::sort(v.begin(), v.end());
    int expectedNumber = v[rankWeWant];

    if(ourNumber != expectedNumber) {
        std::cout << "Nooo!\n";
    } else {
        std::cout << "Yayy!\n";
    }
    return 0;
}