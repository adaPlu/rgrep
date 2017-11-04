/*
Adam Pluguez
CSE 31
11/3/17
Project 1
rgrep
*/
#include <stdio.h>
#define MAXSIZE 4096

//Functions
int strleng(char* string);
int strlengIgnoreSlash(char* string);
int firstOccur(char* line, char c);
int checkForSpecialChar(char* pattern);
int samePattern(char* pattern);
int patternDotAfterPlus(char* pattern, char* line);
int matchPatternDots(char* pattern,char* line);
int patternSinglePlus(char* pattern,char* line);
int multiplePlus(char* pattern,char* line);
int basicRgrep(char* pattern,char* line, int n, int m);
int quesMark(char * pattern, char* line);
int escapeChar(char* pattern,char* line);
int matchOne(char* pattern,char* line);
int plusDotsCount(char* pattern);
int slashesCount(char* pattern);
int quesCount(char* pattern);

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
int rgrep_matches(char *line, char *pattern){
	int n = strleng(pattern);
	int m = strleng(line);
	if(n==0 || m == 0){
		return 0;
	}
	if(checkForSpecialChar(pattern) != 5000){
		switch(pattern[checkForSpecialChar(pattern)]) {
		case '.' :
			//
			if(samePattern(pattern)){
				if(m == n)
					return 1;	
				else
					return 0;
			}
			else if(firstOccur(pattern, '+') != 5000){
				if (patternDotAfterPlus(pattern, line)){
					return 1;
				}
				return 0;
			}
			else if(firstOccur(pattern, '?') != 5000){
				if (m==n-quesCount(pattern)){
					return 1;
				}
				return 0;
			}
			else if (matchPatternDots(pattern, line)){
				return 1;
			}
			else
				return 0;
		case '\\' :
			if(n==2){
				if(pattern[1] == '?'){
					pattern = "?";
					if(basicRgrep(pattern, line, 1, m))
						return 1;
				}
				else if(pattern[1] == '.'){
					pattern = ".";
					if(basicRgrep(pattern, line, 1, m))
						return 1;
				}
				return 0;
			}
			else if(n==3){
				if(pattern[1] == '\\'){
					if(pattern[2] == '+'){
						pattern = "\\";
						for(int i = 0; i < m; i++){
							if(line[i] == pattern[0])
								return 1;
						}
					}
				}
			}
			else{
				if(escapeChar(pattern, line))
					return 1;
				else
					return 0;
			}
		case '+' :
			if(n==1)
				return 1;
			if(multiplePlus(pattern, line))
				return 1;
			if(patternSinglePlus(pattern, line))
				return 1;
			return 0;
		case '?' :
			if(n==1){
				pattern = "?";
				if(basicRgrep(pattern, line, 1, m))
					return 1;
			}
			else if(quesMark(pattern, line))
				return 1;
			else
				return 0;
		default :
			return 0;
		}

	}
	else{
		if(basicRgrep(pattern , line, n, m))
			return 1;
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
 
/*Checks for the first special character not proceeded by a \(escape char)
returns index of special char or returns 5000*/	
int checkForSpecialChar(char* pattern){
	int n = strleng(pattern);	
	//checks for .
	for(int i = 0; i < n; i++){
		if(pattern[i] == '.'){
			if(i != 0 && pattern[i-1] != '\\'){
				return i;
				
			}
			else if (i == 0)
				return i;
		}
	}
	//checks for +
	for(int i = 0; i < n; i++){
		if(pattern[i] == '+'){
			if(i != 0 && pattern[i-1] != '\\'){
				return i;
				
			}
			else if (i == 0)
				return i;
		}
	}	
	//checks for ?
	for(int i = 0; i < n; i++){
		if(pattern[i] == '?'){
			if(i != 0 && pattern[i-1] != 92){
				return i;
				
			}
			else if (i == 0)
				return i;
		}
	}	
	
	
	//checks for '\\'
	for(int i = 0; i < n; i++){
		if(pattern[i] == '\\'){
			if(i != 0 && pattern[i-1] != 92){
				return i;
				
			}
			else if (i == 0)
				return i;
		} 
	}
	return 5000;
}
 
//Checks for matchs to dot-pattern
int matchPatternDots(char* pattern,char* line){
	int n = strleng(pattern);
	int m = strleng(line);
	int index = 0;
	int matches = 0;
	int slashes = slashesCount(pattern);
	for(int i = 0; i< m; i++){
		if(pattern[index] == '\\')
			index++;
		if(pattern[index] == line[i] || pattern[index] == '.'){
				matches++;
				if(pattern[index] != '\0')
					index++;		
		}
		if(line[i]=='\\'){
			i++;
			if(line[i]=='n'){
				matches =0;
				index=0;				
			}
		}
		if(matches == n|| matches == n - slashes)
			return 1;
	}
	return 0;	
}

//Checks for matches in pattern after a +
int patternDotAfterPlus(char* pattern, char* line){
	int n = strlengIgnoreSlash(pattern);
	int m = strleng(line);
	int matches= 0;
	int i = 0;
	int plusDots = plusDotsCount(pattern); 
	for(int j = 0; j < m; j++){
		if(pattern[i] == '\\'){
			if(i+2 < m && pattern[i+1] == 'n'){
				i = i+1;
			}
			i++;
		}	
		if(i+1 > m && pattern[i] == line[j]){
			matches++;
			if (i != n){
				i++;
			}
		}
		else if(pattern[i] == '+' && pattern[i+1] != '\\'){
			if (i != n){
				i++;
			}
		}
		else if(pattern[i] == '+'|| pattern[i] == '.'){
			if (i != n){
				i++;
		
			}
		}	
		else if(pattern[i] == line[j]){
			matches++;
			if(line[j] == '\n'){
				line[j] = '\0';
			}
			if (i != n){
				i++;
			}
		}
		
	}
	if(  matches == n-1 ||matches == n  || matches >= n - plusDots -1 ){
		return 1;
	}
	return 0;
}

int patternSinglePlus(char* pattern,char* line){
 	int n = strleng(pattern);
 	int m = strleng(line);
 	int p = firstOccur(pattern, '+');
 	int matches = 0;
	int found = 0;
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
				matches = 1;
			}
		}
		for(int i = 1; i< n; i++){
			if(line[i] == pattern[i]){
				matches++;
			}
		}
		
		if(p < n){
			char p2 = pattern[p+1];
			for(int i = p+1; i< n && i < m; i++){
				if(line[firstOccur(line, p2)] == pattern[i]){
					matches++;
				}
			}
		}
		if(matches == n-1 || matches == n)
			return 1;
	}
 	return 0;
 }
 

/*Checks for and deals with multiple plus signs*/
int multiplePlus(char* pattern,char* line){
	int n = strleng(pattern);
	int m = strleng(line);
	int matches = 0;
	int plus = 0;
	char beforePlus[n];
	int temp = 0;
	for(int i = 0; i  < n; i++ ){
		if(pattern[i] == '+'){
			plus++;
			temp++;
			
		}
		else
			beforePlus[temp] = pattern[i];

	}
	temp = 0;
	if(plus < 2)
		return 0;
	else{
		for(int i = 0; i  < n; i++ ){
			for(int j = 0; j  < m; j++ ){
				if (line[j] == beforePlus[i]){
					matches++;
					break;		
				}
			}		
		}
		if(matches >= plus)
			return 1;					
		
		
	}
	return 0;
}

/*Deals with question mark as first occurence in pattern*/
int quesMark(char * pattern, char* line){
	int n = strleng(pattern);
	int m = strleng(line);
	if(m == 0)
		return 0;
	int q = firstOccur(pattern, '?');
	char newPat[n];
	char newPat2[n-1];
	int index = 0;
	int index2 = 0;
	for(int i = 0; i < n; i++){
		if(i== n-1){
			newPat2[index2] = '\0';
		}
		if(pattern[i] != '?' && pattern[i+1] != '?')
			newPat2[index2++] = pattern[i];
		
		if(i == n){
			newPat[index] = '\0';
		}
		else if(i+1< n && pattern[i+1] == '?'&& pattern[i] != '\\'){
			newPat[index++] = '.';

		}
		else if(pattern[i] == '?'){
			if(pattern[i+1] != '\0')
				newPat[index++] = pattern[i+1];
			else
				newPat[i] = '\0';

		}
		else if(i == n-1)
			newPat[index] = '\0';
		else
			newPat[index++] = pattern[i];
			
	}
	if(q != 5000){	
		if(n<=3){
			if(matchOne(newPat2,line))
			return 1;
		}
		if(matchPatternDots(newPat, line))
			return 1;
	}
	return 0;
}

int escapeChar(char* pattern,char* line){
	int n = strleng(pattern);
	int m = strleng(line);
	int index = 0;
	int matches = 0;
	for(int i = 0; i < m; i++){
		if(line[i] == pattern[index]){
			matches++;
			if(index < n)
				index++;
		}	
	}
	if(matches == n)
		return 1;
	return 0;
}


/*Non special char rgrep; n strleng of pattern, m strleng of line*/
int basicRgrep(char* pattern , char* line, int n, int m){
		int matches = 0;
		int index = firstOccur(line, pattern[0]);
		//If pattern is empty string, prints all lines
		if(n == 0){
			return 1;
		}
		//If pattern is length one char and no special chars.
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

//Finds matches to patterns of one letter
int matchOne(char* pattern,char* line){
	int m = strleng(line);
	for(int i = 0; i < m; i++){
		if(line[i] == pattern[0])
			return 1;
	}
	return 0;
}

//Checks if pattern is all the same
int samePattern(char *pattern){
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

/* Strlen function ignoring \n and \r*/
int strleng(char* string){

	int i = 0;
	while(string[i] != '\0' && string[i] != '\n'&& string[i] != '\r'){
		i++;
	}
	return i;
}


/* Strlen function ignoring \\*/
int strlengIgnoreSlash(char* string){
	int i = 0;
	int count = 0;
	while(string[i] != '\0'){
		i++;
		count++;
		if(string[i] == '\\'){
			count--;
		}
	}
	return count;
}

/*Returns index of first char in string that matches char, returns 5000 if no matches*/
int firstOccur(char * line, char  c){
	int n  = strlengIgnoreSlash(line);
	for(int i = 0; i < n; i++){
			if(i-1 < n && line[i] == c && line[i-1] != '\\')
				return i;	
	}
	return 5000;
}

/*Counts the number of dots and plus's in a pattern*/
int plusDotsCount(char* pattern){
	int i = 0;
	int count = 0;
	while(pattern[i] != '\0'){
		if((pattern[i] == '.' && pattern[i-1] != '\\' )||( pattern[i] == '+' && pattern[i-1] != '\\')){
			count++;
		}
		i++;
	}
	return count;
}

/*Counts the number of slashes in a pattern */
int slashesCount(char* pattern){
	int i = 0;
	int count = 0;
	while(pattern[i] != '\0'){
		if(pattern[i] == '\\'){
			count++;
		}
		i++;
	}
	return count;
	
}

/*Counts question marks in pattern*/
int quesCount(char* pattern){
		int i = 0;
	int count = 0;
	while(pattern[i] != '\0'){
		if(pattern[i] == '?' && pattern[i-1] != '\\'){
			count++;
		}
		i++;
	}
	return count;

}