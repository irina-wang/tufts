public class Edge {
    private String src, dst; // source, destination
    Edge(String src, String dst) {
	this.src = src; this.dst = dst;
    }
    
    String getSrc() { return src; }
    String getDst() { return dst; }
}