#include <stdlib.h>
#include <math.h>
#include "automata.h"

#define n1len 108
#define n2len 36

int n1offsx[n1len];
int n1offsy[n1len];
int n2offsx[n2len];
int n2offsy[n2len];

float getCell(float* grid, int x, int y, int width, int height){
	//if(x >= 0 && x < width && y >= 0 && y < height) return grid[y*width + x];
	int X = x < 0 ? width - x : x;
	int Y = y < 0 ? height - y : y;
	return grid[(Y % height)*width + (X % width)];
}

float stepCell(float n1avg, float n2avg, float cell){
	if( n1avg >= 0.210 
	&&  n1avg <= 0.220 ) { return 1.0; }
	if( n1avg >= 0.350 
	&&  n1avg <= 0.500 ) { return 0.0; }
	if( n1avg >= 0.750 
	&&  n1avg <= 0.850 ) { return 0.0; }
	if( n2avg >= 0.100 
	&&  n2avg <= 0.280 ) { return 0.0; }
	if( n2avg >= 0.430 
	&&  n2avg <= 0.550 ) { return 1.0; }
	if( n1avg >= 0.120 
	&&  n1avg <= 0.150 ) { return 0.0; }
	return cell;
}

void initOffsets(){
	int n1i = 0;
	int n2i = 0;

	for(int xoff = -7; xoff <= 7; xoff++){
		for(int yoff = -7; yoff <= 7; yoff++){
			if(xoff == 0 && yoff == 0) continue;	

			int d = xoff * xoff + yoff * yoff;
			
			if(d >= 25 && d <= 53){
				n1offsx[n1i] = xoff;
				n1offsy[n1i] = yoff;
				n1i++;
			}else if(d <= 10){
				n2offsy[n2i] = xoff;
				n2offsx[n2i]	= yoff;
				n2i++;
			}
		}
	}
}

void step(float* grid, int width, int height){
	float ngrid[width * height];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			float n1sum = 0;
			float n2sum = 0;
			float cell = getCell(grid, x, y, width, height);

			for(int i = 0; i < n1len; i++){
				n1sum += getCell(grid, x + n1offsx[i], y + n1offsy[i], width, height);
			}
			for(int i = 0; i < n2len; i++){
				n2sum += getCell(grid, x + n2offsx[i], y + n2offsy[i], width, height);
			}

			ngrid[y * width + x] = stepCell(n1sum*0.0092592, n2sum*0.0270270, cell);
		}
	}

	for(int i = 0; i < width * height; i++){
		grid[i] = ngrid[i];
	}
}

int color(float* grid, int width, int height, int index){
	float sum = 0;
	for(int x = -1; x <= 1; x++){
		for(int y = -1; y <= 1; y++){
			int cx = index % width;
			int cy = index / width;
			sum += getCell(grid, cx + x, cy + y, width, height);
		}
	}
	sum *= 0.11111;

	return floor( sum * 7.9999);
}

void main(){
	initOffsets();

	int w = 600;
	int h = 400;

	uint8_t palette[3*8] =
	{0x00, 0x00, 0x00,
	0x00, 0x00, 0x20,
	0x00, 0x00, 0x40,
	0x00, 0x00, 0x60,
	0x00, 0x00, 0x80,
	0x00, 0x00, 0xA0,
	0x00, 0x00, 0xC0}; // black and white

	float grid[w*h];

	for(int i = 0; i < w*h; i++){
		int x = i % w;
		int y = i / w;

		//if(x > 190 && x < 210 && y > 190 && y < 210) grid[i] = 1;
		//else grid[i] = 0;
		grid[i] = ((float) random() / RAND_MAX);
	}

	render("test.gif", w, h, &step, &color, grid, palette, 3, 1000, 7);
}
