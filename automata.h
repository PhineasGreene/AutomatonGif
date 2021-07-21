#include "gifenc.h"

void render(char* filename, int width, int height, void (*stepf)(int*, int, int), int (*colorf)(int), int* grid, uint8_t* palette, int depth, int frames);
