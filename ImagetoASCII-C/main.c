#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct that holds the RBG and luminosity values for a pixel
typedef struct{
	int r;
	int g;
	int b;
	float lum;
}Pixel;

//given an array of pixels, the number of pixels, and the width of the image, prints the ASCII art
//the character that represents each pixel is determined by that pixel's luminosity
void print_ASCII(Pixel* pixels, int numPixels, int width){
	for(int i = 0; i < numPixels; i++){
                float luminosity = pixels[i].lum;
                if(i % width == 0){ //prints a new line for each row of pixels
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
}
int main(int argc, char** argv){
	//the header of ppm files contain information about dimensions and format
	FILE* file = fopen(argv[1], "rb"); //open ppm file
	char type[3]; //type (ex. p3, p6)
	int width;
	int height;
	int max_rgb;
	fgets(type, 3, file);
	if(strcmp(type, "P6") != 0){ //only supports P6 format
		printf("Invalid file format. Expected P6 type ppm. File type: %s\n", type);
		exit(0);
	}
	fscanf(file, "%d %d %d", &width, &height, &max_rgb); //get values from header
	long int size = width * height * 3; //size of all the rbg values 
	long int numPixels = width * height; //number of pixels
	unsigned char* data = malloc(sizeof(char) * size); //to store rgb vals
	fread(data, sizeof(unsigned char), size, file); //get data
		
	Pixel* pixels = malloc(numPixels * sizeof(Pixel)); //to store pixels
	//convert rgb values to pixels
	for(int i = 0; i < size; i += 3){ 
		Pixel* cur = &pixels[i/3];
		cur->r = data[i];
		cur->g = data[i + 1];
		cur->b = data[i + 2];
		//the overall "brightness" of the pixel
		cur->lum = (0.2126 * cur->r) + (0.7152 * cur->g) + (0.0722 * cur->b);
	}
	//print the characters
	print_ASCII(pixels, numPixels, width);
	//free mallocs and close file to prevent memory leaks
	free(pixels);
	free(data);
	fclose(file);
}
