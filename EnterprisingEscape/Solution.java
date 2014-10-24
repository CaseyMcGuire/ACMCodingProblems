import java.util.*;
import java.io.*;
import java.awt.Point;
class Solution{
    
   
    static Scanner scanner;// = new Scanner(System.in);
    static Map<String, Integer> classes;
    static TreeMap<Integer, Point> pq;// = new TreeMap<Integer, Point>();
    static boolean[][] closedSet;
    static int[][] dist;
    static int x;
    static int y;

    static int height;
    static int width;

    public static void main(String[] args){

	//	try{
	    scanner = new Scanner(System.in);
	    //	}
	//	catch(FileNotFoundException e){}

	int numCases = Integer.parseInt(scanner.nextLine());

	for(int i = 0; i < numCases; i++){
	    String nums[] = scanner.nextLine().split(" ");
	    
	    int numClasses = Integer.parseInt(nums[0]);//number of different Kinglon classes
	    width =Integer.parseInt(nums[1]);//width of the grid
	    height =Integer.parseInt(nums[2]);//height of the grid

	    //map classes to time to defeat
	    classes = new HashMap<String, Integer>();
	    pq = new TreeMap<Integer, Point>();

	    for(int j = 0; j < numClasses; j++){
		String curLine = scanner.nextLine();
		String[] line = curLine.split(" ");

		classes.put(line[0], Integer.parseInt(line[1]));
	    }

	    int[][] curGrid = getGrid();
	     System.out.println(findShortestPath(curGrid));
	    
	}
	
	
    }
    //set up our grids
    public static int[][] getGrid(){
	int[][] grid = new int[height][width];
	closedSet = new boolean[height][width];
	dist = new int[height][width];
	
	for(int i = 0; i < height; i++){
	    char[] curLine = scanner.nextLine().toCharArray();
	    for(int j = 0; j < width; j++){
		String curLetter = curLine[j] + "";
	
		//we found the enterprise
		if(curLetter.equals("E")){
		    grid[i][j] = 0;
		    dist[i][j] = 0;
		    x = j;
		    y = i;
		    closedSet[i][j] = true;
		    pq.put(dist[i][j], new Point(i, j));
		}
		//otherwise there is an enemy ship
		else{
		    grid[i][j] = classes.get(curLetter);
		    dist[i][j] = Integer.MAX_VALUE;
		}
	    }
	  
	}

	return grid;
    }
    
    public static int findShortestPath(int[][] grid){

	
	while(!pq.isEmpty()){
	    Integer lowestKey = pq.firstKey();
	    Point cur = pq.get(lowestKey);
	    pq.remove(lowestKey);
	    
	   
	    int curX = cur.y;
	    int curY = cur.x;

	    

	    if(curX == 0 ||curX == width - 1 || curY == 0 || curY == height -1){
		return dist[curY][curX];
	    }

	    Point[] neighbors = getNeighbors(cur);
	    for(Point p: neighbors){
		if(p.x >= width || p.x < 0  || p.y >= height || p.y < 0){
		    continue;
		}
		int curDist = dist[curY][curX] + grid[p.y][p.x];
		
		if(curDist < dist[p.y][p.x]){
		    dist[p.y][p.x] = curDist;
		 
		}
		//if the neighbor node is not on the open list or has not been already explored,
		//add to our 'priority queue'
		if(closedSet[p.y][p.x] == false){
		    closedSet[p.y][p.x] = true;
		    pq.put(dist[p.y][p.x], new Point(p.y, p.x));
		}
	    }
	}
	return -1;
    }

    //return all neighbors of this point
    public static Point[] getNeighbors(Point p){
	Point[] array = new Point[4];
	array[0] = new Point(p.y - 1, p.x);
	array[1] = new Point(p.y + 1, p.x);
	array[2] = new Point(p.y, p.x - 1);
	array[3] = new Point(p.y, p.x + 1);
	return array;
    }
    
}
