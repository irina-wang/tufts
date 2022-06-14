import java.util.*;

public class ListGraph implements Graph {
    private HashMap<String, LinkedList<String>> nodes = new HashMap<>();

    /* boolean addNode(String n) 
        adds the node n to the graph.
            - accepts string n
            - Returns true if the node was not previously in the graph 
                      false if the node was already present.
    */ 
    public boolean addNode(String n) {
        if (hasNode(n)){
            return false;
        }
        nodes.put(n, new LinkedList<String>());
        return true;
    }

    /* boolean addEdge(String n1, String n2)
        adds an edge from the node n1 to the node n2. 
            - accepts string n1, n2
            - returns true if the edge was not previously in the graph, 
                  and false otherwise. 
            - exceptions: throw NoSuchElementException if n1 or n2 were not 
                        previously added as nodes.
    */ 
    public boolean addEdge(String n1, String n2) {
        if (!hasNode(n1) || !hasNode(n2)) {
            throw new NoSuchElementException();
        }

        if (hasEdge(n1, n2)) {
            return false;
        }
            
        nodes.get(n1).add(n2); 
        return true;
    }

    /* boolean hasNode(String n)
        - accepts string n
        - returns true if the node n was added to the graph previously (and not 
                                                                    removed), 
              and false if not.
    */
    public boolean hasNode(String n) {
        return nodes.containsKey(n);
    }

    /* boolean hasEdge(String n1, String n2)
            - accepts string n1, n2
            - returns true if the edge from n1 to n2 was added to the graph 
                                            previously (and not removed), 
                  and false if not.
    */
    public boolean hasEdge(String n1, String n2) {
        if (hasNode(n1) && hasNode(n2)) {
            return nodes.get(n1).contains(n2);
        }
        return false;
    }


    /* boolean removeNode(String n) 
        removes node n from the graph and all edges to or from n. 
            - accepts string n 
            - returns true if n was previously in the graph, and 
                      false otherwise.

    */
    public boolean removeNode(String n) {
        if (!hasNode(n)) {
            return false;
        }

    // remove edges to node n
        for (String s : nodes.keySet()) {
            if (hasEdge(s, n)) {
                removeEdge(s, n);
            }
        }

    // remove edges from node n
        nodes.remove(n);
        return true;
    }

    /* boolean removeEdge(String n1, String n2) 
        removes the edge from n1 to n2 from the graph
            - accepts string n1, n2
            - returns true if the edge was previously in the graph and 
                      false otherwise. 
            - exceptions: throw NoSuchElementException if n1 or n2 were not
                         previously added as nodes.
    */
    public boolean removeEdge(String n1, String n2) {
	    if (!hasNode(n1) || !hasNode(n2)) { 
            throw new NoSuchElementException();
        }

        if (!hasEdge(n1, n2)) {
          return false;
        }

        nodes.get(n1).remove(n2);
        return true;
    }


    /* List<String> nodes() 
        return a list containing all the nodes in the current graph, 
                in some unspecified order.
    */
    public List<String> nodes() {
        List<String> nodesInGraph = new ArrayList<String>();
        for (String n : nodes.keySet()) {
            nodesInGraph.add(n);
        }

        return nodesInGraph;
    }

    /* List <String> succ(String n) 
        returns a list of all nodes n2 such that there is an edge from 
            n to n2 in the graph, i.e., it returns the successors of n. 
            This method type uses the List (Links to an external site.) 
            interface. 
    */
    public List<String> succ(String n) {
        if (!hasNode(n)) {
            throw new NoSuchElementException();
        }

        List<String> succNodes = new ArrayList<String>();
        for (String n2 : nodes.get(n)) { 
            succNodes.add(n2);
        }
	    return succNodes;
    }


    /* List <String> pred(String n) 
        returns a list (a List<String>) of all nodes n2 such that there is 
            an edge from n2 to n in the graph, i.e., it returns the predecessors
            of n. This method should throw NoSuchElementException if n was not 
            previously added as a node.
    */
    public List<String> pred(String n) {
	    if (!hasNode(n)){
            throw new NoSuchElementException();
        }

        List<String> predNodes = new ArrayList<String>();
        List<String> nodesInGraph = nodes();

        for (String n2 : nodesInGraph) { 
            if (hasEdge(n2, n)){
                predNodes.add(n2);
            }
        }
	    return predNodes;
    }

    /* Graph union(Graph g) 
        returns a new graph that includes all the nodes and edges of the 
            current graph and all the nodes and edges of g. Nodes identified 
            by the same string in both graphs are coalesced to be the same 
            node in the returned graph.
    */
    public Graph union(Graph g) {
	    Graph unionGraph = new ListGraph();

        List<String> nodesInGraph = nodes();
        List<String> nodesInNewGraph = g.nodes();

    // adding all nodes to graph g
        for (String n1 : nodesInGraph) {
            unionGraph.addNode(n1);
        }
        
        for (String n2 : nodesInNewGraph) {
            unionGraph.addNode(n2);
        }

    // edge in g
        for (String n : nodesInGraph) {
            List<String> successors = succ(n);
            for (String succ : successors) {
                unionGraph.addEdge(n, succ);
            }

            List<String> predecessors = pred(n);
            for (String pred : predecessors) {
                unionGraph.addEdge(pred, n);
            }
        }

        for (String n : nodesInNewGraph) {
            List<String> successorsIng = g.succ(n);
            for (String succ : successorsIng) {
                unionGraph.addEdge(n, succ);
            }

            List<String> predecessorsIng = g.pred(n);
            for (String pred : predecessorsIng) {
                unionGraph.addEdge(pred, n);
            }
        }

        return unionGraph;
    }

    
    /* Graph subGraph(Set<String> nodes) 
        returns a new graph containing the nodes of the current graph that are
            included in nodes and the current graph's edges among them.
    */
    public Graph subGraph(Set<String> nodes) {
        Graph subGraph = new ListGraph();

    // add nodes to the SubGraph
        for(String n : nodes){
            if(hasNode(n)){
                subGraph.addNode(n);
            }
        }

    // add edges to the SubGraph  
        List<String> nodesInSubGraph = subGraph.nodes();
        for (String n1 : nodesInSubGraph) {
            for (String n2 : nodesInSubGraph) {
                if (hasEdge(n1, n2)) {
                    subGraph.addEdge(n1, n2);
                }

                if (hasEdge(n2, n1)) {
                    subGraph.addEdge(n2, n1);
                }
            }
        }
	    return subGraph;
    }


    /* boolean connected(String n1, String n2) 
        returns true if and only if there is a path from n1 to n2, 
            meaning there is a sequence of edges from n1 to some na 
            to some nb etc to n2. If n1.equals(n2), this method should 
            return true, i.e., a path of length 0 counts. 
    */
    public boolean connected(String n1, String n2) {
        if (!hasNode(n1) || !hasNode(n2)) {
            throw new NoSuchElementException();
        }

	    if ( n1.equals(n2) ){
            return true;
        }

        Queue<String> nodeQueue = new LinkedList<String>();
        HashSet<String> visited = new HashSet<String>();

        nodeQueue.add(n1);
        visited.add(n1);
        
        while(!nodeQueue.isEmpty()){
            String node = nodeQueue.poll();

            for (String nextNode : succ(node)) {
                if (nextNode.equals(n2)){
                    return true;
                }

                if (!visited.contains(nextNode)) {
                    visited.add(nextNode);
                    nodeQueue.add(nextNode);
                }
            }
        }

        return false;
    }
}
