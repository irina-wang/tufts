/*
 * Filename: SixDegrees.h
 * Contains: Interface of the SixDegrees class 
 * Part of: Homework 5 assignment for Comp 15 Spring 2019
 * 
 * Author: Mengqi Irina Wang
 * Date: 2019/04/03
 *
 */

#include "Graph.h" 
#include "Actor.h" 
#include "LinkedList.h"

#include <iostream>
#include <ostream>

#ifndef SIXDEGREE_H_
#define SIXDEGREE_H_

class SixDegrees{
    public:
        void populate_graph();
        void run(istream &in, ostream &out);
        void BFS(Actor a, Actor b, ostream &out);

    // Created only for Unit test
       Graph<Actor> return_graph();
       void get_graph(Graph<Actor> object);

    private:
        Graph<Actor> object;
        LinkedList<Actor> populate_graph_from_file();        
};


#endif