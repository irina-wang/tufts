/*
 * Filename: MaxHeap.h
 * Author: Hayden Wolff
 * Contains: Derived class for MaxHeap type, inherits from abstract
 *           heap class
 * Comp 15 Lab 10 Fall 2018: Heaps
 *
 */

#include "Heap.h"

#ifndef MAXHEAP_H_
#define MAXHEAP_H_

template<class E> class MaxHeap : public Heap<E>
{
public:
    MaxHeap();
    ~MaxHeap();
private:    
    // Overriding purely virtual functions
    void heapify_up(int);
    void heapify_down(int);
};

#endif
