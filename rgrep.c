#include <stdio.h>
#define MAXSIZE 4096

//Funtions
int strleng(char* string);
int firstOccur(char* line, char c);
int secondOccur(char* line, char c);
int checkSpecial(char* pattern);
int sameChar(char* pattern);
int afterPlus(char* pattern, char* line);
int matchPatternDots(char* pattern,char* line);
int patternPlus(char* pattern,char* line);
int morePlus(char* pattern,char* line);
int basic(char* pattern,char* line, int n, int m);
int quesMark(char * pattern, char* line);
int escapeChar(char* pattern,char* line);
int matchOne(char* pattern,char* line);
int strlengn(char* string);
int dotSlashn(char* pattern,char* line);
char *zstring_remove_chr(char *str,const char *bad);
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
	//zstring_remove_chr(line,"\n");
	printf("%s", line);
	return 0;
	if(checkSpecial(pattern) != 5000){
		switch(pattern[checkSpecial(pattern)]) {
		case '.' :
			if(sameChar(pattern)){
				if(m == n)
					return 1;	
				else
					return 0;
			}
			//printf("%d", firstOccur(line, '\n'));
			else if(firstOccur(line, '\n') != 5000 && firstOccur(line, '\n') < n){
				//printf("\\n");
				if (dotSlashn(pattern, line)){
					return 1;
				}
				return 0;
			}
			else if(firstOccur(pattern, '+') != 5000){
				//printf("Plus");
				if (afterPlus(pattern, line)){
					//printf("Plus");
					return 1;
				}
				return 0;
			}
			else if (matchPatternDots(pattern, line)){
				//printf("match");
				return 1;
			}
			else
				return 0;
		case '\\' :
				if(escapeChar(pattern, line))
					return 1;
				else
					return 0;
		case '+' :
			if(n==1)
				return 1;
			if(morePlus(pattern, line))
				return 1;
			if(patternPlus(pattern, line))
				return 1;
			return 0;
		case '?' :
			if(quesMark(pattern, line))
				return 1;
			else
				return 0;
		default :
			return 0;
		}

	}
	else{
		if(basic(line , pattern, n, m))
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

int patternPlus(char* pattern,char* line){
 	int n = strleng(pattern);
 	int m = strleng(line);
	//int firstFound[m];
 	int p = firstOccur(pattern, '+');
 	int matches = 0;
	int found = 0;
	//int index = 0;
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
		//char p1 = pattern[p-1];
		for(int i = 0; i< m; i++){
			if(line[i] == pattern[0]){
				//firstFound[index++] = i;
				matches = 1;
			}
		}
		//index = 0;
		for(int i = 1; i< n; i++){
			if(line[i] == pattern[i]){
				matches++;
			}
		}
		
		if(p < n){
			char p2 = pattern[p+1];
			for(int i = p+1; i< n && i < m; i++){
				//printf("p2: %d\n", line[firstOccur(line, p2)] == pattern[i]);
				if(line[firstOccur(line, p2)] == pattern[i]){
					//printf("p: %d,n: %d, line: %s\n", p,n,  line);
					matches++;
					//printf("matches: %d,n: %d, line: %s\n", matches,n,  line);
				}
			}
		}
		//printf("matches: %d,n: %d, line: %s\n", matches,n,  line);
		if(matches == n-1 || matches == n)
			return 1;
	
	}
 	return 0;
 }
 
 
//Checks for matchs to dot-pattern
int matchPatternDots(char* pattern,char* line){
	int n = strleng(pattern);
	int m = strleng(line);
	int index = 0;
	int matches = 0;
	for(int i = 0; i< m; i++){
		
		/*
		while(pattern[index] == '.'){
			index++;
			matches++;
			printf("matches: %d", matches);
		}
		*/
		//printf("matches: %d", matches);
		if((pattern[index] != '\0' && pattern[index] == line[i]) || pattern[index] == '.'){
				matches++;
				index++;
				
		}
		//printf("line[i]: %c\n",line[i]);
		if(line[i]=='\n'){
			matches =0;
			printf("matches: %d,n: %d, line: %s\n", matches, n,  line);
		}
		//printf("matches: %d,n: %d, line: %s\n", matches, n,  line);
		if(matches == n)
			return 1;
	}
	return 0;
	
}


//Checks for matches after +
int afterPlus(char* pattern, char* line){
	int n = strlengn(pattern);
	int m = strleng(line);
	int matches= 0;
	int i = 0;
	//printf("%d,%d, %s\n", m,n, line);
	for(int j = 0; j < m; j++){
		//printf("line[i]: %c, pattern[i]:%c\n", line[i], pattern[i]);
		if(pattern[i] == '\\'){
			if(i+2 < m && pattern[i+1] == 'n'){
				i = i+2;
		}}
		
		if((i+1 > m && pattern[i] == line[j]) || (pattern[i] == '+' && pattern[i+1] != '\\')|| (pattern[i] == '.'&& pattern[i+1] != '\\')){
			matches++;
			//printf("matches: %d, %c\n", matches, pattern[i]);
			if (i != n){
				i++;
		
			}
		}
		else if(pattern[i] == line[j] || pattern[i] == '+'|| pattern[i] == '.'){
			matches++;
			 //printf("matches: %d, %c\n", matches, pattern[i]);
			if(line[i] == '\n'){
				line[i] = '\0';
				//printf("line: %s, %c\n", line, pattern[i]);
			}
			else if (i != n){
				i++;
		
			}
		}
	}
	
	//printf("matches: %d,n: %d,%d, line: %s\n", matches ,n, m,  line);
	if(matches == n- 1||  matches == n){
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

/* Strlen function ignoring \n and \r*/
int strleng(char* string){

	int i = 0;
	while(string[i] != '\0' && string[i] != '\n'&& string[i] != '\r'){
		i++;
	}
	return i;

}

/* Strlen function*/
int strlengp(char* string){

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
/* Strlen function ignoring \\*/
int strlengn(char* string){

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
	int n  = strlengp(line);
	for(int i = 0; i < n; i++){
			if(i-1 < n && line[i] == c && line[i-1] != '\\')
				return i;
		
	}
	return 5000;
}

/*Returns index of second char in string that matches char , returns 5000 if no matches*/
int secondOccur(char* line, char c){
	int n  = strleng(line);
	int matches = 0;
	for(int i = 0; i < n; i++){
			if(line[i] == c)
				matches++;
			if(matches == 2)
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
	

	//checks for '\\'
	for(int i = 0; i < n; i++){
		if(pattern[i] == '\\'){
			if(i != 0 && pattern[i-1] != 92){
				return i;
				
			}
			else
				return i;
		} 
	}
			
	return 5000;
}
//Checks for and deals with multiple plus
int morePlus(char* pattern,char* line){
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
	//printf("%c,%c, %c\n", beforePlus[0], beforePlus[1], beforePlus[2]);
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

		//printf("matches %d, plus: %d,, line: %s\n", matches, plus,  line);		
		if(matches >= plus)
			return 1;					
		
		
	}
	return 0;
}

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
	//printf("%d\n", n);
	for(int i = 0; i < n; i++){
		if(i== n-1){
			newPat2[index2] = '\0';
		}
		if(pattern[i] != '?' && pattern[i+1] != '?')
			newPat2[index2++] = pattern[i];
		
		if(i == n){
			newPat[index] = '\0';
			//printf("n== 2 ,%s\n", newPat);
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

	//printf("%s, %s\n, %s", newPat2, newPat, line);
	if(q != 5000){
		//printf("%s, %s, %d\n", newPat2, line, basic(line, newPat2, n, m) );
		//printf("%d, %s, %s \n", matchOne(newPat2,line), newPat2, line);
		
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
	//printf("matches: %d,n: %d, line: %s\n", matches,n, line);
	if(matches == n)
		return 1;
	return 0;
}

//Finds matches to patterns of one letter
int matchOne(char* pattern,char* line){
	int m = strleng(line);
	for(int i = 0; i < m; i++){
		//printf("%s", pattern);
		if(line[i] == pattern[0])
			return 1;
	}
	return 0;
}

/*Non special char rgrep; n strleng of pattern, m strleng of line*/
int basic(char* line , char* pattern, int n, int m){
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
							//printf("matches: %d,n: %d, line: %s\n", matches,n, line);
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


int dotSlashn(char* pattern,char* line){
	int n = strlengp(line);
	//int m = strleng(pattern);
	int index = 0;
	int matches = 0;
	int num = 0;
	//printf("%s\n", line);
	for(int i = 0; i < n; i++){
		
			//printf("%d, %d\n", n, num);
		if(line[index] == '\n'){
			index++;
			num++;
			//printf("%d\n", num);
		}
		if(line[i] == pattern[index]){
			matches++;
			index++;
		}
		else if(pattern[index] == '.'){
				index++;
		}
	}
	//printf("matches: %d,n-num: %d, line: %s\n", matches,n-num, line);
	if(matches == n- num)
		return 1;
	
	return 0;
}
int zstring_search_chr(const char *token,char s){
    if (!token || s=='\0')
        return 0;

    for (;*token; token++)
        if (*token == s)
            return 1;

    return 0;
}

char *zstring_remove_chr(char *str,const char *bad) {
    char *src = str , *dst = str;
    while(*src)
        if(zstring_search_chr(bad,*src))
            src++;
        else
            *dst++ = *src++;  /* assign first, then incement */

    *dst='\0';
        return str;
}