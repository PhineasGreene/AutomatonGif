#include "gifenc.h"
#include <stdio.h>

void render(char* filename, int width, int height, void (*stepf)(float*, int, int), int (*colorf)(float*, int, int, int), float* grid, uint8_t* palette, int depth, int frames, int step){
	ge_GIF *gif = ge_new_gif(filename, width, height, palette, depth, 0);

	for(int i = 0; i < frames; i++){
		printf("Rendering frame %d.\n", i);
		
		// create and add frame
		for(int j = 0; j < width*height; j++){
			gif->frame[j] = colorf(grid, width, height, j);
		}
		ge_add_frame(gif, step);

		// step grid
		stepf(grid, width, height);
	}
}
