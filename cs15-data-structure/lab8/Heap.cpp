/*
 * Filename: heap.cpp
 * Author: Hayden Wolff
 * Contains: Implementation for Heap abstract class
 * Comp 15 Lab 10 Fall 2018: Heaps
 *
 */

#include "Heap.h"
#include "Patient.h"

// Function: template class constructor
// Parameters: none
// Returns: nothing
// Does: default constructor, initializes with length 0
template<class E>
Heap<E>::Heap()
{
    length = 0;
}

// Function: template class destructor
// Parameters: none
// Returns: nothing
// Does: nothing
template<class E>
Heap<E>::~Heap()
{
}

// Function: get_value_at
// Parameters: int index
// Returns: Value in heap
// Does: for testing: verify what value is at an index
template<class E>
E Heap<E>::get_value_at(int index)
{
    if (index < 0)
        throw EmptyHeap();
    else if (index > length)
        throw FullHeap();
    return heap[index];
}

// Function: get_parent_index
// Parameters: int index
// Returns: int index of parent
// Does: returns the index of a parent
template<class E>
int Heap<E>::get_parent_index(int index) const
{
    if (index == 0)
        return 0;
    return (index - 1) / 2;
}

// Function: get_children_indices
// Parameters: int index, int left index, int right index
// Returns: none
// Does: updates by reference the indices of left/right children
template<class E>
void Heap<E>::get_children_indices(int index, int &left, int &right) const
{
    left = (index * 2) + 1;
    right = (index *2) + 2;
}

// Function: is_full
// Parameters: none
// Returns: bool, true if full
// Does: is full if length = capacity
template<class E>
bool Heap<E>::is_full() const
{
    return (length == MAX_CAPACITY);
}

// Function: is_empty
// Parameters: none
// Returns: bool, true if empty
// Does: is empty if length is zero
template<class E>
bool Heap<E>::is_empty() const
{
    return (length == 0);
}

// Function: insert_item
// Parameters: template item
// Returns: none
// Does: inserts a new item
template<class E>
void Heap<E>::insert_item(E item)
{
    if (is_full())
        throw FullHeap();

    heap[length] = item;
    heapify_up(length);
    length++;
}

// Function: extract
// Parameters: none
// Returns: template item
// Does: extracts the root then heapify
//       down to adjust
template <class E>
E Heap<E>::extract()
{
    if (is_empty())
        throw EmptyHeap();
    E item = heap[0];

    heap[0] = heap[length-1];
    length--;
    heapify_down(0);
    return item;
}

// template class specifications
template class Heap<Patient>;
template class Heap<int>;
template class Heap<double>;