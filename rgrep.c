#include <stdio.h>
#define MAXSIZE 4096

//Funtions
int strleng(char * string);
//int patternlen1(char *line, char *pattern);
int firstOccur(char* line, char c);
int checkSpecial(char* pattern);
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
	//printf("%d\n", checkSpecial(pattern));
	printf("%d\n", n);
	int n = strleng(pattern);
	if(checkSpecial(pattern) != 5000){
		switch(pattern[checkSpecial(pattern)]) {
		case '.' :
			if(strleng(line) == n){
				printf("%s", line);
			}
			else
				return 1;
		case '\\' :
			return 2;
		case '+' :
			return 3;
		case '\?' :
			return 4;
		default :
			return 0;
		}
	}
	else{
		int matches = 0;
		int index = firstOccur(line, pattern[0]);
		//If pattern is empty string, prints all lines
		if(n == 0)
			printf("%s", line);
		//If pattern is length one char and no special chars.
		else if(n==1){
			if(index != 5000){
				/*check for next letter in pattern in line*/
				printf("%s", line);
				return 0;
			}
			//if(patternlen1(line, pattern))
				//printf("%s", line);
		}
		//If pattern length > 1 and no special chars.
		else if (n > 1){
			if(index != 5000){
				matches++;
				/*check for next letter in pattern in line*/
				//printf("index:%d, n:%d ", index, n);
					for(int i = 1, l = strleng(line); i < l; i++){
						if(pattern[i] == line[index + i]){
							matches++;
							//printf("matches:%d ", matches);
							if(matches == n){
								printf("%s", line);
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

/*Strlen function*/
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
/*Checks for any special characters not proceeded by a \(escape char)
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

/*Single letter pattern
returns 1 if first char of pattern is in the letter
int patternlen1(char *line, char *pattern){
//Prints all strings containing single character.
	int matches = 0;
	for(int i = 0; i < 1; i++){
		
		for(int j = 0, l = strleng(line); j < l; j++){
				if(line[j] == pattern[i])
					matches++;					
		}
	}
	if(matches > 0){
		//printf("%s", line);
		return 1;
	}
	return 0;
}
*/