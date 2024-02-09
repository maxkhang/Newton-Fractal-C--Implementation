#pragma once

class Complex
{
private:
	double imag;
	double real;

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
	unsigned int maxlter;
	unsigned int rows;
	Pixel determinePixelColor(Complex);
	void makeNewtonFractal();
public:
	~Fractal();
	Fractal();
	Fractal(const Fractal&);
	Fractal(Fractal&&);
	Fractal(unsigned int, unsigned int);
	const Fractal& operator=(const Fractal&);
	Fractal& operator=(Fractal&&);
};