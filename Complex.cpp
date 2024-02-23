#include "HeaderFile.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
using namespace std;

//***********************************************//
//  Implementation of the Complex class          //
//***********************************************//
double& Complex::operator[](const char* realOrnot)
{
	if (realOrnot == "real")
	{
		real = 0.0;
		return real;
	}
	else if (realOrnot == "imag")
	{
		imag = 0.0;
		return imag;
	}
}

Complex::InputOutOfBoundsException::InputOutOfBoundsException(const char* error, const char* index) : errorMessage(error), offendingIndex(index)
{}

const char* Complex::InputOutOfBoundsException::returnError()
{
	return errorMessage;
}

const char* Complex::InputOutOfBoundsException::returnOffendingIndex()
{
	return offendingIndex;
}

Complex::Complex() : real(0.0), imag(0.0)
{}

Complex::Complex(const Complex& cp)
{
	real = cp.real;
	imag = cp.imag;
}

Complex::Complex(double a)
{
	real = a;
	imag = a;
}

Complex::Complex(double a, double b) : real(a), imag(b)
{}

Complex::~Complex()
{}

const Complex operator*(const Complex& cp1, const Complex& cp2)
{
	Complex temp;
	temp.real = cp1.real * cp2.real - cp1.imag * cp2.imag;
	temp.imag = cp1.real * cp2.imag + cp1.imag * cp2.real;
	return temp;
}

const Complex operator/(const Complex& cp1, const Complex& cp2)
{
	Complex temp;
	temp.real = (cp1.real * cp2.real + cp1.imag * cp2.imag) / (cp2.real * cp2.real + cp2.imag * cp2.imag);
	temp.imag = (cp1.imag * cp2.real - cp1.real * cp2.imag) / (cp2.real * cp2.real + cp2.imag * cp2.imag);
	return temp;
}

const Complex operator+(const Complex& cp1, const Complex& cp2)
{
	Complex temp;
	temp.real = cp1.real + cp2.real;
	temp.imag = cp2.imag + cp1.imag;
	return temp;
}

const Complex operator+(const Complex& cp1, const Complex& cp2)
{
	Complex temp;
	temp.real = cp1.real - cp2.real;
	temp.imag = cp2.imag - cp1.imag;
	return temp;
}

double getMagnitude(const Complex& cp)
{
	double m = cp.real * cp.real + cp.imag * cp.imag;
	return sqrt(m);
}


//***********************************************//
//  Implementation of the Pixel class            //
//***********************************************//

Pixel::~Pixel()
{}

const unsigned int& Pixel::operator[](const char* color)
{
	if (color == "red")
	{
		return red;
	}
	else if (color == "green")
	{
		return green;
	}
	else
		return blue;
}

Pixel::Pixel() : red(0), green(0), blue(0)
{}

Pixel::Pixel(const Pixel& p)
{
	red = p.red;
	green = p.green;
	blue = p.blue;
}

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b)
{
	red = r;
	green = g;
	blue = b;
}
ostream& operator<<(ostream& os, const Pixel& p)
{
	fstream filePPM("file.ppm", ios::out);
	if (filePPM.fail())
	{
		cout << "Fail opening the file" << endl;
	}
	else
		filePPM << p.red << p.green << p.blue;
	return os;
}

//***********************************************//
//  Implementation of the Fractal class          //
//***********************************************//

Fractal::~Fractal()
{
	cout << "> Destructor called" << endl;
	delete[] grid;
	grid = nullptr;
}

Pixel Fractal::determinePixelColor(Complex cp)
{
	double tol = 1E-4, diff = 1.0, test = 0.58974;
	unsigned int iter = 0, color = 0;
	Complex Znew;

	while (iter < 512)
	{
		iter++;
		Znew = cp - ((cp * cp * cp) - (2.0 * cp) + 2.0) / ((3.0 * cp * cp) - 2.0);
		diff = getMagnitude(cp - Znew);
		cp = Znew;
		if (diff < tol)
		{
			color = maxIter - min(iter, maxIter);
			if (abs(cp["imag"]) < tol)
			{
				return Pixel(color, color, 0);
			}
			else if (abs((cp["imag"] - test)) < tol)
			{
				return Pixel(0, color, color);
			}
			else if (abs(cp["imag"] + test) < tol)
			{
				return Pixel(color, 0, color);
			}
		}
	}
	return Pixel(0, 0, 0);
} 

Fractal::Fractal() :maxIter(30)
{
	cout << "> Default constructor called"<<endl;
	grid = new Pixel*[rows];
	for (int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
	}
	this->makeNewtonFractal();
}

Fractal::Fractal(const Fractal& f)
{
	cout << "> Copy constructor called";
	maxIter = f.maxIter;
	rows = f.rows;
	cols = f.cols;
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			grid[i][j] = f.grid[i][j];
		}
	}
	this->makeNewtonFractal();
}

// Move constructor

Fractal::Fractal(Fractal&& f)
{
	cout << "> Move constructor called" << endl;
	grid = f.grid;
	rows = f.rows;
	cols = f.cols;
	grid = new Pixel* [rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
		for (unsigned int j = 0; j < cols; j++)
		{
			grid[i][j] = f.grid[i][j];
		}
	}
	f.grid = nullptr;
	f.rows = 0;
	f.cols = 0;
	this->makeNewtonFractal();
}

Fractal::Fractal(unsigned int r, unsigned int c)
{
	cout << "> Two-arg constructor called" << endl;
	rows = r;
	cols = c;
	grid = new Pixel * [rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
	}
	this->makeNewtonFractal();
}

const Fractal& Fractal::operator=(const Fractal& f)
{
	if (this != &f)
	{
		if (f.grid != nullptr)
		{
			this->rows = f.rows;
			this->cols = f.cols;
			grid = new Pixel * [rows];
			for (unsigned int i = 0; i < rows; i++)
			{
				grid[i] = new Pixel[cols];
				for (unsigned int j = 0; j < cols; j++)
				{
					grid[i][j] = f.grid[i][j];
				}
			}
		}
	}
}

Fractal& Fractal::operator=(Fractal&& f)
{
	cout << "> Move assignment operator called" << endl;
	if (this != &f)
	{
		swap(this->grid, f.grid);
		swap(this->cols, f.cols);
		swap(this->rows, f.rows);
	}
	return (*this);
}

void Fractal::makeNewtonFractal()
{
	cout << "> Now creating the Newton Fractal" << endl;
	Complex Z;
	double step_height = 4.0 / rows;
	double step_width = 4.0 / cols;
	for (unsigned int j = 0; j < rows; j++)
	{
		for (unsigned int k = 0; k < cols; k++)
		{
			Z["imag"] = 2.0 - (j * step_height);
			Z["real"] = (k * step_width) - 2.0;
			grid[j][k] = determinePixelColor(Z);
		}
	}
}

Fractal Fractal::testMoveConstructor(unsigned int rows, unsigned int cols)
{
	Fractal temp;
	temp.rows = rows;
	temp.cols = cols;
	temp.grid = new Pixel*[rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		temp.grid[i] = new Pixel[cols];
	}
	return temp;
}

void saveToPPM(Fractal f, const char* name)
{
	cout << "> Saving Fractal object to PPM file" << endl;
	ofstream dataFile(name, ios::out);
	for (unsigned int i = 0; i < f.rows; i++)
	{
		for (unsigned int j = 0; j < f.cols; j++)
		{
			dataFile << f.grid[i][j];
		}
	}
}


