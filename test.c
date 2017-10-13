/*
Test file to test strlen and other functions built for rgrep.
*/

#include<stdio.h>

int strleng(char * string){
	int i = 0;
	while(string[i] != '\0'){
		i++;
	}
	return i;
}

int main(void){
char* string = "123456789";
printf("%d", strleng(string));

}