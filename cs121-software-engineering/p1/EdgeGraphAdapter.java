import java.util.*;

public class EdgeGraphAdapter implements EdgeGraph {

    private Graph g;

    EdgeGraphAdapter(Graph g) { this.g = g; }

    /* boolean addEdge(Edge e) 
        adds an edge to the graph, 
        - returns true if the edge was not already in the graph or false if not.
            Note that, in this API, nodes are not added separately from edges.
            Node n is automatically added to the graph if an edge containing n 
            is added.
    */
    public boolean addEdge(Edge e) {
        String src = e.getSrc();
        String dst = e.getDst();
        if(hasEdge(e)){
            return false;
        }

        g.addNode(src);
        g.addNode(dst);
        g.addEdge(src, dst);
        return true;
    }


    /* boolean hasNode(String n) 
        returns true if and only if some edge has been added to the graph 
          (and not removed) with n as either the source or destination fo 
          the edge.
    */
    public boolean hasNode(String n) {
        return g.hasNode(n);
    }


    /* boolean hasEdge(Edge e) 
          returns true if edge e has been added to the graph (and not removed).
    */
    public boolean hasEdge(Edge e) {
        return g.hasEdge(e.getSrc(), e.getDst());

    }


    /* boolean removeEdge(Edge e) 
          removed edge e from the graph, 
            - returns true if it was previously in the graph and 
                false otherwise. If this method removes the last edge 
                to or from a given node in the graph, that node should 
                also be removed. Note: This method does not throw an 
                exception even if one or the other end of the Edge is 
                not in the graph.
    */
    public boolean removeEdge(Edge e) {
        if (!hasEdge(e)) {
          return false;
        }
		String src = e.getSrc();
        String dst = e.getDst();

        g.removeEdge(src, dst);

		// check if the removed edge is the last edge for src node
		if (outEdges(src).isEmpty() && inEdges(src).isEmpty()){
			g.removeNode(src);
		}

		// check if the removed edge is the last edge for dst node
		if (outEdges(dst).isEmpty() && inEdges(dst).isEmpty()){
			g.removeNode(dst);
		}
        return true;
    }


    /* List<Edge> outEdges(String n) 
        returns a list of all edges that start at node n. 
    */
    public List<Edge> outEdges(String n) {
    	List<Edge> outEdges = new ArrayList<Edge>();
        
        if (hasNode(n)){
            List<String> succ = g.succ(n);
            // get all sucessors of n and create edges
            for (String s : succ) {
                Edge e = new Edge(n, s);
                outEdges.add(e);
    	    }
        }
    	
    
      
      	return outEdges;
    }

    /* List<Edge> inEdges(String n) 
        returns a list of all edges that end at node n. */
    public List<Edge> inEdges(String n) {
		List<Edge> inEdges = new ArrayList<Edge>();
        if (hasNode(n)){
		    List<String> pred = g.pred(n);

            for (String s : pred) {
                Edge e = new Edge(s, n);
                inEdges.add(e);
            }
        }

    	return inEdges;
    }

	/* List<Edge> edges() 
		returns a list of all the edges in this graph, 
			in some unspecified order.
	*/
    public List<Edge> edges() {
		List<Edge> edges = new ArrayList<Edge>();
		List<String> nodes = g.nodes();

		for (String n : nodes) {
			for (Edge outEdge : outEdges(n)){
				edges.add(outEdge);
			}
		}

		return edges;
    }

	/* EdgeGraph union(EdgeGraph g) 
		returns a new graph that includes all the nodes and edges of the 
			current graph and all the nodes and edges of g. Nodes identified 
			by the same string in both graphs are coalesced to be the same node
			in the returned graph. 
	*/
    public EdgeGraph union(EdgeGraph g) {
		EdgeGraph unionGraph = new EdgeGraphAdapter(new ListGraph());

        List<Edge> edgesInGraph = edges();
        List<Edge> edgesInNewGraph = g.edges();

    // adding all edges to graph g
        for (Edge e1 : edgesInGraph) {
			unionGraph.addEdge(e1);
        }
        
        for (Edge e2 : edgesInNewGraph) {
            unionGraph.addEdge(e2);
        }

        return unionGraph;
    }

	/* boolean hasPath(List<Edge> l) 
			returns true if the path l (a List<Edge>) is in the graph, 
				meaning if l = e1, e2, ..., en then all edges ei are in 
				the graph. The method should also check if the argument 
				is a path, i.e., if ei.getDst() == e(i+1).getSrc() for 
				every edge in the middle of the list. If this is not the 
				case, this code should raise the exception BadPath, which 
				is defined in file BadPath.java. Note that every graph 
				includes the empty path (since if a graph contains a path, 
				it should contain every sub-path).
	*/
    public boolean hasPath(List<Edge> l) {
		// check if all edges are in the graph
		for (Edge e : l) {
			if (!hasEdge(e)){
				return false;
			}
		}
	
		// check condition for correct path
		for (int i = 0; i < l.size() - 1; i++) {
			if (l.get(i).getDst() != l.get(i + 1).getSrc()) {
				throw new BadPath();
			}
		}
        
		return true;
    }

}
