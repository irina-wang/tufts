/*
 * Filename: MaxHeap.cpp
 * Author: Hayden Wolff
 * Contains: Implementation for MaxHeap class inherits from
 *           abstract Heap class
 * Comp 15 Lab 10 Fall 2018: Heaps
 *
 */

#include <iostream>
#include "MaxHeap.h"
#include "Patient.h"
using namespace std;

// Function: MaxHeap constructor
// Parameters: none
// Returns: nothing
// Does: default constructor, does nothing
template<class E>
MaxHeap<E>::MaxHeap()
{
}

// Function: MaxHeap destructor
// Parameters: none
// Returns: nothing
// Does: destructor, does nothing
template<class E>
MaxHeap<E>::~MaxHeap()
{
}

// Function: heapify_up
// Parameters: int index
// Returns: nothing
// Does: heapify up- compare myself to my parent
//       swap if needed, recursively repeat
template<class E>
void MaxHeap<E>::heapify_up(int index)
{
    if (index == 0 || index > Heap<E>::length || Heap<E>::length == 0)
        return;

    E item = Heap<E>::heap[index];
    int parent_index = Heap<E>::get_parent_index(index);

    if (Heap<E>::heap[parent_index] < item)
    {
        E temp = Heap<E>::heap[parent_index];
        Heap<E>::heap[parent_index] = item;
        Heap<E>::heap[index] = temp;
        heapify_up(parent_index);
    }
}

// Function: heapify_down
// Parameters: int index
// Returns: void
// Does: heapify down- compare myself to left/right
//       children, if I'm too big, swap with smaller
//       of them. Recursively repeat until I'm in place
template<class E>
void MaxHeap<E>::heapify_down(int index)
{
    int left_index, right_index;
    Heap<E>::get_children_indices(index, left_index, right_index);

    int big_index = index;
    if (left_index < Heap<E>::length && 
        Heap<E>::heap[big_index] < Heap<E>::heap[left_index])
        big_index = left_index;
    if (right_index < Heap<E>::length &&
        Heap<E>::heap[big_index] < Heap<E>::heap[right_index])
        big_index = right_index;

    // Swap if necessary
    if (big_index != index)
    {
        E temp = Heap<E>::heap[index];
        Heap<E>::heap[index] = Heap<E>::heap[big_index];
        Heap<E>::heap[big_index] = temp;
        heapify_down(big_index);
    }
}

// Template class specifications
template class MaxHeap<Patient>;
template class MaxHeap<int>;
template class MaxHeap<double>;
