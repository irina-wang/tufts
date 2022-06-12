/*
 * BinarySearchTree-unittest.cpp
 * COMP15
 * Spring 2019
 * 
 * Small unit test for the Binary Search Tree class using google Test 
 * Modified by Irina Mengqi Wang
 * Date 02/27/2019
 */

#include "BinarySearchTree.h"
#include <gtest/gtest.h>
#include <limits>
#include <vector>

// some sanity check unit tests

class BSTtests : public ::testing::Test {
protected:
/**
 * This a TEST Fixture in Google Test. It is used to define data that
 * many tests can use. Each test gets its own copy of the same data.
 * Here, We define a testdata vector with some predefined numbers
 * The array is initialized in the constructor. No clean up is needed.
**/
        const std::vector<int> testdata;
        BSTtests()
            : testdata{258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255} {}
};

/*
 * Unit testing for find_min
 */
TEST_F(BSTtests, find_min) {
        BinarySearchTree bst;
        constexpr int    errorVal    = std::numeric_limits<int>::min();
        constexpr int    testdataMin = -898;

        // We start testng an edge case: find the 
        // minimum in an empty tree
        EXPECT_EQ(bst.find_min(), errorVal)
            << "find_min on an empty tree should"
               " return INT_MIN";

        // edge case: root is min
        bst.insert(0);
        EXPECT_EQ(bst.find_min(), 0);

        for (int num : testdata)
                bst.insert(num);

        // typical usage: we look for minimum after inserting many numbers
        EXPECT_EQ(bst.find_min(), testdataMin);
}

/*
 * Unit testing for find_max
 */
TEST_F(BSTtests, find_max) {
        BinarySearchTree bst;
        constexpr int    errorVal    = std::numeric_limits<int>::max();
        constexpr int    testdataMax = 814;

        // We start testng an edge case: find the 
        // maximum in an empty tree
        EXPECT_EQ(bst.find_max(), errorVal)
            << "find_min on an empty tree should"
               " return INT_MAX";

        // edge case: root is max
        bst.insert(800);
        EXPECT_EQ(bst.find_max(), 800);

        for (int num : testdata)
                bst.insert(num);

        // typical usage: we look for maximum after inserting many numbers
        EXPECT_EQ(bst.find_max(), testdataMax);
}

/*
 * Unit testing for contains
 */
TEST_F(BSTtests, contains) {
        BinarySearchTree bst;
        constexpr int    testValue_Inlist = 172;
        constexpr int    testValue_NotInlist = 50;


        // We start testng an edge case: find both
        // values in an empty tree
        EXPECT_FALSE(bst.contains(testValue_Inlist));
        EXPECT_FALSE(bst.contains(testValue_NotInlist));

        // edge case: root's data equals to the value
        bst.insert(328);
        EXPECT_TRUE(bst.contains(328));

        for (int num : testdata)
                bst.insert(num);

        // typical case: tree should contain the data in the list
        //               and shouldn't contain the data that's not in the list
        for (int num : testdata){
                bst.insert(num);
                EXPECT_TRUE(bst.contains(num));
        }
                
        EXPECT_FALSE(bst.contains(testValue_NotInlist));
}

/*
 * Unit testing for insert
 */
TEST_F(BSTtests, insert) {
        BinarySearchTree bst;
        constexpr int    testValue_Inlist = 172;
        constexpr int    testValue_NotInlist = 50;

        // We start testng an edge case: 
        // values shouldn't exist in an empty tree
        EXPECT_FALSE(bst.contains(testValue_Inlist));
        EXPECT_FALSE(bst.contains(testValue_NotInlist));

        // edge case: root's data equals to the value inserted
        bst.insert(328);
        EXPECT_TRUE(bst.contains(328));
        
        // typical case: tree should contain the data that has been inserted
        for (int num : testdata){
                bst.insert(num);
                EXPECT_TRUE(bst.contains(num));
                EXPECT_FALSE(bst.contains(testValue_NotInlist));
        }       
}

/*
 * Unit testing for remove
 */
TEST_F(BSTtests, remove) {
        BinarySearchTree bst;
        constexpr int    testValue_Inlist = 397;
        constexpr int    testValue_NotInlist = 50;

        // We start testng an edge case: remove a 
        // value from an empty tree
        EXPECT_FALSE(bst.remove(testValue_Inlist));
        EXPECT_FALSE(bst.remove(testValue_NotInlist));

        // typical usage: check if we can remove every node inserted
        //                and check if we fail to remove if value that's 
        //                not in the list            
        // Some special cases to note:
        //                   - leaf : 255, 430...
        //                   - one child: -768, -55..
        //                   - two child: 172, -686..
        for (int num : testdata){
                bst.insert(num);
        }

        EXPECT_FALSE(bst.remove(testValue_NotInlist));

        for (int num : testdata){        
                EXPECT_TRUE(bst.remove(num));
        }

        // edge case: remove a value that has a count that's more than 1
        bst.insert(testValue_Inlist);
        bst.insert(testValue_Inlist);
        bst.insert(testValue_Inlist);

        EXPECT_TRUE(bst.remove(testValue_Inlist));
        EXPECT_TRUE(bst.contains(testValue_Inlist)); // check in list -rm once
        EXPECT_TRUE(bst.remove(testValue_Inlist));
        EXPECT_TRUE(bst.contains(testValue_Inlist)); // check in list -rm twice
        EXPECT_TRUE(bst.remove(testValue_Inlist));

        EXPECT_FALSE(bst.contains(testValue_Inlist)); // check in list 
                                                     // rm three times -not in
        EXPECT_FALSE(bst.remove(testValue_Inlist)); // fail to remove

}

/*
 * Unit testing for height
 */
TEST_F(BSTtests, height) {
        BinarySearchTree bst;
        constexpr int    randomtestValue = 27139;
        constexpr int    initialheight = -1;
        constexpr int    expect_height = 6;

        // We start testng an edge case: find the 
        // height of an empty tree
        EXPECT_EQ(bst.tree_height(), initialheight);

        // edge case: height of a tree only with root
        bst.insert(randomtestValue);
        EXPECT_EQ(bst.tree_height(), 0);
        bst.remove(randomtestValue); // removed
                                     // so that it won't affect later tests

        for (int num : testdata)
                bst.insert(num);

        // typical usage: we look for the height of the tree
        EXPECT_EQ(bst.tree_height(), expect_height);
}


/*
 * Unit testing for node_count
 */
TEST_F(BSTtests, node_count) {
        BinarySearchTree bst;
        constexpr int    initialnodeNUM = 0;
        constexpr int    expectnodesNUM = 20;
        constexpr int    testValue_Inlist = 172;

        // We start testng an edge case: find the num of
        // nodes of an empty tree
        EXPECT_EQ(bst.node_count(), initialnodeNUM);

        for (int num : testdata)
                bst.insert(num);

        // typical usage: we look total node num after inserting all nodes
        EXPECT_EQ(bst.node_count(), expectnodesNUM);

        // edge case: node count should NOT include duplicates
        bst.insert(testValue_Inlist);
        bst.insert(testValue_Inlist); 
        EXPECT_EQ(bst.node_count(), expectnodesNUM);
}


/*
 * Unit testing for count_total
 */
TEST_F(BSTtests, count_total) {
        BinarySearchTree bst;
        constexpr int    initialvalue = 0;
        constexpr int    expectvalue = -1120;
        constexpr int    randomtestValue = 27;

        // We start testng an edge case: find the node value of an empty tree
        EXPECT_EQ(bst.count_total(), initialvalue);

        for (int num : testdata)
                bst.insert(num);

        // typical usage: we look for total value after inserting all the nodes
        EXPECT_EQ(bst.count_total(), expectvalue);

        // edge case: count the total value with one node inserted more than
        //            once(has a count of more than 1)
        bst.insert(randomtestValue);
        bst.insert(randomtestValue);
        bst.insert(randomtestValue);
        bst.insert(randomtestValue);

        EXPECT_EQ(bst.count_total(), expectvalue+4*randomtestValue);
}

/*
 * Unit testing for copy_constructor
 */
TEST_F(BSTtests, copy_constructor) {
        BinarySearchTree bst;
        constexpr int    testValue_Inlist = 397;

        for (int num : testdata)
                bst.insert(num);

        // typical case : value should exist in both lists 
        BinarySearchTree bst_cp(bst); // copy
        bst.remove(testValue_Inlist); // remove the value from original list
        EXPECT_TRUE(bst_cp.contains(testValue_Inlist)); // should still exist       
}

/*
 * Unit testing for assignment operator(also test post-order delete)
 */
TEST_F(BSTtests, operator) {
        BinarySearchTree bst;
        BinarySearchTree bst_cp;
        constexpr int    testValue = 0;
       
        for (int num : testdata)
                bst.insert(num);

        bst_cp.insert(testValue);
        EXPECT_TRUE(bst_cp.contains(testValue));

// typical case : original value should be emptied, new value should exist
        bst = bst_cp;

        for (int num : testdata)
                EXPECT_FALSE(bst.contains(num));// since it's deleted from the 
                                                // original BinarySearchTree
        
        EXPECT_TRUE(bst_cp.contains(testValue)); // original value should still
                                                // exist

        EXPECT_TRUE(bst.contains(testValue)); // new value should exist since it
                                              // is copied over
}