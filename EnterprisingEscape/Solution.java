import java.util.*;

class Solution{

    static Scanner scanner = new Scanner(System.in);
    static Map<String, Integer> classes;
    static int x;
    static int y;

    public static void main(String[] args){

	int numCases = Integer.parseInt(scanner.nextLine());

	for(int i = 0; i < numCases; i++){
	    String nums[] = scanner.nextLine().split(" ");
	    
	    int numClasses = Integer.parseInt(nums[0]);//number of different Kinglon classes
	    int width =Integer.parseInt(nums[1]);//width of the grid
	    int height =Integer.parseInt(nums[2]);//height of the grid

	    //map classes to time to defeat
	    classes = new HashMap<String, Integer>();

	    for(int j = 0; j < numClasses; j++){
		String curLine = scanner.nextLine();
		String[] line = curLine.split(" ");
	
		classes.put(line[0], Integer.parseInt(line[1]));
	    }

	    int[][] curGrid = getGrid(height, width);
	}
	

    }

   public static int[][] getGrid(int height, int width){
	int[][] grid = new int[height][width];
	
	for(int i = 0; i < height; i++){
	    char[] curLine = scanner.nextLine().toCharArray();
	    for(int j = 0; j < width; j++){	
		grid[i][j] = classes.get(curLine[0] + "");
	    }
	}

	return grid;
   }

}
