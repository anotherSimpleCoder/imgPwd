#include "define.h"

struct pwd{
    char* seed;
    char* keyword;
    char* res;
};

typedef struct pwd pwd;

int initPwd(pwd* p, char* seed, char* keywords);
char* subString(char* src, int a, int b);
char* generate(pwd* p, int acc);