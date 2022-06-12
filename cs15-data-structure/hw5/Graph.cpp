/*
 * Filename: Graph.cpp
 * Contains: Implementation of the template Graph class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Spring 2019
 * 
 * Modified by: Mengqi Irina Wang
 * Date: 2019/04/03
 *
 */

#include <iostream>
#include <exception>
#include "Graph.h"
#include "Stack.h"
#include "Actor.h"
using namespace std;

// Function: constructor
// Parameters: none
// Returns: nothing
// Does: default constructor. Initializes with zero vertices
template<class Vertex>
Graph<Vertex>::Graph()
{
    curr_vertex = 0;
    edges = NULL;
    path = NULL;
    vertices = NULL;
    marks = NULL;
}

// Function: parametrized constructor
// Parameters: integer (size of graph)
// Returns: nothing
// Does: default constructor. Initializes with num_v vertices
template<class Vertex>
Graph<Vertex>::Graph(int num_v)
{
    initialize_graph(num_v);
}

// Function: destructor
// Parameters: none
// Returns: nothing
// Does: destruct "newed" memory
template<class Vertex>
Graph<Vertex>::~Graph(){
    remove();
}

// Function: remove
// Parameters: none
// Returns: nothing
// Does: destruct "newed" memory and was called by destructor
template<class Vertex>
void Graph<Vertex>::remove(){
    if(edges != NULL) { // delete edges
        for (int i = 0; i < num_vertices; i++){
            delete [] edges[i];
        }
        delete [] edges;
    }
    edges = NULL;
    
    if(marks != NULL) { 
        delete [] marks;
    }
    marks = NULL;

    if(path != NULL) {
        delete [] path;
    }
    path = NULL;

    if(vertices != NULL) {
        delete [] vertices;
    }
    vertices = NULL;

    this->curr_vertex = 0; 
    this->num_vertices = 0;
}

// Function: copy constructor
// Parameters: a reference to a Graph<Vertex> source
// Returns: Graph<Vertex> 
// Does: copy constructor. construct an object and copy source over to this
template<class Vertex>
Graph<Vertex>::Graph(const Graph<Vertex> &source){
    copy(source);
}

// Function: copy
// Parameters: a reference to a Graph<Vertex> source
// Returns: none
// Does: copy source over to this and is called by copy construtor and 
//       assignment overload
template<class Vertex>
void Graph<Vertex>::copy(const Graph<Vertex> &source)
{
    if (source.edges != NULL) {
        curr_vertex = source.curr_vertex; 
        num_vertices = source.num_vertices;

        vertices = new Vertex[num_vertices]; 
        marks = new bool[num_vertices];
        path = new int[num_vertices];
        edges = new string*[num_vertices]; 
    
        for (int i = 0; i < num_vertices; i++) {
            edges[i] = new string[num_vertices];
            marks[i] = source.marks[i];
            path[i] = source.path[i];
            vertices[i] = source.vertices[i];
            for (int j = 0; j < num_vertices; j++)
                edges[i][j] = source.edges[i][j]; 
        }
        return;
    }
}


// Function: assignment operator
// Parameters: a reference to a Graph<Vertex> source
// Returns: Graph<Vertex>
// Does: copy constructor. Initializes with zero vertices
template<class Vertex>
Graph<Vertex>& Graph<Vertex>::operator=(const Graph<Vertex> &source)
{
    if( this != &source){
        remove(); // delete the data in orignal Graph
        copy(source);
    }
    return *this;
}


// Function: initialize_graph
// Input: integer, number of vertices
// Returns: void
// Does: dynamically allocates all memory
//       for a graph of num_v vertices 
//       without any vertices
//       and prepares all DFS,BFS variables
template<class Vertex>
void Graph<Vertex>::initialize_graph(int num_v)
{
    curr_vertex = 0;
    num_vertices = num_v;
    vertices = new Vertex[num_vertices];
    marks = new bool[num_vertices];
    path = new int[num_vertices];

    edges = new string*[num_vertices];
    for (int i = 0; i < num_vertices; i++)
        edges[i] = new string[num_vertices];

    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
        path[i] = NULL_PRED;
        for (int j = 0; j < num_vertices; j++)
            edges[i][j] = NULL_EDGE;
    }

    initialize_path();
}

// Function: add_vertex
// Parameters: Vertex, by value
// Returns: void
// Does: Add a new vertex to the end of the 2d array
//       Initializes every from/to edge to be NULL
template<class Vertex>
void Graph<Vertex>::add_vertex(Vertex v)
{
     vertices[curr_vertex] = v;
     for (int i = 0; i < num_vertices; i++)
     {
         edges[curr_vertex][i] = NULL_EDGE;
         edges[i][curr_vertex] = NULL_EDGE;
     }
     curr_vertex++;
 }

// Function: add_edge
// Parameters: Two vertices, and integer (weight)
// Returns: void
// Does: Adds an edge between the two vertices and 
//       assigns their weight equal to the given integer
//       (in case the edge did not exist) 
template<class Vertex>
void Graph<Vertex>::add_edge(Vertex f, Vertex t, string weight)
{
    int row;
    int col;

    row = index_is(vertices, f);
    col = index_is(vertices, t);
    if (edges[row][col] == NULL_EDGE)
         edges[row][col] = weight;
}


// Function: print_matrix
// Parameters: ostream
// Returns: void
// Does: Prints the 2d adjacency matrix of the graph
template <class Vertex>
void Graph<Vertex>::print_matrix(ostream & out) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
            out << edges[i][j] << " ";
        out << endl;
    }
}


// Function: clear_marks
// Parameters: none
// Returns: none
// Does: sets all the marks to be false
//       For algorithms that need to mark vertices (BFS, DFS)
template<class Vertex>
void Graph<Vertex>::clear_marks()
{
    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
    }
}

// Function: initialize_path
// Parameters: none
// Returns: none
// Does: sets every value in the predecessor path to be NULL vertex
template<class Vertex>
void Graph<Vertex>::initialize_path()
{
    for (int i = 0; i < num_vertices; i++)
        path[i] = NULL_PRED;
}

// Function: update_predecessor
// Parameters: Two vertices
// Returns: None
// Does: sets pred as the predecessor of curr in the path
//       (in case that curr did not have any predecessor)
//       Nothing otherwise.
template<class Vertex>
void Graph<Vertex>::update_predecessor(Vertex pred, Vertex curr)
{
    int pred_index = index_is(vertices, pred);
    int curr_index = index_is(vertices, curr);
    if (path[curr_index] == NULL_PRED)
        path[curr_index] = pred_index;
}

// Function: report_path
// Parameters: ostream to print, start and end vertices
// Returns: none
// Does: finds path from start to end and prints it
//       uses the information stored on predecessor path 
template<class Vertex>
int Graph<Vertex>::report_path(ostream &out, Vertex start, Vertex end) const
{
    if (start == end) return -1; // finding path to itself
    Stack<Vertex> s;
    int index = index_is(vertices, end);
    s.push(vertices[index]);
    bool done = false;
    int cosdar = 0;
    while (!done){
        index = path[index];
        if (index == -1)  return -1; // no path at all
        if (vertices[index] == start)  done = true; // find path - stop looping
        s.push(vertices[index]);
        cosdar ++;
    }
    out << start << " and " << end << " have a costar distance of " 
        << cosdar << endl; // print the distance
    if(s.is_empty()) return -1; // no path
    Vertex v1 = s.top();
    s.pop();
    Vertex v2;
    while (!s.is_empty()){
        out << v1 << " was in ";
        v2 = s.top();
        out << get_edge(v1,v2) << " with " << v2 << endl;
        v1 = v2;
        s.pop();
    }   
    return cosdar;
}

// Function: mark_vertex
// Parameters: Vertex
// Returns: none
// Does: sets the mark of the given vertex to true
template<class Vertex>
void Graph<Vertex>::mark_vertex(Vertex v)
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            marks[i] = true;
    }
}

// Function: is_marked
// Parameters: Vertex
// Returns: bool
// Does: returns true if the vertex is marked
//       false otherwise
template<class Vertex>
bool Graph<Vertex>::is_marked(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return marks[i];
    }
    return false;
}

// Function: is_vertex
// Parameters: vertex
// Returns: bool
// Does: returns true if vertex exists in the graph,
//       false otherwise.
template <class Vertex>
bool Graph<Vertex>::is_vertex(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return true;
    }
    return false;
}

// Function: get_to_vertices
// Parameters: Vertex, queue of vertices by reference
// Returns: void
// Does: Finds all neighbors of the the given vertex
//       enqueues all of its neighbors to the queue
 template<class Vertex>
 void Graph<Vertex>::get_to_vertices(Vertex v, Queue<Vertex> &adj) const
 {
    int from;
    int to;
    from = index_is(vertices, v);
    for (to = 0; to < num_vertices; to++)
        if (edges[from][to] != NULL_EDGE)
            if (vertices[to] != vertices[from])
                   adj.enqueue(vertices[to]);
}

// wrapper function definitions
// Function: index_is
// Parameters: array of vertices, Vertex
// Returns: integer
// Does: Finds the target vertex in the list of vertices
//       returns the index of v
template<class Vertex>
int index_is(Vertex *vertices, Vertex v) 
{
    int index = 0;
    while (!(v == vertices[index]))
        index++;
    return index;
}

// Function: get_edge
// Parameters: Vertex f, Vertex t
// Returns: string, the edge
// Does: Finds the edge between two vertexes and return the thing inside
template<class Vertex>
string Graph<Vertex>::get_edge(Vertex f, Vertex t) const
{
    int row;
    int col;

    row = index_is(vertices, f);
    col = index_is(vertices, t);
    
    return edges[row][col];
}

// Function: get_vertex_at
// Parameters: int i, the index of the corresponding vertex
// Returns: Vertex, the information of the vertex
// Does: returns the vertex at place i
template<class Vertex>
Vertex Graph<Vertex>::get_vertex_at(int i) const
{
    if (i >= num_vertices || i < 0)
        throw out_of_range("The index of the vertes is out of range");
    return vertices[i];
}

template class Graph<int>;
template class Graph<char>;
template class Graph<string>;
template class Graph<Actor>;

