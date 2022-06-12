/*
 * Filename: Graph.h
 * Contains: Interface of the Actor class 
 * Part of: Homework 5 assignment for Comp 15 Spring 2019
 * 
 * Author: Mengqi Irina Wang
 * Date: 2019/04/03
 *
 */

#include "LinkedList.h"
#include <iostream>
#include <ostream>

#ifndef ACTOR_H_
#define ACTOR_H_

class Actor{
    public:
        Actor(); // default constructor
        Actor(string name); // constructor

        void Insert_movie(std::string movie);
        bool Actor_is_in(string movie) const;
        std::string connect(const Actor &actor) const;

        // Operator Overload
        bool operator==(const Actor& otherObj) const;
        bool operator!=(const Actor& otherObj) const;
        friend ostream& operator<< (ostream &out, const Actor &ACTOR);


    private:
        LinkedList<std::string> movies;
        std::string actor;
};


#endif