/*
 * LinkedList.cpp
 * COMP15
 * Spring 2019
 * Google Test Lab
 *
 * Unit tests for Linked List class
 *
 * Author: Kevin Destin
 * Date: 2/10/2019
 */

#include "LinkedList.h"
#include <gtest/gtest.h>

using namespace std;

TEST(LinkedList, clear) {
        /*
         * Setup test by initializing a list with some data
         */
        LinkedList ll = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        /*
         * Run function under test
         */
        ll.clear();

        /*
         * Check that function meets contract
         */

        for (int i = 0; i < 10; i++) {
                // We shouldn't find any elements that were added to the list
                EXPECT_FALSE(ll.find(i)) << i
                                         << " was cleared from list,"
                                            " should not be found\n";
        }

        // The list should have 0 elements
        // TODO: Fix clear so this assertion doesn't fail.
        EXPECT_EQ(ll.length(), 0) << "Clear should result in an empty list\n";
}

TEST(LinkedList, remove) {
        LinkedList ll;

        // empty list test
        EXPECT_FALSE(ll.remove(1));
        EXPECT_EQ(ll.length(), 0) << "Removing from empty list shouldn't"
                                     " decrement length\n";

        ll             = {1, 2, 3, 3, 4, 5};
        int initLength = ll.length();

        EXPECT_TRUE(ll.remove(3));
        EXPECT_EQ(ll.length(), initLength - 1);

        EXPECT_TRUE(ll.remove(3));
        EXPECT_EQ(ll.length(), initLength - 2);

        // Expect third remove to fail, since there are only two 3s
        EXPECT_FALSE(ll.remove(3)) << "3 is no longer present and"
                                      " should not have been removed\n";
        EXPECT_EQ(ll.length(), initLength - 2) << "length shouldn't"
                                                  " decrement again\n";

        // Edge case: Remove head
        EXPECT_TRUE(ll.remove(1));
        EXPECT_EQ(ll.length(), initLength - 3);

        // Removing 3s and 1 shouldn't affect anything else in the list
        EXPECT_TRUE(ll.find(2) && ll.find(4) && ll.find(5))
            << "other elements should still be present in list\n";
}

TEST(LinkedList, length) {
        LinkedList ll;
        int        data[]           = {1, 2, 3, 4, 5, 6, 7, 8};
        int        reference_length = 0;
        
        EXPECT_EQ(ll.length(), 0);

        // (This is a "For Each" loop. Read it as: "For each int i in data")
        // (More info: http://www.cplusplus.com/doc/tutorial/control/#rangefor)
        for (int i : data) {
                ll.push_front(i);
                EXPECT_EQ(ll.length(), ++reference_length);
        }

        for (int i : data) {
                ll.remove(i);
                EXPECT_EQ(ll.length(), --reference_length);
        }
}

TEST(LinkedList, at) {
    LinkedList ll;
    EXPECT_THROW(ll.at(1), std::logic_error) << "at on empty list should"
                                                 " throw std::logic_error";
    ll = {1,2,3,4,5};

    EXPECT_EQ(ll.at(2),3);
    EXPECT_EQ(ll.at(4),5);

}

TEST(LinkedList, push_front) {
    LinkedList ll;
    
    ll.size = 10;
    ll.push_front(5); // add 5 to the list
    EXPECT_EQ(ll.size,11);
    EXPECT_EQ(ll.head->info, 5);
}

TEST(LinkedList, find) {
    LinkedList ll;
    
    ll.head = NULL;
    EXPECT_FALSE(ll.find(5));

    ll = {5,8,13,21,34,65};
    EXPECT_TRUE(ll.find(5));
    EXPECT_FALSE(ll.find(2));
    
    
}
