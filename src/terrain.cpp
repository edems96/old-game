#include "terrain.h"

double Terrain::FindNoise1(int n, int seed) {
	n += seed;
    n = (n << 13) ^ n;
	
    int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
		return 1.0 - ((double)nn / 1073741824.0);
}
 
double Terrain::FindNoise2(double x, double y,int seed) {
	int n = (int)x + (int)y * 57;
    return FindNoise1(n,seed);
}

double Terrain::interpolate(double a, double b, double x) {
	double ft = x * 3.1415927;
    double f = (1.0 - cos(ft)) * 0.5;
    return a * (1.0 - f) + b * f;
}

double Terrain::noise(double x, double y,int seed) {
	double floorx = (double)((int)x);//This is kinda a cheap way to floor a double integer.
    double floory = (double)((int)y);
    double s, t, u, v;//Integer declaration
	
    s = FindNoise2(floorx, floory,seed);
	t = FindNoise2(floorx + 1, floory,seed);
    u = FindNoise2(floorx, floory + 1,seed);//Get the surrounding pixels to calculate the transition.
    v = FindNoise2(floorx + 1, floory + 1,seed);
	double int1 = interpolate(s, t, x - floorx);//Interpolate between the values.
    double int2 = interpolate(u, v, x - floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
 
	return interpolate(int1, int2, y - floory);//Here we use y-floory, to get the 2nd dimension.
 }
       
// Here we get how terrain at X, Y is high. zoomget is only for some testing reasons.
// Here you can edit maximum and minimum level of height.
// Also here you pass seed. It's int.  
       
int Terrain::GetHeight(int x, int y, int seed) {
	double zoomget = 150;
    //x += 30; y -= 30;
    //double p = 0.2 + ((findnoise2(x / 100.0, y / 100.0) + 1.0) / 2) * 0.3;
    double p = 0.5;
     //double zoom = 150;
    double zoom = zoomget;
	double getnoise = 0;
    int octaves = 6;
	
    for (int a = 0; a < octaves - 1; a++) { //This loops trough the octaves.{
		double frequency = pow(2.0, a);//This increases the frequency with every loop of the octave.
        double amplitude = pow(p, a);//This decreases the amplitude with every loop of the octave.
        getnoise += noise(((double)x) * frequency / zoom, ((double)y) / zoom * frequency,seed) * amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
    }
	 
    double maxheight = CHUNK_HEIGHT-16;
    int height = (int)(((getnoise + 1) / 2.0) * (maxheight - 5)) + 3;//(int)((getnoise * 128.0) + 128.0);
	if (height > maxheight - 1) { height = (int)maxheight - 1; }
 
   //if (height > maxheight - 1) { height = maxheight-(height-maxheight); }
 
    if (height < 2) { height = 2; }
		return height;
}
 
 
// Here we get what kind of block it is.
// z is which block we are currently in column.
// height is height of block at this collumn.
 
int Terrain::GetBlock(int z, int height) {
	printf("height(%d): \n", z, height);
	
    if (z > WATER_LEVEL) {
		if (z > height) { return 0; } // air
        if (z == height) { return 3; } // it's probably grass block
        if (z > height - 7) { return 2; } // and it's probably dirt
		
		return 4;// stone?
	} else {
        if ((z > height+5))   { return 5; } // water?
        if ((z > height-5))   { return 1; } // sand?
        if ((z > height-10))  { return 2; } //dirt?
        return 4; // stone?
    }
}
 
void Terrain::Generate(std::vector<Cube>& cubes, Textures textures) {
	int size = 3;
	
	for(int z = 0; z < size; z++) {
		for(int y = 0; y < size; y++) {
			for(int x = 0; x < size; x++) {
				
				int cheight = GetHeight (x, z, 10);
				int t = GetBlock(y, cheight);
				
				if( t != 0 )
					cubes.push_back( Cube(vector3f(x * Cube::SIZE, y * Cube::SIZE, z * Cube::SIZE)).setTexture(t).Generate() );
			}
		}
	}
}
 
