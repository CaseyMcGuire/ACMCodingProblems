import java.util.*;
import java.io.*;
class Solution{

    static Scanner scanner;
    static Map<String, Integer> translator;
    static int numInversions;

    public static void main(String[] args){
	
	try{
	    scanner = new Scanner(new File("input.txt"));
	}
	catch(FileNotFoundException e){}

	while(true){
	    numInversions = 0;
	    int length = Integer.parseInt(scanner.nextLine());
	    translator = new HashMap<String, Integer>();
	    String[] line = scanner.nextLine().split(" ");
	    for(int i = 0; i < length; i++){
		translator.put(line[i], i);
	    }

	    int[] array = new int[length];
	    String[] nextLine = scanner.nextLine().split(" ");
	    for(int i = 0; i < length; i++){
		array[i] = translator.get(nextLine[i]);
	    }
	    countInversions(
	}
	
    }

    public int countInversions(array){
	

    }

   

}
