#pragma once
#include "Complex.hpp"
#include "Pixel.hpp"
#include <iostream>

using namespace std;

class Fractal
{
private:
	unsigned int rows;
	unsigned int cols;
	unsigned int maxIter;
	Pixel** grid;
	Pixel determinePixelColor(Complex);
	void makeNewtonFractal();
public:

	~Fractal();
	Fractal();
	Fractal(const Fractal&);
	Fractal(Fractal&&);
	Fractal(unsigned int, unsigned int);
	const Fractal& operator=(const Fractal&);
	Fractal& operator= (Fractal&&);
	friend void saveToPPM(Fractal, const char*);

};