#include "gifenc.h"
#include <stdio.h>

void render(char* filename, int width, int height, void (*stepf)(float*, int, int), int (*colorf)(float*, int, int, int), float* grid, uint8_t* palette, int depth, int frames, int step);
