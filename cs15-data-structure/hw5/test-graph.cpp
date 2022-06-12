/*
 * test-graph.cpp
 * COMP15
 * Spring 2019
 * 
 * Small unit test for the actor,graph and sixdegrees class using google Test 
 * 
 * created by Irina Mengqi Wang
 * Date 04/01/2019
 */

#include "Graph.h"
#include "SixDegrees.h"
#include "Actor.h"
#include <gtest/gtest.h>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

class Graphclass : public ::testing::Test {
protected:
/**
 * This a TEST Fixture in Google Test. It is used to define data that
 * many tests can use. Each test gets its own copy of the same data.
 * Here, We define a testdata vector with some predefined numbers
 * The array is initialized in the constructor. No clean up is needed.
**/
        const std::vector<string> testdata;
        Graphclass()
            : testdata{"Steve Martin", "Edward Norton", "Patrick Swayze",
                        "Hilary Duff", "Alicia Silverstone","Jamie Foxx",
                        "Sam Elliott"} {}
};


class SixDegreesclass : public ::testing::Test {
protected:
/**
 * This a TEST Fixture in Google Test. It is used to define data that
 * many tests can use. Each test gets its own copy of the same data.
 * Here, We define a testdata vector with some predefined numbers
 * The array is initialized in the constructor. No clean up is needed.
**/
        const std::vector<string> test_data;
        SixDegreesclass()
            : test_data{"Steve Martin", "Edward Norton", "Patrick Swayze",
                        "Hilary Duff", "Alicia Silverstone","Jamie Foxx",
                        "Sam Elliott"} {}
};


TEST_F(Graphclass, populate_graph) {
        SixDegrees sd;
        
        sd.populate_graph();
        Actor actor1("Steve Martin");
        Actor actor2("Edward Norton");
        Actor actor3("Patrick Swayze");
        Actor actor4("Hilary Duff");

        // function return_graph is only created for unit test
        Graph<Actor> result_graph = sd.return_graph();

        // check vertices
        EXPECT_EQ(result_graph.get_vertex_at(0),actor1);
        EXPECT_EQ(result_graph.get_vertex_at(1),actor2);
        EXPECT_EQ(result_graph.get_vertex_at(2),actor3);
        EXPECT_EQ(result_graph.get_vertex_at(3),actor4);


        // check edges
        Actor actor5("Allison Janney");
        Actor actor6("Jamie Foxx");

        Actor actor7("Meryl Streep");
        Actor actor8("Stanley Tucci");
        EXPECT_EQ(result_graph.get_edge(actor1,actor4), "Cheaper by the Dozen");
        EXPECT_EQ(result_graph.get_edge(actor5,actor6), ""); // no connecion
        EXPECT_EQ(result_graph.get_edge(actor7,actor8), 
                                        "The Devil Wears Prada");
                                        // more than one connection

}

TEST(Actor, Insert_movie) {
        Actor act("ACTOR");

        act.Insert_movie("a");
        act.Insert_movie("b");
        act.Insert_movie("c");
        act.Insert_movie("d");
        act.Insert_movie("e");
        act.Insert_movie("f");

        EXPECT_TRUE(act.Actor_is_in("a"));
        EXPECT_FALSE(act.Actor_is_in("h"));
}

TEST(Actor, connect) {
        Actor act("ACTOR");
        Actor act2("ACTOR2");

        // No same movie
        act.Insert_movie("a");
        act.Insert_movie("b");
        act.Insert_movie("c");
        act2.Insert_movie("d");
        act2.Insert_movie("e");
        act2.Insert_movie("f");

        EXPECT_EQ(act.connect(act2),"");
        
        // One same movie
        act2.Insert_movie("b");
        EXPECT_EQ(act.connect(act2),"b");

        // More than one same movie
        act2.Insert_movie("a");
        EXPECT_EQ(act.connect(act2),"b");

        // connect to itself
        EXPECT_EQ(act.connect(act),"");
}


TEST(Actor, operator_double_equal) {
        Actor act("ACTOR");
        Actor act2("ACTOR2");
        Actor act3("ACTOR");

        // Actors with different names
        EXPECT_FALSE(act.operator==(act2));

        // Actors with same names
        EXPECT_TRUE(act.operator==(act3));

        // Actors with same names but different movies
        act.Insert_movie("b");
        act.Insert_movie("c");
        EXPECT_TRUE(act.operator==(act3));
}


TEST(Actor, operator_not_equal) {
        Actor act("ACTOR");
        Actor act2("ACTOR2");
        Actor act3("ACTOR");

        // Actors with different names
        EXPECT_TRUE(act.operator!=(act2));

        // Actors with same names
        EXPECT_FALSE(act.operator!=(act3));

        // Actors with same names but different movies
        act.Insert_movie("b");
        act.Insert_movie("c");
        EXPECT_FALSE(act.operator!=(act3));
}

TEST(Graph, insert) {
        Graph<int> g;

        g.initialize_graph(6);
        g.add_vertex(1);
        g.add_vertex(2);
        g.add_vertex(4);
        g.add_vertex(8);
        g.add_vertex(16);
        g.add_vertex(32);

        // The items you’re searching for are in the graph
        EXPECT_EQ(g.get_vertex_at(0), 1);
        EXPECT_EQ(g.get_vertex_at(1), 2);
        EXPECT_EQ(g.get_vertex_at(2), 4);
        EXPECT_EQ(g.get_vertex_at(3), 8);
        EXPECT_EQ(g.get_vertex_at(4), 16);
        EXPECT_EQ(g.get_vertex_at(5), 32);
 
        EXPECT_ANY_THROW(g.get_vertex_at(6));

        // The items you’re searching for are not in the graph
        EXPECT_ANY_THROW(g.get_vertex_at(7));
}

TEST_F(Graphclass, operator_equal) {
        Graph<Actor> g;

        g.initialize_graph(8);
        
        // Insert vertices
        for (string name : testdata){
                Actor a(name);
                g.add_vertex(a);
        }
        
        // Copy Constructor
        Graph<Actor> g2; 

        g2 = g;

        // Check if the copy succeed
        for(int i = 0; i < 6; i++)
                EXPECT_EQ(g2.get_vertex_at(i),g.get_vertex_at(i));

        // Change the original graph
        Actor b("NEW_ACTOR");
        g.add_vertex(b);
        EXPECT_NE(g2.get_vertex_at(7),b);

        // Change the new graph
        Actor c("ANOTHER_NEW_ACTOR");
        g2.add_vertex(c);
        EXPECT_NE(g.get_vertex_at(7),c);
}

TEST_F(Graphclass, copy_constructor) {
        Graph<Actor> g;

        g.initialize_graph(8);
        
        // Insert vertices
        for (string name : testdata){
                Actor a(name);
                g.add_vertex(a);
        }
        
        // Copy Constructor
        Graph<Actor> g2(g); 

        // Check if the copy succeed
        for(int i = 0; i < 6; i++)
                EXPECT_EQ(g2.get_vertex_at(i),g.get_vertex_at(i));

        // Change the original graph
        Actor b("NEW_ACTOR");
        g.add_vertex(b);
        EXPECT_NE(g2.get_vertex_at(7),b);

        // Change the new graph
        Actor c("ANOTHER_NEW_ACTOR");
        EXPECT_NE(g.get_vertex_at(7),c);
}

TEST_F(Graphclass, get_edge) {
        Graph<Actor> g;

        g.initialize_graph(8);
        
        // Insert vertices
        for (string name : testdata){
                Actor a(name);
                g.add_vertex(a);
        }
        
        // When there's no edge
        EXPECT_EQ(g.get_edge(g.get_vertex_at(3), g.get_vertex_at(5)),NULL_EDGE);

        // Add more subedges
        g.add_edge(g.get_vertex_at(3), g.get_vertex_at(4), "edge1");
        g.add_edge(g.get_vertex_at(4), g.get_vertex_at(5), "edge2");

        EXPECT_EQ(g.get_edge(g.get_vertex_at(3), g.get_vertex_at(5)),NULL_EDGE);
        
        // Add one edge
        g.add_edge(g.get_vertex_at(3), g.get_vertex_at(5), "edge");
        EXPECT_EQ(g.get_edge(g.get_vertex_at(3), g.get_vertex_at(5)),"edge");


        // Add other edges
        g.add_edge(g.get_vertex_at(3), g.get_vertex_at(5), "edge1");
        g.add_edge(g.get_vertex_at(3), g.get_vertex_at(5), "edge2");
        EXPECT_EQ(g.get_edge(g.get_vertex_at(3), g.get_vertex_at(5)),"edge");
}

TEST_F(Graphclass, report_path_no_path) {
        Graph<Actor> g;

        stringstream ss;
        string result;

        g.initialize_graph(8);
        
        // Insert vertices
        for (string name : testdata){
                Actor a(name);
                g.add_vertex(a);
        }

        // no path 
        string expected_result = "";

        g.report_path(ss, g.get_vertex_at(0),g.get_vertex_at(3));
        result = ss.str();
}



TEST_F(Graphclass, report_path_one_path) {
        Graph<Actor> g;

        stringstream ss;
        string result;

        g.initialize_graph(8);
        
        // Insert vertices
        for (string name : testdata){
                Actor a(name);
                g.add_vertex(a);
        }

        // only one path 
        g.update_predecessor(g.get_vertex_at(0),g.get_vertex_at(1));
        g.update_predecessor(g.get_vertex_at(1),g.get_vertex_at(2));
        g.update_predecessor(g.get_vertex_at(2),g.get_vertex_at(3));

        string expected_result = "Steve Martin and Hilary Duff have a costar ";
        expected_result += "distance of 3\nSteve Martin was in  with Edward ";
       expected_result += "Norton\nEdward Norton was in  with Patrick Swayze\n";
        expected_result += "Patrick Swayze was in  with Hilary Duff\n";

        g.report_path(ss, g.get_vertex_at(0),g.get_vertex_at(3));
        result = ss.str();

        EXPECT_EQ(expected_result, result);
}




TEST_F(SixDegreesclass, BFS) {
        Graph<Actor> g;

        stringstream ss;
        string result;

        g.initialize_graph(7);
        
        // Insert vertices
        for (string name : test_data){
                Actor a(name);
                g.add_vertex(a);
        }

        // Insert 4 Edges - no path to Vertex 5,6
        g.add_edge(g.get_vertex_at(0), g.get_vertex_at(1), "first");
        g.add_edge(g.get_vertex_at(1), g.get_vertex_at(2), "second");
        g.add_edge(g.get_vertex_at(2), g.get_vertex_at(3), "third");
        g.add_edge(g.get_vertex_at(3), g.get_vertex_at(4), "fourth");
        SixDegrees sd;

        // Get graph 
        sd.get_graph(g);

        // Test case: one path 
        sd.BFS(g.get_vertex_at(0),g.get_vertex_at(2),ss);
        result = ss.str();

        string expected_result = "Steve Martin and Patrick Swayze have a ";
        expected_result += "costar distance of 2\nSteve Martin was in ";
        expected_result += "first with Edward Norton\nEdward Norton";
        expected_result += " was in second with Patrick Swayze\n";

        EXPECT_EQ( expected_result, result);

        // Test case: no path 
        stringstream ss1;
        string result1;
        sd.BFS(g.get_vertex_at(0),g.get_vertex_at(5),ss1);
        result1 = ss1.str();

        string expeced_result_1 = "Steve Martin and Jamie Foxx: ";
        expeced_result_1 += "No connection\n";
        EXPECT_EQ( expeced_result_1, result1);

        // Insert new paths
        g.add_edge(g.get_vertex_at(0), g.get_vertex_at(2), "fifth");
        g.add_edge(g.get_vertex_at(0), g.get_vertex_at(3), "sixth");

        // Get new graph 
        sd.get_graph(g);

        // Test case: more than one path 
        stringstream ss2;
        string result2;
        sd.BFS(g.get_vertex_at(0),g.get_vertex_at(4),ss2);
        result2 = ss2.str();

        string expected_result_2 ="Steve Martin and Alicia Silverstone have a ";
        expected_result_2 += "costar distance of 2\nSteve Martin was in ";
        expected_result_2 += "sixth with Hilary Duff\nHilary Duff";
        expected_result_2 += " was in fourth with Alicia Silverstone\n";
        
        EXPECT_EQ( expected_result_2, result2);
}

