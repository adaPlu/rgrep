/*
Test file to test individual functions built for rgrep.
*/

#include<stdio.h>

int strleng(char * string){
	int i = 0;
	while(string[i] != '\0'){
		i++;
	}
	return i;
}
int firstOccur(char * line, char  c){
	int n  = strleng(line);
	for(int i = 0; i < n; i++){
			if(line[i] == c)
				return i;
		
	}
	return 0;
}

int main(void){
char* string = "aa\n";
printf("%d", strleng(string));

}