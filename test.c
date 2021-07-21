#include "automata.h"

void step(int* grid, int width, int height){
	for(int i = 0; i < width * height; i++){
		grid[i] = grid[i] ? 0 : 1;
	}
}

int color(int state){
	return state;
}

void main(){
	int w = 100;
	int h = 100;
	uint8_t palette[6] = {0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF}; // black and white
	int grid[w*h];

	for(int i = 0; i < w*h; i++){
		grid[i] = i % 2;
	}

	render("test.gif", w, h, &step, &color, grid, palette, 1, 2);
}
