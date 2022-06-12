/*
 * Filename: SixDegrees.cpp
 * Contains: Implementation of the SixDegrees class 
 * Part of: Homework 5 assignment for Comp 15 Spring 2019
 * 
 * Author: Mengqi Irina Wang
 * Date: 2019/04/03
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "SixDegrees.h"
#include "Queue.h"
#include "Actor.h"
using namespace std;

// Function: populate_graph
// Parameters: none
// Returns: nothing
// Does: populate the graph. call populate_graph_from_file
void SixDegrees::populate_graph(){
    LinkedList<Actor> actors = populate_graph_from_file(); // get data from 
                                                           // actors.txt
    int length = actors.get_length();
    object.initialize_graph(length);

    for (int i = length-1; i > -1; i--) { // insert actors in reverse order
        Actor Actor_1 = actors.get_value_at(i);
        object.add_vertex(Actor_1); // add vertices
    }

    for(int i = 0; i < length; i++){ // insert edges
        Actor Actor_1 = actors.get_value_at(i);
        for(int j = 0; j < length; j++){
            Actor Actor_2 = actors.get_value_at(j);
            string connection = Actor_1.connect(Actor_2);
            if( connection != "") { // no connection - make edges
                object.add_edge(Actor_1, Actor_2, connection);
            }
        }
    }
}

// Function: populate_graph_from_file
// Parameters: none
// Returns: LinkedList<Actor> of object
// Does: get data from actors.txt file, and count the total actors
LinkedList<Actor> SixDegrees::populate_graph_from_file(){
    ifstream infile;
    infile.open("actors.txt");
    if (!infile.is_open()){
        cerr << "Could not open actors.txt for reading\n";
        exit(1);
    }

    LinkedList<Actor> actors;
    string actor_name;
    int actor_count = 0;
    while(getline(infile,actor_name)){
        Actor actor(actor_name); // create actor
        actor_count++;

        string movie;
        getline(infile, movie);
        while (movie != "*"){ // signal for the end of current actor
            actor.Insert_movie(movie);
            getline(infile, movie);
        }
        actors.insert(actor); // insert actor after inserting all his movies
                              // into the object
    }
    infile.close();
    return actors;
}

// Function: run
// Parameters: insteam, a reference to in,
//             ostream, a reference to out
// Returns: nothing
// Does: run the program
void SixDegrees::run(istream &in, ostream &out){
    out << "Enter two actor names separated by a new line." << endl;
    out << "Press ctrl-D to quit" << endl << endl;

    populate_graph(); // populate graph first
    string Actor1_name,Actor2_name;

    while(true) { 
        if(!getline(in,Actor1_name)) // end of file
            return;
        while(!object.is_vertex(Actor(Actor1_name))){
            out << "Sorry, " << Actor1_name << " is not in the list" << endl 
                                                                    << endl;
            if(!getline(in,Actor1_name)) // end of file
                return;
        }

        if(!getline(in,Actor2_name)) // end of file
            return;
        while(!object.is_vertex(Actor(Actor2_name))){
            out << "Sorry, " << Actor2_name << " is not in the list" << endl 
                                                                     << endl;
            if(!getline(in,Actor2_name)) // end of file
                return;    
        }                    
        BFS(Actor(Actor1_name),Actor(Actor2_name),out); // run BFS
        out << endl;
    }
}   

// Function: BFS
// Parameters: Actor a,  Actor b
//             ostream, a reference to out
// Returns: nothing
// Does: does Breadth-First Search
void SixDegrees::BFS(Actor a, Actor b, ostream &out){
    object.clear_marks(); 
    object.initialize_path();

    Queue <Actor> q1; // queue 1 - actors to search
    Queue <Actor> q2; // queue 2 - neighbours

    q1.enqueue(a);
    Actor first_to_search;

    while(first_to_search != b && !q1.is_empty()){
        q1.dequeue(first_to_search); // dequeue one actor from the queue 1
        object.mark_vertex(first_to_search); // mark
        object.get_to_vertices(first_to_search, q2); // find neighbours

        while(!q2.is_empty()){ 
            Actor neighbour;
            q2.dequeue(neighbour); // dequeue one actor from the queue 2
            if(!object.is_marked(neighbour)) { // search when it's not marked
                object.update_predecessor(first_to_search, neighbour); 
                q1.enqueue(neighbour); // push into q1
            }
        }
    }
    int cosdar = object.report_path(out, a, b);
    if (cosdar == -1) // no path between actors
        out << a << " and " << b << ": No connection" << endl;
}

// Function: return_graph
// Parameters: none
// Returns: Graph<Actor> object
// Does: Violation of ADT, created for unit test - return graph
Graph<Actor> SixDegrees::return_graph(){
    return object;
}

// Function: get_graph
// Parameters: Graph<Actor> object
// Returns: nothing
// Does: Violation of ADT, created for unit test - insert graph
void SixDegrees::get_graph(Graph<Actor> object){
    this->object = object;
}