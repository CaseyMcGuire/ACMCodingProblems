import java.awt.Point;    
class Node implements Comparable<Node>{

	int dist;
	Point p;
	
	public Node(int d, Point p){
	    this.dist = d;
	    this.p = p;
	}

	
	public int compareTo(Node n){
	    return this.dist - n.dist;
	}
	
    }
