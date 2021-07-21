#include "gifenc.h"

void render(char* filename, int width, int height, void (*stepf)(int*, int, int), int (*colorf)(int), int* grid, uint8_t* palette, int depth, int frames){
	ge_GIF *gif = ge_new_gif(filename, width, height, palette, depth, 0);

	for(int i = 0; i < frames; i++){
		// create and add frame
		for(int j = 0; j < width*height; j++){
			gif->frame[j] = colorf(grid[j]);
		}
		ge_add_frame(gif, 10);

		// step grid
		stepf(grid, width, height);
	}
}
