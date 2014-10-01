import java.util.*;
class Solution {

    static Scanner in = new Scanner(System.in);

    public static void main(String[] args){
	
	//put all the number of times 
	List<Long> list = new ArrayList<>();
	while(in.hasNextLine()){

	    list.add(getNumLines(in.nextLong()));
	}
	for(Long l: list){
	    System.out.println(l);
	}
	

    }

    /*
      Returns the number of times the sequence n, 2n, 3n, 4n, ... must be applied
      until every decimal integer appears at least once.
     */
    public static long getNumLines(long n){
	Set<Character> nums = new HashSet<>();
	for(int i = 48; i <= 57; i++){
	    nums.add((char) i);
	}

	long numLines = 0;
	long curNum = n;
	
	while(!nums.isEmpty()){
	    char[] cur = String.valueOf(curNum).toCharArray();
	 
	    for(char c: cur){
		nums.remove(c);
	    }
	    numLines++;
	    curNum = n * (numLines + 1);
	}

	return numLines;
    }

}
