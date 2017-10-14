#include <stdio.h>
#define MAXSIZE 4096

//Funtions
int strleng(char * string);
int patternlen1(char *line, char *pattern);
int firstOccur(char * line, char c);

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
int rgrep_matches(char *line, char *pattern) {
	int n = strleng(pattern);
	//int matches = 0;
	//If pattern is empty string
	if(n == 0)
		printf("%s", line);
	//If pattern is length one char and no special chars.
	else if(n==1){
		if(patternlen1(line, pattern))
			printf("%s", line);
	}
	//If pattern length > 1 and no special chars.
	else if (n > 1){
		int index = firstOccur(line, pattern[0]);
		if(index != 5000){
			/*check for next letter in pattern in line*/
			printf("%s", line);
			return 0;
		}
		else
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

/*Strlen function built for rgrep*/
int strleng(char * string){
	int i = 0;
	while(string[i] != '\0'){
		i++;
	}
	return i;
}

/*Single letter pattern
returns 1 if first char of pattern is in the letter*/
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

/*Returns index of first char in string that matches, returns zero if no matches*/
int firstOccur(char * line, char  c){
	int n  = strleng(line);
	for(int i = 0; i < n; i++){
			if(line[i] == c)
				return i;
		
	}
	return 5000;
}