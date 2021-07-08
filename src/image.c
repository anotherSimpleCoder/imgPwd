#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

//unsigned int width;
//unsigned int height;
//png_bytep* pixels;

int readFile(image* i, char* filename){
	FILE* fp = fopen(filename, "rb");
	png_byte bit_depth;
	png_byte color_type;
	unsigned int y;

	if(!fp)
		return INVALID_FILE_PTR;

	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if(!png)
		return INVALID_PNG_PTR;

	png_infop info = png_create_info_struct(png);

	if(!info)
		return INVALID_INFO_PTR;

	if(setjmp(png_jmpbuf(png)))
		return 1;

	png_init_io(png, fp);
	png_read_info(png, info);
	i->width = png_get_image_width(png, info);
	i->height = png_get_image_height(png, info);
	color_type = png_get_color_type(png, info);
	bit_depth = png_get_bit_depth(png, info);
	
	if(bit_depth == 16)
		png_set_strip_16(png);
	
	if(color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);
	
	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	if(png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	if(color_type == PNG_COLOR_TYPE_RGB ||
		color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xff, PNG_FILLER_AFTER);

	if(color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	png_read_update_info(png, info);
	i->pixels = (png_bytep*)malloc(sizeof(png_bytep) * i->height);
	
	for(y = 0; y < i->height; y++){
		i->pixels[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
	}
	png_read_image(png, i->pixels);
	fclose(fp);
	return 0;
}

long* getValues(image* i){
	i->colorMap = malloc(sizeof(color) * (i->height*i->width));
	long* hexValues = malloc(sizeof(long) * (i->height * i->width));

	for(unsigned int y = 0; y < i->height; y++){
		png_bytep row = i->pixels[y];
		
		for(unsigned int x = 0; x < i->width; x++){
			color c;
			png_bytep px = &(row[x * 4]);

			c.r = px[0];
			c.g = px[1];
			c.b = px[2];
			c.a = px[3];

			i->colorMap[x*y] = c;
		}
	}
	
	for(int y = 0; y < i->height; y++){
			for(int x = 0; x < i->width; x++){
				color* c = &(i->colorMap[x*y]);
				long hex = rgbToHex(c->r, c->g, c->b);
				hexValues[x*y] = hex;
				//printf("(%d ,%d) = (%3d, %3d, %3d, %3d)\n", x, y, c->r, c->g, c->b, c->a);
				//printf("(%d, %d) = 0x%X \n", x, y, rgbToHex(c->r, c->g, c->b));
			}
	}


	return hexValues;
}

char* processValues(image* i, long* values){
	int size = i->width * i->height;
	char* res = malloc(sizeof(char) * (30 * size));

	for(int j = 0; j < size; j++){
		char snp[30];
		sprintf(snp, "%lX", values[j]);
		strcat(res, snp);
	}
	//printf("%s\n", res);

	return res;
}

int terminate(image* i){
	free(i->pixels);
	free(i->colorMap);
	free(i);
}

long powInt(int b, int e){
	long res = 1;
	
	for(int i = 0; i < e; i++){
		res = res * b;
	}

	return res;
}

long rgbToHex(int r, int g, int b){
	int arr[3];

	arr[0] = b;
	arr[1] = g;
	arr[2] = r;

	long res = 0;

	for(int i = 2; i >= 0; i--){
		res = res*10 + (arr[i] * powInt(2, 8* i));
	}

	return res;
}