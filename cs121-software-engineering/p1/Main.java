import javax.swing.plaf.basic.BasicInternalFrameTitlePane.SystemMenuBar;
import java.util.*;

public class Main {

    // Run "java -ea Main" to run with assertions enabled (If you run
    // with assertions disabled, the default, then assert statements
    // will not execute!)
    
	public static void Test_hasNode() {
		System.out.printf("Test for hasNode(): ");
		Graph g = new ListGraph();

	// no nodes
		assert !g.hasNode("a");

	// add nodes
		assert g.addNode("a");
		assert !g.addNode("a"); // can't add same node twice

		assert g.addNode("b");

	// check nodes	
		assert g.hasNode("a");
		assert g.hasNode("b");
		assert !g.hasNode("c");

		System.out.printf("PASSED. \n");
    }

	public static void Test_hasEdge() {
		System.out.printf("Test for hasEdge(): ");
		Graph g = new ListGraph();

	// no node / edge
		assert !g.hasEdge("a", "b");

		// assert !g.addEdge("a", "b" ); // exception 

	// add nodes and edges to construct graph
		//  Nodes: a, b, c
		//  Edges: a -> b, a->c   
		assert g.addNode("a");
		assert g.addNode("b");
		assert g.addNode("c");

	// no edge
		assert !g.hasEdge("a", "b");

		assert g.addEdge("a", "b");
		assert g.addEdge("a", "c");
	
	// Checks added ages 
		assert g.hasEdge("a", "b");
		assert g.hasEdge("a", "c");

	// No reverse age
		assert !g.hasEdge("c", "a");

		System.out.printf("PASSED. \n");
		
    }

	public static void test_edge_funcs(){
		Graph t = new ListGraph();
		String one = "aaa";
		String two = "bbb";
		String three = "ccc";
		t.addNode(one);
		t.addNode(two);
		t.addNode(three);
		t.addEdge(one, two);
		t.addEdge(one, three);
	
	//should return false, there is no such edge declared 
		assert !t.hasEdge(two, three);
	
	t.removeNode(two);
		//should return false, one node has been removed 
		assert !t.hasEdge(one, two);
	
	t.removeNode(three);
		//should return false 
		assert !t.hasNode(three);
	
	//should throw "NoSuchElementException"
		// t.addEdge(one, two);
	}


	public static void Test_removeNode() {
		System.out.printf("Test for removeNode(): ");
		Graph g = new ListGraph();
		
		assert !g.removeNode("a");
		//test node
		assert g.addNode("a");
		assert g.removeNode("a");
		assert !g.removeNode("a");

		System.out.printf("PASSED. \n");
	}

	public static void Test_removeEdge() {
		System.out.printf("Test for removeEdge(): ");
		Graph g = new ListGraph();
		//add nodes and edges to construct graph
		//  Nodes: a, b, c
		//  Edges: a -> b, a->c   
		assert g.addNode("a");
		assert g.addNode("b");
		assert g.addNode("c");
		assert !g.hasNode("d");
		assert g.addEdge("a", "b");
		assert g.addEdge("a", "c");
	
	//Checks that hasEdge() correctly recognizes added edges
		assert g.hasEdge("a", "b");
		assert g.hasEdge("a", "c");
	
	//Checks that hasEdge() correctly recognizes that non-added edges do not 
		//  exist (checks directionality as well).
		assert !g.hasEdge("c", "a");
		assert !g.hasEdge("b", "a");
		assert !g.hasEdge("b", "c");
	
	// Checks that hasEdge() correctly recognizees removed edges do not exist
		//  at each state of the graph during removal of the edges.
	
	// Edge a->b removed
		assert g.removeEdge("a", "b");  // edge to itself
		// assert !g.removeEdge("d", "c"); // exception 
		assert !g.removeEdge("b", "c"); // nodes exist, edge doesn't exist
		assert !g.removeEdge("a", "a"); // edge to itself
		
		assert !g.hasEdge("a", "b");
		assert g.hasEdge("a", "c");

		//Edge a->c removed
		assert g.removeEdge("a", "c");
		assert !g.hasEdge("a", "b");
		assert !g.hasEdge("a", "c");

		System.out.printf("PASSED. \n");
	}

	public static void Test_succ() {
		System.out.printf("Test for succ(): ");
		Graph g = new ListGraph();
		
		// add one node no edges 
		g.addNode("a");
		
		// no edges = no successors 
		assert(g.succ("a").size() == 0);
		
		//add a node & edge
		g.addNode("b");
		g.addEdge("a", "b");
		
		// now successor list should have one node 
		assert(g.succ("a").size() == 1);
		
		// but successor list for node b is still 0
			// since edges are directed
		assert(g.succ("b").size() == 0);
		
		// NoSuchElementException expected 
			// g.succ("hello world");
		System.out.printf("PASSED. \n");
	}

	public static void Test_pred() {
		System.out.printf("Test for pred(): ");
		Graph g = new ListGraph();
		
		// add one node no edges 
		g.addNode("a");
		
		// no edges = no successors 
		assert(g.pred("a").size() == 0);
		
		//add a node & edge
		g.addNode("b");
		g.addEdge("a", "b");

		// still no edges = no successors 
		assert(g.pred("a").size() == 0);
		
		// now successor list should have one node 
		g.addEdge("b", "a");
		assert(g.pred("a").size() == 1);
		
		g.addNode("c");
		g.addNode("d");
		g.addEdge("c", "a");
		g.addEdge("d", "a");

		// but successor list for node b is still 0
			// since edges are directed
		assert(g.pred("a").size() == 3);
		
		// NoSuchElementException expected 
			// g.succ("hello world");
		System.out.printf("PASSED. \n");
	}

    // public static void test1() {
	// 	System.out.printf("Test for test1(): ");
	// 	Graph g = new ListGraph();
	// 	assert g.addNode("a");
	// 	assert g.removeNode("a");
	// 	assert !g.hasNode("a");

	// 	System.out.printf("PASSED. \n");
    // }

    // public static void test2() {
	// 	System.out.printf("Test for test2(): ");
	// 	Graph g = new ListGraph();
	// 	EdgeGraph eg = new EdgeGraphAdapter(g);
	// 	Edge e = new Edge("a", "b");
	// 	assert eg.addEdge(e);
	// 	assert eg.hasEdge(e);
	// 	System.out.printf("PASSED. \n");
    // }
    
	
	public static void Test_addEdge() {
		Graph g = new ListGraph();

		assert g.addNode("a");
		assert g.addNode("b");
		assert g.hasNode("a");
		assert g.hasNode("b");

		// This method should throw NoSuchElementException if n1 or n2 were not previously added as nodes.
		// loop
		// assert g.addEdge("a", "a");
    }

	public static void testEdge() {
		Graph g = new ListGraph();
	
	// add nodes
		assert g.addNode("a");
		assert g.addNode("b");

	// False: remove edge
		assert !g.removeEdge("a","a");
		assert !g.removeEdge("a","b");
		assert !g.removeEdge("b","a");
	
	// add and remove edge
		assert g.addEdge("a","b");
	
	// check edge is not there
		assert !g.hasEdge("a","b");
	}

	public static void Test_union() {
		System.out.printf("Test for union(): ");
		Graph g = new ListGraph();
		Graph h = new ListGraph();

		assert h.addNode("a");
		assert h.addNode("b");
		assert h.addEdge("a","b");
		
		// same node
		assert g.addNode("a");
		assert g.addNode("c");
		assert g.addNode("d");
		assert g.addEdge("a","d");
		
		Graph g_and_h = g.union(h);

		assert g_and_h.hasNode("a");
		assert g_and_h.hasNode("b");
		assert g_and_h.hasNode("c");
		assert g_and_h.hasNode("d");
		assert !g_and_h.hasNode("e");
		assert g_and_h.hasEdge("a","b");
		assert g_and_h.hasEdge("a","d");
		assert !g_and_h.hasEdge("a","c");
		assert !g_and_h.hasEdge("b","d");
		assert !g_and_h.hasEdge("a","z");

		System.out.printf("PASSED. \n");
	}

	public static void Test_subGraph() {
		System.out.printf("Test for subGraph(): ");
		//test subgraph
		Graph g = new ListGraph();
		g.addNode("a");
		g.addNode("b");
		g.addNode("c");
		g.addNode("d");
		g.addEdge("a", "b");
		g.addEdge("a", "c");
		g.addEdge("c", "d");

		Set<String> subgraph_nodes = new HashSet<>();
		subgraph_nodes.add("a");
		subgraph_nodes.add("b");
		subgraph_nodes.add("c");
		subgraph_nodes.add("e");


		Graph subgraph = g.subGraph(subgraph_nodes);
		assert subgraph.hasNode("a");
		assert subgraph.hasNode("b");
		assert subgraph.hasNode("c");
		assert !subgraph.hasNode("d");
		assert !subgraph.hasNode("e");
		assert  subgraph.hasEdge("a","b");
		assert  subgraph.hasEdge("a","c");
		assert !subgraph.hasEdge("c","d");
		assert !subgraph.hasEdge("d","e");
		//test remove
		System.out.printf("PASSED. \n");
	}

	/* Test to assert two non-connected nodes do not evaluate as being connected */
    public static void Test_connected() {
		System.out.printf("Test for connected(): ");
        Graph g = new ListGraph();
        assert g.addNode("A");
        assert g.addNode("B");
        assert g.addNode("C");
        assert g.addNode("D");
        assert g.addNode("E");
        assert g.addNode("F");
        assert g.addNode("G");
        assert g.addEdge("A", "B");
        assert g.addEdge("B", "C");
        assert g.addEdge("C", "D");
        assert g.addEdge("D", "E");
        assert g.addEdge("E", "A");
        assert g.addEdge("F", "G"); // F, G connected to each other only
        // re-adding nodes and edges should return false
        assert !(g.addNode("A"));
        assert !(g.addEdge("E", "A"));
        // main test
        assert !(g.connected("A", "G"));

		System.out.printf("PASSED. \n");
    }

// Test for edge graphs
	public static void Test_Eg_Edge() {
		System.out.printf("Test for Eg_Edge(): ");
		Graph g = new ListGraph();
		EdgeGraph eg = new EdgeGraphAdapter(g);
		Edge e = new Edge("a", "b");
		Edge e1 = new Edge("b", "a");
		Edge e2 = new Edge("a", "c");

		assert !eg.hasEdge(e);
		assert !eg.hasEdge(e1);
		assert !eg.hasEdge(e2);

		assert eg.addEdge(e);
		assert eg.hasEdge(e);
		assert !eg.hasEdge(e1);
		assert !eg.hasEdge(e2);

		assert !eg.addEdge(e);
		assert eg.addEdge(e1);
		assert eg.addEdge(e2);
		assert eg.hasEdge(e1);
		/* has edge
				a <--> b
				   --> c
		*/

		// remove edges 

			/* has edge
					a <-- b
						--> c
			*/
		assert eg.removeEdge(e);
		
		assert eg.hasEdge(e2);
		assert eg.hasNode("a");
		assert eg.hasNode("c");
		assert eg.hasNode("b");

		/* has edge
				a --> c
		*/
		assert eg.removeEdge(e1);

		assert !eg.hasEdge(e);
		assert !eg.hasEdge(e1);

		assert eg.hasNode("a");
		assert eg.hasNode("c");
		assert !eg.hasNode("b");
		
		System.out.printf("PASSED. \n");
    }


	public static void Test_Eg_Node() {
		System.out.printf("Test for Eg_Node(): ");
		Graph g = new ListGraph();
		EdgeGraph eg = new EdgeGraphAdapter(g);
		Edge e = new Edge("a", "b");
		Edge e1 = new Edge("b", "a");
		Edge e2 = new Edge("a", "c");

		assert !eg.hasEdge(e);
		assert !eg.hasEdge(e1);
		assert !eg.hasEdge(e2);
		assert !eg.hasNode("a");
		assert !eg.hasNode("b");
		assert !eg.hasNode("c");
		assert !eg.hasNode("d");

		assert eg.addEdge(e);
		assert eg.hasNode("a");
		assert eg.hasNode("b");
		assert !eg.hasNode("c");
		assert !eg.hasNode("d");

		assert !eg.addEdge(e);
		assert eg.addEdge(e2);
		assert eg.hasNode("b");
		assert eg.hasNode("c");
		assert !eg.hasNode("d");

		System.out.printf("PASSED. \n");
    }

	public static void Test_outNinEdges() {
		System.out.printf("Test for outEdges() and inEdges() : ");
		Graph g = new ListGraph();
		EdgeGraph eg = new EdgeGraphAdapter(g);
		Edge e = new Edge("a", "b");
		Edge e1 = new Edge("b", "a");
		Edge e2 = new Edge("a", "c");

	// no edge added yet 
		assert(eg.outEdges("a").size() == 0);
		assert eg.addEdge(e);

	// added a --> b
		assert(eg.outEdges("a").size() == 1);
		assert(eg.inEdges("a").size() == 0);
		assert(eg.inEdges("b").size() == 1);
		assert(eg.outEdges("b").size() == 0);

		assert eg.addEdge(e1);
		assert eg.addEdge(e2);

	// added a <--> b
	//			--> c
		assert(eg.outEdges("a").size() == 2);
		assert(eg.inEdges("a").size() == 1);
		assert(eg.inEdges("b").size() == 1);
		assert(eg.outEdges("b").size() == 1);
		assert(eg.inEdges("c").size() == 1);
		assert(eg.outEdges("c").size() == 0);

	// remove one edge
		assert eg.removeEdge(e);
		assert eg.removeEdge(e1);

		assert(eg.outEdges("a").size() == 1);
		assert(eg.inEdges("a").size() == 0);
		assert(eg.inEdges("c").size() == 1);
		assert(eg.outEdges("c").size() == 0);


	// remove all edge
		assert eg.removeEdge(e2);

		assert(eg.outEdges("a").size() == 0);
		assert(eg.inEdges("a").size() == 0);
		assert(eg.inEdges("b").size() == 0);
		assert(eg.outEdges("b").size() == 0);
		assert(eg.inEdges("c").size() == 0);
		assert(eg.outEdges("c").size() == 0);
			
		System.out.printf("PASSED. \n");
	}

	public static void Test_eg_union() {
		System.out.printf("Test for eg_union(): ");
		Graph g = new ListGraph();
		Graph h = new ListGraph();
		EdgeGraph EGg = new EdgeGraphAdapter(g);
		EdgeGraph EGh = new EdgeGraphAdapter(h);
		Edge e = new Edge("a", "b");
		Edge e1 = new Edge("b", "a");
		Edge e2 = new Edge("a", "c");
		Edge e3 = new Edge("a", "d");
		Edge e4 = new Edge("b", "d");

		assert EGg.addEdge(e);
		assert EGg.addEdge(e3);

		assert EGh.addEdge(e1);
		assert EGh.addEdge(e2);
		assert EGh.addEdge(e3);
		
		EdgeGraph g_and_h = EGg.union(EGh);

		assert g_and_h.hasNode("a");
		assert g_and_h.hasNode("b");
		assert g_and_h.hasNode("c");
		assert g_and_h.hasNode("d");
		assert !g_and_h.hasNode("e");
		assert g_and_h.hasEdge(e);
		assert g_and_h.hasEdge(e1);
		assert g_and_h.hasEdge(e2);
		assert g_and_h.hasEdge(e3);
		assert !g_and_h.hasEdge(e4);

		System.out.printf("PASSED. \n");
	}

	public static void Test_eg_hasPath() {
		System.out.printf("Test for eg_hasPath(): ");
		Graph g = new ListGraph();
		EdgeGraph EGg = new EdgeGraphAdapter(g);

		Edge e = new Edge("a", "b");
		Edge e1 = new Edge("b", "c");
		Edge e2 = new Edge("c", "d");
		Edge e3 = new Edge("d", "e");
		Edge e4 = new Edge("b", "d");
	
	// create a list
		List<Edge> es = new ArrayList<>();

	// empty graph, empty list --> true 
		assert EGg.hasPath(es);

	// non-empty graph, empty list --> true 
		assert EGg.addEdge(e);
		assert EGg.hasPath(es);

	// empty graph, non-empty list --> false 
		es.add(e);
		assert EGg.removeEdge(e);
		assert !EGg.hasPath(es);

	// bad path
		// es.add(e2);
		// assert EGg.addEdge(e);
		// assert EGg.addEdge(e2);
		// assert !EGg.hasPath(es);

	// has path
		es.add(e1);
		es.add(e2);
		assert EGg.addEdge(e);
		assert EGg.addEdge(e1);
		assert EGg.addEdge(e2);
		assert EGg.hasPath(es);


	// list has one more member
		es.add(e3);
		assert !EGg.hasPath(es);
		
		System.out.printf("PASSED. \n");
	}

	// public static void test1() {
	// 	Graph g = new ListGraph();
	// 	assert g.addNode("a");
	// 	assert g.hasNode("a");
	// }

	// public static void test2() {
	// 	Graph g = new ListGraph();
	// 	EdgeGraph eg = new EdgeGraphAdapter(g);
	// 	Edge e = new Edge("a", "b");
	// 	assert eg.addEdge(e);
	// 	assert eg.hasEdge(e);
	// }

	// public static void test3() {
	// 	Graph g = new ListGraph();
	// 	assert g.addNode("a");
	// 	assert g.addEdge("a", "a");
	// 	assert !g.addNode("a");
	// 	assert !g.addEdge("a", "a");
	// 	g.addNode("b");
	// 	g.addNode("c");
	// 	assert g.hasNode("b");
	// 	assert !g.hasNode("d");
	// 	assert g.hasEdge("a", "a");
	// 	assert !g.hasEdge("b", "c");
	// 	g.addEdge("b", "c");
	// 	g.addEdge("c", "a");
	// 	assert g.connected("a", "a");
	// 	assert g.removeEdge("a", "a");
	// 	assert g.connected("a", "a");
	// 	assert g.connected("c", "c");
	// }

	public static void listGraphTests() {
		addNodeTest();
		addEdgeTest();
		hasNodeTest();
		hasEdgeTest();
		removeNodeTest();
		removeEdgeTest();
		nodesTest();
		succTest();
		predTest();
		unionTest();
		subGraphTest();
		connectedTest();
	}
	
	public static void addNodeTest() {
		Graph g = new ListGraph();
		assert g.addNode("a");
		assert !g.addNode("a");
	}
	
	public static void addEdgeTest() {
		Graph g = new ListGraph();
		
		boolean raisedExn = false;
		try {
			g.addEdge("a", "a");
		} catch (NoSuchElementException e) {
			raisedExn = true;
		} finally {
			assert raisedExn;
		}
		
		g.addNode("a");
		assert g.addEdge("a", "a");
		assert !g.addEdge("a", "a");
		raisedExn = false;
		try {
			g.addEdge("a", "b");
		} catch (NoSuchElementException e) {
			raisedExn = true;
		} finally {
			assert raisedExn;
		}
	}
	
	public static void hasNodeTest() {
		Graph g = new ListGraph();
		assert !g.hasNode("a");
		g.addNode("a");
		assert g.hasNode("a");
	}
	
	public static void hasEdgeTest() {
		Graph g = new ListGraph();
		assert !g.hasEdge("a", "a");
		assert g.addNode("a");
		assert g.addNode("b");
		assert g.addEdge("a", "b");
		assert g.hasEdge("a", "b");
		assert !g.hasEdge("b", "a");
		assert !g.hasEdge("a", "a");
		assert !g.hasEdge("b", "b");
	}
	
	public static void removeNodeTest() {
		Graph g = new ListGraph();
		assert !g.removeNode("a");
		assert g.addNode("a");
		assert !g.removeNode("b");
		assert g.addNode("b");
		assert g.addEdge("a", "b");
		assert g.addEdge("b", "a");
		assert g.removeNode("a");
		assert !g.hasNode("a");
		assert !g.hasEdge("a", "b");
		assert !g.hasEdge("b", "a");
		assert g.hasNode("b");
		assert !g.removeNode("a");
	}
	
	public static void removeEdgeTest() {
		Graph g = new ListGraph();
		assert g.addNode("a");
		assert g.addEdge("a", "a");
		boolean raisedExn = false;
		try {
			g.removeEdge("a", "b");
		} catch (NoSuchElementException exn) {
			raisedExn = true;
		} finally {
			assert raisedExn;
		}
		assert g.addNode("b");
		assert !g.removeEdge("a", "b");
		assert g.removeEdge("a", "a");
	}
	
	public static void nodesTest() {
		Graph g = new ListGraph();
		assert g.addNode("a");
		List<String> ns = g.nodes();
		ns.set(0, "b");
		ns.add("c");
		assert g.hasNode("a");
		assert !g.hasNode("b");
		assert !g.hasNode("c");
	}
	
	public static void succTest() {
		Graph g = new ListGraph();
		boolean raisedExn = false;
		try {
			g.succ("a");
		} catch (NoSuchElementException exn) {
			raisedExn = true;
		} finally {
			assert raisedExn;
		}
		assert g.addNode("a");
		assert g.succ("a").size() == 0;
		assert g.addNode("b");
		assert g.addEdge("b", "a");
		assert g.succ("a").size() == 0;
		assert g.succ("b").size() == 1 && g.succ("b").get(0) == "a";
	}
	
	public static void predTest() {
		Graph g = new ListGraph();
		boolean raisedExn = false;
		try {
			g.pred("a");
		} catch (NoSuchElementException exn) {
			raisedExn = true;
		} finally {
			assert raisedExn;
		}
		assert g.addNode("a");
		assert g.pred("a").size() == 0;
		assert g.addNode("b");
		assert g.addEdge("b", "a");
		assert g.pred("b").size() == 0;
		assert g.pred("a").size() == 1 && g.pred("a").get(0) == "b";
	}
	
	public static void unionTest() {
		Graph g1 = new ListGraph();
		Graph g2 = new ListGraph();
		assert g1.union(g2).nodes().size() == 0;
		assert g1.addNode("a");
		assert g1.union(g2).nodes().equals(g2.union(g1).nodes());
		assert g2.union(g1).nodes().equals(g1.nodes());
		assert g2.addNode("a");
		assert g1.union(g2).nodes().equals(g1.nodes());
		assert g2.addEdge("a", "a");
		assert g1.union(g2).hasEdge("a", "a");
	}
	
	public static void subGraphTest() {
		Graph g = new ListGraph();
		Set<String> query = new HashSet<>();
		assert g.subGraph(query).nodes().size() == 0;
		query.add("a");
		assert g.subGraph(query).nodes().size() == 0;
		g.addNode("a");
		g.addNode("b");
		assert g.subGraph(query).nodes().size() == 1;
	}
	
	public static void connectedTest() {
		Graph g = new ListGraph();
		boolean raisedExn = false;
		try {
			g.connected("a", "a");
		} catch (NoSuchElementException exn) {
			raisedExn = true;
		} finally {
			assert raisedExn;
		}
		assert g.addNode("a");
		assert g.connected("a", "a");
		assert g.addNode("b");
		assert g.addEdge("a", "b");
		assert g.connected("a", "b");
		assert !g.connected("b", "a");
		assert g.addEdge("b", "a");
		assert g.addNode("c");
		assert g.addEdge("a", "c");
		assert g.connected("b", "c");
	}
	
	public static void edgeGraphAdapterIntegrationTest() {
		EdgeGraph g1 = new EdgeGraphAdapter(new ListGraph());
		EdgeGraph g2 = new EdgeGraphAdapter(new ListGraph());
		List<Edge> es = new LinkedList<>();
		es.add(new Edge("a", "b"));
		es.add(new Edge("b", "c"));
		es.add(new Edge("c", "d"));
		es.add(new Edge("d", "e"));
		es.add(new Edge("e", "f"));
		es.add(new Edge("f", "a"));
		for (int i = 0; i < es.size(); i++) {
			if (i % 2 == 0) {
				assert g1.addEdge(es.get(i));
			} else {
				assert g2.addEdge(es.get(i));
			}
		}
		EdgeGraph u = g1.union(g2);
		assert !u.edges().equals(es);
		for (Edge e: es) {
			assert u.hasEdge(e);
		}
		
		List<Edge> es1 = Arrays.asList(new Edge[] {});
		List<Edge> es2 = Arrays.asList(new Edge[] {es.get(0)});
		List<Edge> es3 = Arrays.asList(new Edge[] {es.get(0), es.get(1)});
		List<Edge> es4 = Arrays.asList(new Edge[] {new Edge("a", "c")});
		List<Edge> es5 = Arrays.asList(new Edge[] {es.get(0), es.get(2)});
		assert u.hasPath(es);
		assert u.hasPath(es1);
		assert u.hasPath(es2);
		assert u.hasPath(es3);
		assert !u.hasPath(es4);
		boolean raisedExn = false;
		try {
			u.hasPath(es5);
		} catch (BadPath exn) {
			raisedExn = true;
		} finally {
			assert raisedExn;
		}
	}

	public static void test1() {
		Graph g = new ListGraph();
		assert g.addNode("a");
		assert g.hasNode("a");
    }
    
    public static void test2() {
		Graph g = new ListGraph();
		EdgeGraph eg = new EdgeGraphAdapter(g);
		Edge e = new Edge("a", "b");
		assert eg.addEdge(e);
		assert eg.hasEdge(e);
    }
    
    public static void test3() {
    	Graph g = new ListGraph();
    	// Tests adding nodes
    	assert g.addNode("a");
    	assert g.addNode("b");
    	assert g.addNode("c");
    	assert g.addNode("d");
    	assert g.addNode("e");
    	assert g.hasNode("c");
    	
    	// Tests removing nodes
    	assert g.removeNode("e");
    	assert !g.hasNode("e");
    	
    	// Tests adding edges
    	assert g.addEdge("a", "b");
    	assert g.addEdge("a", "c");
    	assert g.addEdge("a", "d");
    	assert g.addEdge("c", "b");
    	assert g.addEdge("d", "a");
    	assert g.hasEdge("a", "d");
    	assert !g.hasEdge("a", "e");
    	
    	// Tests removing edges
    	assert g.removeEdge("a", "d");
    	assert !g.hasEdge("a", "d");
    	
    	// Tests path connection
    	assert g.connected("d", "a");
    	assert !g.connected("a", "d");
    	
    	assert (g.succ("a").equals(Arrays.asList("b", "c")));
    	assert (g.pred("a").equals(Arrays.asList("d")));
    	
    }
    
    public static void test4() {
    	Graph g = new ListGraph();
    	// Tests adding nodes
    	assert g.addNode("a");
    	assert g.addNode("b");
    	assert g.addNode("c");
    	assert g.addNode("d");
    	assert g.addNode("e");
    	assert g.addEdge("a", "d");
    	
    	Graph u = new ListGraph();
    	
    	assert u.addNode("a");
    	assert u.addNode("b");
    	assert u.addNode("e");
    	assert u.addNode("f");
    	assert u.addNode("g");
    	assert u.addEdge("a", "b");
    	assert u.addEdge("f", "g");
    	
    	Graph ug = g.union(u);
    	
    	assert ug.hasNode("g");
    	assert ug.hasNode("e");
    	assert ug.hasEdge("a", "d");
    	assert ug.hasEdge("a", "b");
    	assert ug.hasEdge("f", "g");
    	assert ug.succ("a").equals(Arrays.asList("d", "b"));
    	
    	Set<String> nodes = new HashSet<>(Arrays.asList("a", "d", "f"));
    	
    	Graph sg = ug.subGraph(nodes);
    	
    	assert sg.hasNode("a");
    	assert !sg.hasNode("g");
    	assert sg.hasEdge("a", "d");
    	assert !sg.hasEdge("f", "g");
    	
    }
    
    
    public static void test5() {
    	Graph g = new ListGraph();
		EdgeGraph eg = new EdgeGraphAdapter(g);
		Edge e = new Edge("a", "b");
		assert eg.addEdge(e);
		assert eg.hasEdge(e);
		assert eg.addEdge(new Edge("c", "d"));
		assert eg.addEdge(new Edge("b", "c"));
		assert eg.addEdge(new Edge("a", "c"));
		assert eg.addEdge(new Edge("a", "d"));
		assert eg.hasNode("b");
		assert eg.hasEdge(new Edge("b", "c"));
		assert eg.removeEdge(e);
		assert !eg.hasEdge(e);
		
		List<Edge> edges = new ArrayList<>();
		edges.add(new Edge("a", "c"));
		edges.add(new Edge("c", "d"));
		assert eg.hasPath(edges);
		
		Graph u = new ListGraph();
		EdgeGraph ug = new EdgeGraphAdapter(u);
		
		assert ug.addEdge(new Edge("d", "f"));
		assert ug.addEdge(new Edge("a", "c"));
		assert ug.addEdge(new Edge("f", "a"));
		
		EdgeGraph union = eg.union(ug);
		
		assert union.hasEdge(new Edge("d", "f"));
		assert union.hasEdge(new Edge("c", "d"));
		assert union.addEdge(new Edge("g", "h"));
		
		List<Edge> unionPath = new ArrayList<>();
		unionPath.addAll(Arrays.asList(new Edge("a", "c"), new Edge("c", "d"), new Edge("d", "f"), new Edge("f", "a")));
		
		assert union.hasPath(unionPath);
		
		unionPath.add(new Edge("a", "b"));
		
		assert !union.hasPath(unionPath);
		try {
			unionPath.remove(1);
			unionPath.remove(3);
			assert !union.hasPath(unionPath);
		}catch(BadPath b) {
			System.out.println("1");
		}
		
		assert !eg.hasEdge(new Edge("g", "h"));
		assert !ug.hasEdge(new Edge("g", "h"));
		
		assert union.addEdge(new Edge("i", "i"));
		assert union.hasNode("i");
		assert union.removeEdge(new Edge("i", "i"));
		assert !union.hasNode("i");
		
		
		
    }
    
    public static void test6() {
    	Graph g = new ListGraph();
    	assert g.addNode("x");
    	assert g.addNode("a");
    	assert g.addNode("b");
    	assert g.addNode("c");
    	assert g.addEdge("x", "a");
    	assert g.addEdge("a", "b");
    	assert g.addEdge("b", "c");
    	assert g.removeNode("a");
    	assert !g.hasNode("a");
    	assert !g.hasEdge("x", "a");
    }
    
    public static void test7() {
    	Graph g = new ListGraph();
    	// Tests adding nodes
    	assert g.addNode("a");
    	assert g.addNode("b");
    	assert g.addNode("c");
    	assert g.addNode("d");
    	assert g.addNode("e");
    	assert g.hasNode("c");
    	
    	// Tests adding edges
    	assert g.addEdge("a", "b");
    	assert g.addEdge("b", "c");
    	assert g.addEdge("c", "a");
    	
    	// Test connected edge cases
    	assert !g.connected("a", "d");
    	
    	assert g.addEdge("c", "d");
    	assert g.connected("a", "d");
    	
    	assert g.connected("d", "d");
    	
    	assert g.addEdge("d", "d");
    	assert g.addEdge("d", "a");
    	assert g.removeEdge("c", "a");
    	assert g.connected("b", "a");
    	
    	
    }
    

    public static void main(String[] args) {
		System.out.println("Start with test cases   ——————————");
	// ListGraph
		Test_hasNode(); 
		Test_hasEdge();
		Test_removeNode();
		Test_removeEdge();
		Test_succ();
		Test_pred();
		Test_union();
		Test_connected();
		Test_subGraph();
		test_edge_funcs();
	
	// EdgeGraphAdapter
		Test_Eg_Edge();
		Test_Eg_Node();
		Test_outNinEdges();
		Test_eg_union();
		Test_eg_hasPath();

		// test
		// test1();
		// test2();

		test1();
		test2();
		test3();

		test1();
		test2();
		test3();
		test4();
		test5();
		test6();
		test7();
		listGraphTests();
		edgeGraphAdapterIntegrationTest();
		System.out.println("End with test cases  ——————————————");
    }

}