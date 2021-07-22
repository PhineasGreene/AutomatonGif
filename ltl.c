#include <stdlib.h>
#include <math.h>
#include "automata.h"

float getCell(float* grid, int x, int y, int width, int height){
	//if(x >= 0 && x < width && y >= 0 && y < height) return grid[y*width + x];
	int X = x < 0 ? width - x : x;
	int Y = y < 0 ? height - y : y;
	return grid[(Y % height)*width + (X % width)];
}

float stepCell(float n1avg, float n2avg, float cell){
	if(n1avg >= 0 && n1avg <= 33) return 0;
	if(n1avg >= 34 && n1avg <= 45) return 1;
	if(n1avg >= 58 && n1avg <= 121) return 0;
	return cell;
}

void step(float* grid, int width, int height){
	float ngrid[width * height];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			float n1sum = 0;
			float n2sum = 0;
			float cell = getCell(grid, x, y, width, height);

			for(int xoff = -5; xoff <= 5; xoff++){
				for(int yoff = -5; yoff <= 5; yoff++){
					//if(xoff == 0 && yoff == 0) continue;	
					
					/*
					if(abs(xoff) > 3 || abs(yoff) > 3){
						n1sum += getCell(grid, x+xoff, y+yoff, width, height);
					}else{
						n2sum += getCell(grid, x+xoff, y+yoff, width, height);
					}*/
					n1sum += getCell(grid, x+xoff, y+yoff, width, height);
				}
			}

			ngrid[y * width + x] = stepCell(n1sum, 0, cell);
		}
	}

	for(int i = 0; i < width * height; i++){
		grid[i] = ngrid[i];
	}
}

int color(float* grid, int width, int height, int index){
	return floor(grid[index] * 7.999);
}

void main(){
	int w = 400;
	int h = 400;

	uint8_t palette[3*8] =
	{0x00, 0x00, 0x00,
	 0x2F, 0x2F, 0x2F,
	 0x4F, 0x4F, 0x4F,
	 0x6F, 0x6F, 0x6F,
	 0x8F, 0x8F, 0x8F,
	 0xAF, 0xAF, 0xAF,
	 0xCF, 0xCF, 0xCF,
	 0xEF, 0xEF, 0xEF}; // black and white

	float grid[w*h];

	for(int i = 0; i < w*h; i++){
		int x = i % w;
		int y = i / w;

		//if(x > 195 && x < 205 && y > 195 && y < 205) grid[i] = 1;
		//else grid[i] = ((float) random() / RAND_MAX);
		grid[i] = ((float) random() / RAND_MAX);
	}

	render("largerthanlife.gif", w, h, &step, &color, grid, palette, 3, 1000, 10);
}
