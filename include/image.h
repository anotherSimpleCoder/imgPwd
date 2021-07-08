#include <png.h>
#include "color.h"
#include "define.h"

struct image{
    unsigned int width;
    unsigned int height;
    png_bytep* pixels;
    color* colorMap;
};

typedef struct image image;

int readFile(image* i,char* filename);
long* getValues(image* i);
char* processValues(image* i, long* values);
long powInt(int b, int e);
long rgbToHex(int r, int g, int b);