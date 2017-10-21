#include <stdio.h>
#define MAXSIZE 4096

//Funtions
int strleng(char* string);
int firstOccur(char* line, char c);
int checkSpecial(char* pattern);
int sameChar(char* pattern);
int dotPlus(char* pattern);
int matchPatternDots(char* pattern,char* line);
int patternPlus(char* pattern,char* line);
/**
 * You can use this recommended helper function 
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  // Implement if desire 

  return 0;
}

/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
 
 /* . = any char
	+ = preceeding will appear any # of times
	? = preceeding char may or may not appear
	\ = nullifys any special meaning of the previous character
	Usage:
	a+ Matches a, aa, aaaaa or sreally any number of a’s more than one 
	.+ Matches any non-empty String 
	\\+ Matches a string of \’s
	a?b+ Matches ab, b, abbb or any amount of b following op:onal a. 
	\? A question mark must appear in the line 
	they?re Matches a line that contains either the string "theyre" or the string "there" 
	h.d..?n Matches lines that contain substrings like "hidden", "hidin", "hbdwen", "hadbn", etc.
	cu\.?t Matches lines that either contain the substring "cut" or "cu.t" 
	*/
	
int rgrep_matches(char *line, char *pattern){
	int n = strleng(pattern);
	int m = strleng(line);
	if(checkSpecial(pattern) != 5000){
		switch(pattern[checkSpecial(pattern)]) {
		case '.' :
			if(sameChar(pattern))
				if(m - 1 == n)
					return 1;	
				else
					return 0;
				
			else if (dotPlus(pattern))
				return 1;
			else if (matchPatternDots(pattern, line))
				return 1;
			else
				return 0;
		case '\\' :
			return 0;
		case '+' :
			if(n==1)
				return 1;
			if(patternPlus(pattern, line))
				return 1;
			return 0;
		case '\?' :
			return 0;
		default :
			return 0;
		}

	}
	else{
		int matches = 0;
		int index = firstOccur(line, pattern[0]);
		//If pattern is empty string, prints all lines
		if(n == 0){
			return 1;
		//If pattern is length one char and no special chars.
		}
		else if(n==1){
			if(index != 5000){
				/*check for next letter in pattern in line*/
				return 1;
			}
		}
		//If pattern length > 1 and no special chars.
		else if (n > 1){
			if(index != 5000){
				matches++;
				/*check for next letter in pattern in line*/
					for(int i = 1, l = strleng(line); i < l; i++){
						if(pattern[i] == line[index + i]){
							matches++;
							if(matches == n){
								return 1;
							}
						}
						else
							return 0;
					}
			}
			else
				return 0;
				
		}
		return 0;
	}
	return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}

int patternPlus(char* pattern,char* line){
 	int n = strleng(pattern);
 	int m = strleng(line);
	int firstFound[m];
 	int p = firstOccur(pattern, '+');
 	int count = 0;
	int found = 0;
	int index = 0;
	//Pattern length less then = 2
	if(n <= 2){
		for(int i = 0; i< m; i++){
			if(line[i] == pattern[0]){
				found++;
				return 1;
			}
		}
	}
	//Pattern Greater Than 2
	else{
		for(int i = 0; i< m; i++){
			if(line[i] == pattern[0]){
				firstFound[index++] = i;
				count = 1;
			}
		}
		index = 0;
		for(int i = 1; i< n; i++){
			if(line[i] == pattern[i]){
				count++;
			}
		}
		//printf("count: %d,n: %d, line: %s\n", count,n,  line);
		if(count == n-1)
			return 1;
	
	}
 	return 0;
 }
 
 /*
int patternPlus(char* pattern,char* line){
	int n = strleng(pattern);
	int m = strleng(line);
	//int p = firstOccur(pattern, '+');
	int count = 0;
	int firstFound[m];
	int k = 1;
	int temp = 0;
	//printf("%d", n);
	if(n <= 2){
		for(int i = 0; i< m; i++){
			if(line[i] == pattern[0])
				return 1;
		}
	}
	else{
		for(int j = 0; j< m; j++){
			if(line[j] == pattern[0]){
				firstFound[temp++] = j;
				count = 1;
			}
		}
		temp = 0;
		for(int l = 0; l< m; l++){
			if(firstFound[temp] == pattern[k])
				count++;
			if(k != n)
				k++;
		}
	
	}
	if(count == n)
		return 1;
	return 0;
	
}
*/

//Checks for matchs to dot-pattern
int matchPatternDots(char* pattern,char* line){
	int n = strleng(pattern);
	int m = strleng(line);
	int count = 0;
	for(int i = 0; i< m; i++){
		if(line[i] == '.'  || pattern[i] == line[i]){
				count++;
		}
		if(count == n)
			return 1;
	}
	return 0;
	
}


//Checks for a plus after dots
int dotPlus(char* pattern){
	int n = strleng(pattern);
	for(int i = 1; i< n; i++){
		if(pattern[i] == '+')
			return 1;
	}
	return 0;
}

//Checks if pattern is all the same
int sameChar(char *pattern){
	int n = strleng(pattern);
	int m = 0;
	for(int i = 0; i< n; i++){
		if(pattern[i] == pattern[0]){
				m++;
		}
		if(m == n)
			return 1;
	}
	return 0;
}

/*Custom Strlen function*/
int strleng(char * string){

	int i = 0;
	while(string[i] != '\0'){
		i++;
	}
	return i;

}


/*Returns index of first char in string that matches first char in pattern, returns 5000 if no matches*/
int firstOccur(char * line, char  c){
	int n  = strleng(line);
	for(int i = 0; i < n; i++){
			if(line[i] == c)
				return i;
		
	}
	return 5000;
}
/*Checks for the first special character not proceeded by a \(escape char)
returns index of special char or returns 5000
	. = any char
	+ = preceeding will appear any # of times
	? = preceeding char may or may not appear
	\ = nullifys any special meaning of the previous character*/
	
int checkSpecial(char* pattern){
	int n = strleng(pattern);
	//checks for .
	for(int i = 0; i < n; i++){
		if(pattern[i] == '.'){
			if(i != 0 && pattern[i-1] != 92){
				return i;
				
			}
			else
				return i;
		}
	}
	//checks for +
	for(int i = 0; i < n; i++){
		if(pattern[i] == '+'){
			if(i != 0 && pattern[i-1] != 92){
				return i;
				
			}
			else
				return i;
		}
	}	
	//checks for ?
	for(int i = 0; i < n; i++){
		if(pattern[i] == '?'){
			if(i != 0 && pattern[i-1] != 92){
				return i;
				
			}
			else
				return i;
		}
	}	
			
	return 5000;
}

