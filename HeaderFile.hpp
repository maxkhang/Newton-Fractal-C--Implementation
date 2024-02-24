#pragma once
#include <iostream>
using namespace std;

class Complex
{
private:
	double real;
	double imag;
public:
	~Complex();
	Complex();
	Complex(const Complex&);
	Complex(double);
	Complex(double, double);
	double& operator[](const char*);
	friend const Complex operator*(const Complex&, const Complex&);
	friend const Complex operator/(const Complex&, const Complex&);
	friend const Complex operator+(const Complex&, const Complex&);
	friend const Complex operator-(const Complex&, const Complex&);
	friend double getMagnitude(const Complex&);
};

class Pixel
{
private:
	unsigned int blue;
	unsigned int green;
	unsigned int red;
public:
	~Pixel();
	const unsigned int& operator[](const char*);
	Pixel();
	Pixel(const Pixel&);
	Pixel(unsigned int, unsigned int, unsigned int);

	friend fstream& operator<<(fstream& file, const Pixel&);

};

class Fractal
{
private:
	unsigned int rows;
	unsigned int cols;
	unsigned int maxIter;
	Pixel** grid;
	Pixel determinePixelColor(Complex);
	
public:
	void makeNewtonFractal();
	~Fractal();
	Fractal();
	Fractal(const Fractal&);
	Fractal(Fractal&&);
	Fractal(unsigned int, unsigned int);
	const Fractal& operator=(const Fractal&);
	Fractal& operator= (Fractal&&);
	friend void saveToPPM(Fractal, const char*);

};
