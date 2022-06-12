/*
 * runalltests.cpp
 * COMP15
 * Spring 2019
 * 
 * Main program used to run all tests fond in unittest_SixDegrees.cpp
 *
 */

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
