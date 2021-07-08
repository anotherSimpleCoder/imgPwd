#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pwd.h"

int initPwd(pwd* p, char* seed, char* keyword){
    
    if(seed == NULL){
        return INVALID_SEED_PTR;
    }
    
    p->seed = seed;

    if(seed == NULL){
        return INVALID_KEYWORD_PTR;
    }

    p->keyword = keyword;

    return 0;
}

char*  subString(char* src, int a, int b){
    int length = b - a;
    char* res = malloc(sizeof(char) * length);

    for(int i = 0; i < length; i++){
        res[i] = src[a+i];
    }

    return res;
}

char* generate(pwd* p, int acc){
    int size = strlen(p->seed);
    int kSize = strlen(p->keyword);
    char* sub = malloc(sizeof(char) * kSize);
    char* res = malloc(sizeof(char) * (size * kSize));

    for(int i = 0; i < acc; i++){
        int ran = rand() % size;
        sub = subString(p->seed, ran, ran+kSize);
        strcat(res, sub);
    }

    //printf("%s\n", res);

    return res;
}