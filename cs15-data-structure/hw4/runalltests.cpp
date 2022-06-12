/*
 * runalltests.cpp
 * COMP15
 * Spring 2019
 * 
 * Main program used to run all gests fond in BinarySearchTree-unittest.cpp
 *
 */

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}