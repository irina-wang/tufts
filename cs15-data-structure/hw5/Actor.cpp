/*
 * Filename: Graph.cpp
 * Contains: Implementation of the Actor class 
 * Part of: Homework 5 assignment for Comp 15 Spring 2019
 * 
 * Author: Mengqi Irina Wang
 * Date: 2019/04/03
 *
 */

#include <iostream>
#include <fstream>
#include "Actor.h"

using namespace std;

// Function: default constructor
// Parameters: none
// Returns: nothing
// Does: default constructor. Initializes actor's name with empty string
Actor::Actor(){
    actor = "";
}

// Function: constructor
// Parameters: string name
// Returns: nothing
// Does: constructor. Initializes actor's name with the name passed in
Actor::Actor(string name){
    actor = name;
}

// Function: Insert_movie
// Parameters: string, movie name
// Returns: nothing
// Does: insert the movie into the Linkedlist movies
void Actor::Insert_movie(string movie){
    movies.insert(movie);
}

// Function: Actor_is_in
// Parameters: string movie
// Returns: boolean, true if actor is in the movie and false when he/she is not
// Does: check if the actor is in the movie
bool Actor::Actor_is_in(string movie) const{
    bool result;
    movies.find(movie, result);  
    return result;
}

// Function: connect
// Parameters: an const Actor reference to the object actor
// Returns: string, movie's name which both actors are in
// Does: check the movie both actors are in
string Actor::connect(const Actor &actor) const{
    if(this != &actor) {
        for(int i=0; i<movies.get_length(); i++){
            if(actor.Actor_is_in(movies.get_value_at(i)))
                return movies.get_value_at(i);
        }
    }  
    return "";
}

// Function: operator==
// Parameters: an const Actor reference to the object otherObj
// Returns: boolean, true if actors have the same name
//                   false if they don't 
// Does: check if the actors have the same name
bool Actor::operator==(const Actor& otherObj) const{
    return actor == otherObj.actor;
}

// Function: operator!=
// Parameters: an const Actor reference to the object otherObj
// Returns: boolean, true if actors don't have the same name
//                   false if they do
// Does: check if the actors have the same name
bool Actor::operator!=(const Actor& otherObj) const{
    return actor != otherObj.actor;
}

// Function: operator<<
// Parameters: ostream, a reference to out 
//             an const Actor reference to the object otherObj
// Returns: ostream reference
// Does: print actor's name to out
ostream & operator << (ostream &out, const Actor &ACTOR){ 
    return out << ACTOR.actor;
}
