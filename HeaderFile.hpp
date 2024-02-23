#pragma once
#include <iostream>
using namespace std;

class Complex
{
private:
	double real, imag;
public:
	~Complex();
	Complex();
	Complex(const Complex&);
	Complex(double);
	Complex(double, double);
	double& operator[](const char*);
	class InputOutOfBoundsException
	{
	private:
		const char* errorMessage;
		const char*	offendingIndex;
	public:
		InputOutOfBoundsException(const char*, const char*);
		const char* returnError();
		const char* returnOffendingIndex();
	};
	friend const Complex operator*(const Complex&, const Complex&);
	friend const Complex operator/(const Complex&, const Complex&);
	friend const Complex operator+(const Complex&, const Complex&);
	friend const Complex operator-(const Complex&, const Complex&);
	friend double getMagnitude(const Complex&);
};

class Pixel
{
private:
	unsigned int blue, green, red;
public:
	~Pixel();
	const unsigned int& operator[](const char*);
	Pixel();
	Pixel(const Pixel&);
	Pixel(unsigned int, unsigned int, unsigned int);
	
	friend ostream& operator<<(ostream& os, const Pixel&);

	class InputOutOfBoundsException
	{
	private:
		const char* errorMessage;
		const char* offendingIndex;
	public:
		InputOutOfBoundsException(const char*, const char*);
		const char* returnError();
		const char* returnOffendingIndex();
	};
};

class Fractal
{
private:
	unsigned int cols;
	Pixel** grid;
	unsigned int maxIter;
	unsigned int rows;
	Pixel determinePixelColor(Complex);
	void makeNewtonFractal();
public:
	~Fractal();
	
	Fractal();
	Fractal(const Fractal&);
	Fractal(Fractal&&);
	Fractal(unsigned int, unsigned int);
	Fractal testMoveConstructor(unsigned int rows, unsigned int cols);
	const Fractal& operator=(const Fractal&);
	Fractal& operator= (Fractal&&);
	friend void saveToPPM(Fractal, const char*);
};

