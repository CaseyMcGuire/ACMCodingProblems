import java.util.*;

class Solution{

    static Scanner in = new Scanner(System.in);
    static Map<String, String> languages = new HashMap<String, String>();

    public static void main(String[] args){
	
	//get the number of languages there are
	int numLanguages = in.nextInt();
	
	//map every language to its vocabulary
	for(int i = 0; i < numLanguages; i++){
	    String[] words = in.nextLine().split(" ");
	    String language = words[0];
	    for(String s: words){
		languages.put(s.toLowerCase(), language);
	    }
	}

	//get rid of blank line
	in.nextLine();
	
	//for each sentence, print out the language associated with it
	while(in.hasNextLine()){
	    String[] sentence = in.nextLine().split(" ");
	    for(String s: sentence){
		String language = null;
		if((language = languages.get(s.toLowerCase())) != null){
		    System.out.println(language);
		    break;
		}
		
	    }
	}

    }



}
