/*
 * Filename: MinHeap.h
 * Author: Hayden Wolff
 * Contains: Derived class for MinHeap type, inherits from abstract
 *           heap class
 * Comp 15 Lab 10 Fall 2018: Heaps
 *
 */

#include "Heap.h"

#ifndef MINHEAP_H_
#define MINHEAP_H_

template<class E> class MinHeap : public Heap<E>
{
public:
    MinHeap();
    ~MinHeap();
private:    
    // Overriding purely virtual functions
    void heapify_up(int);
    void heapify_down(int);
};

#endif
