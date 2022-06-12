/*
 *
 * Filename: search-campus.cpp
 * Contains: Driver for lab 9, BFS for the Tufts campus 
 * Part of: Lab assignment "Graph Traversal" for Comp 15
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
using namespace std;

const int NUM_BUILDINGS = 15;

void populate_graph_from_file(char *, Graph<string> &);
void BFS(Graph<string> &, string, string);

// Function: main
// Parameters: integer and string
// Returns: integer
// Does: main driver: reads filcname given by parameter
//       asks for start and end destinations and runs BFSon graph
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Error. This program needs one parameter. Execute using: ./search [inputfile]\n";
        return 1;
    }

    Graph<string> g(NUM_BUILDINGS);
    populate_graph_from_file(argv[1], g);

    string start, end;
    cout << "Where are you starting from?\n";
    cin >> start;
    while (!g.is_vertex(start))
    {
        cout << "Never heard of it. Enter again, please\n";
        cin >> start;
    }

    cout << "Where are you going to?\n";
    cin >> end;
    while (!g.is_vertex(end))
    {
         cout << "No such place. Enter again, please\n";
         cin >> end;
    }

    cout << "\nHow to get there:\n";
    BFS(g, start, end);

    return 0;
}

// Function populate_graph_from_file
// Parameters: char *filename of adjacency matrix, Graph of strings (ref)
// Returns: void
// Does: creates one vertex for each building
//       and one edge for each non-zero entry in adjacency matrix
void populate_graph_from_file(char *filename, Graph<string> &g)
{
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open())
    {
        cerr << "Could not open " << filename << " for reading\n";
        exit(1);
    }

    string buildings[NUM_BUILDINGS];
    string v;

    for (int i = 0; i < NUM_BUILDINGS; i++)
    {
        infile >> v;
        buildings[i] = v;
        g.add_vertex(v);
    }

    for (int i = 0; i < NUM_BUILDINGS; i++)
    {
        infile >> v;
        for (int j = 0; j < NUM_BUILDINGS; j++)
        {
            int edge_weight;
            infile >> edge_weight;
            if (edge_weight > 0)
                g.add_edge(v, buildings[j], edge_weight);
        }
    }
    infile.close();
}


// Function populate_graph_from_file
// Parameters: graph, start node and end node
// Returns: void
// Does: searches for a shortest path from start to end
//       using BFS and reports the path found (if any)
//       you can assume that the path always exists
void BFS(Graph<string> &g, string start, string end)
{
    g.clear_marks();
    g.initialize_path();

    Queue <string> q1;
    Queue <string> q2;

    q1.enqueue(start);

    while(!q1.is_empty()){
        string vtx_to_search;
        q1.dequeue(vtx_to_search);
        g.mark_vertex(vtx_to_search);
        g.get_to_vertices(vtx_to_search, q2);

        while(!q2.is_empty()){ 
            string neighbour;
            q2.dequeue(neighbour);

            if(!g.is_marked(neighbour)) {
                g.update_predecessor(vtx_to_search, neighbour); 
                q1.enqueue(neighbour); // push into q1
            }
        }
    }

    // Report path if one exists.
    g.report_path(cout, start, end);
}


