#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "pwd.h"

image i;
pwd p;
char* filePath;
char* keyWord;
char* storePath;

void inText(char* c){
	scanf("%s", c);

	if(strlen(c) > 50){
		c = realloc(c, (sizeof(char) * strlen(c)) );
	}
}

void start(){
	filePath = malloc(sizeof(char) * 50);
	keyWord = malloc(sizeof(char) * 50);
	storePath = malloc(sizeof(char) * 50);

	printf("------------------------------\n");
	printf("imgPwd by anotherSimpleCoder\n");
	printf("------------------------------\n");
	printf("\n");
	printf("Enter image path: ");
	inText(filePath);
	printf("\n");
	
	printf("Enter keyword: ");
	inText(keyWord);
	printf("\n");

	printf("Enter store path: ");
	inText(storePath);
	printf("\n");
}

void process(){	
	readFile(&i, filePath);
	long* values = getValues(&i);
	char* c = processValues(&i, values);
	
	initPwd(&p, c, keyWord);
	char* res = generate(&p, 20);

	FILE* fp = fopen(storePath, "w");
	fprintf(fp, "%s", res);
	fclose(fp);
}

int main(int argc, char** argv){
	//TODO: Figure out IO

	start();
	process();
	return 0;
}
