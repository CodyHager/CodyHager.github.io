#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int r;
	int g;
	int b;
	float lum;
}Pixel;
int main(int argc, char** argv){
	FILE* file = fopen(argv[1], "r");
	char type[3];
	int width;
	int height;
	int max_rgb;
	fgets(type, 3, file);
	fscanf(file, "%d %d %d", &width, &height, &max_rgb);
	//printf("%s %d %d %d\n", type, width, height, max_rgb);
	long int size = width * height * 3;
	unsigned char* data = malloc(sizeof(char) * size);
	fread(data, sizeof(unsigned char), size, file);
	
//	for(int i = 0; i < size; i++){
//		if(i % 3 == 0){
//			printf("\n");
//		}
//		printf("%d ", data[i]);
//	}
	
	Pixel pixels[height * width];
	for(int i = 0; i < size; i += 3){
		Pixel* cur = &pixels[i/3];
		cur->r = data[i];
		cur->g = data[i + 1];
		cur->b = data[i + 2];
		cur->lum = (0.2126 * cur->r) + (0.7152 * cur->g) + (0.0722 * cur->b);
	}
	for(int i = 0; i < (height * width); i++){
		//printf("%d) %d %d %d\n", i, pixels[i].r, pixels[i].g, pixels[i].b);
		float luminosity = pixels[i].lum;
		if(i % width == 0){
			printf("\n");
		}	
		if(luminosity < 25){
			printf(" ");
		}
		else if(luminosity >= 25 && luminosity < 50){
			printf(".");
		}
		else if(luminosity >= 50 && luminosity < 75){
			printf(":");
		}
		else if(luminosity >= 75 && luminosity < 100){
			printf("-");
		}
		else if(luminosity >= 100 && luminosity < 125){
			printf("=");
		}
		else if(luminosity >= 125 && luminosity < 150){
			printf("+");
		}
		else if(luminosity >= 150 && luminosity < 175){
			printf("*");
		}
		else if(luminosity >= 175 && luminosity < 200){
			printf("#");
		}
		else if(luminosity >= 200 && luminosity < 225){
			printf("%%");
		}
		else if(luminosity >= 225){
			printf("@");
		}
		else{
			printf("ERROR");
		}
	}
	free(data);
	fclose(file);
}
