#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "cube.h"
#include "textures.h"

// from : http://pastebin.com/WyfukTgL
class Terrain {
	static const double CHUNK_HEIGHT = 30;
	static const int WATER_LEVEL = 5;
	
	double FindNoise1(int n, int seed);
	double FindNoise2(double x, double y,int seed);
	double interpolate(double a, double b, double x);
	double noise(double x, double y,int seed);
	
	int GetHeight(int x, int y, int seed);
	int GetBlock(int z, int height);
	
	public:
		void Generate(std::vector<Cube>& cubes, Textures texture);
};
#endif