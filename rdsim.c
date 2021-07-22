#include "automata.h"

#define D_a 1
#define D_b 0.5
#define f 0.055
#define k 0.062

//float

void step(float* grid, int width, int height){
	int ngrid[width * height * 2];

	for(int ai = 0; ai < width * height; ai++){
		int bi = ai + width * height;

	}
}

int color(float* grid, int width, int height, int index){
	return grid[index];
}

void main(){
	int w = 100;
	int h = 100;
	uint8_t palette[6] = {0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF}; // black and white
	float grid[w*h];

	for(int i = 0; i < w*h; i++){
		grid[i] = i % 2;
	}

	render("test.gif", w, h, &step, &color, grid, palette, 1, 2);
}
