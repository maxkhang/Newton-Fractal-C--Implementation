#include "HeaderFile.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//***********************************************//
//  Implementation of the Complex class          //
//***********************************************//
double& Complex::operator[](const char* realOrnot)
{
	try
	{
		if (strcmp(realOrnot, "real")) 
		{
			throw InputOutOfBoundsException("Yooo, it's definitely not real", realOrnot); 
			return real;																	
		}
		else if (strcmp(realOrnot, "imag"))
		{
			throw InputOutOfBoundsException("Yooo, it's definitely not imag", realOrnot);
			return imag;
		}
		return real, imag;
	}
	catch (Complex::InputOutOfBoundsException& error)
	{
		error.returnError();
		error.returnOffendingIndex();
	}
}

Complex::InputOutOfBoundsException::InputOutOfBoundsException(const char* error, const char* index)
{
	errorMessage = error;
	offendingIndex = index;
}

const char* Complex::InputOutOfBoundsException::returnError()
{
	return errorMessage;
}

const char* Complex::InputOutOfBoundsException::returnOffendingIndex()
{
	return offendingIndex;
}
Complex::Complex() : real(1.0), imag(1.0)
{
	cout << "> Complex default constructor called" << endl;
}

Complex::Complex(const Complex& cp)
{
	cout << "> complex copy constructor called" << endl;
	real = cp.real;
	imag = cp.imag;
}

Complex::Complex(double a)
{
	cout << "> complex one-arg constructor called" << endl;
	real = a;
	imag = a;
}

Complex::Complex(double a, double b) : real(a), imag(b)
{
	cout << "> Complex two-arg constructor called" << endl;
}

Complex::~Complex()
{
	cout << "> Complex destructor called";
}

const Complex operator*(const Complex& cp1, const Complex& cp2)
{
	cout << "> Operator * called" << endl;
	Complex temp;
	temp.real = cp1.real * cp2.real - cp1.imag * cp2.imag;
	temp.imag = cp1.real * cp2.imag + cp1.imag * cp2.real;
	return temp;
}

const Complex operator/(const Complex& cp1, const Complex& cp2)
{
	cout << "> Operator / called" << endl;
	Complex temp;
	temp.real = (cp1.real * cp2.real + cp1.imag * cp2.imag) / (cp2.real * cp2.real + cp2.imag * cp2.imag);
	temp.imag = (cp1.imag * cp2.real - cp1.real * cp2.imag) / (cp2.real * cp2.real + cp2.imag * cp2.imag);
	return temp;
}

const Complex operator+(const Complex& cp1, const Complex& cp2)
{
	cout << "> Operator + called" << endl;
	Complex temp;
	temp.real = cp1.real + cp2.real;
	temp.imag = cp2.imag + cp1.imag;
	return temp;
}

const Complex operator-(const Complex& cp1, const Complex& cp2)
{
	cout << "> Operator - called" << endl;
	Complex temp;
	temp.real = cp1.real - cp2.real;
	temp.imag = cp2.imag - cp1.imag;
	return temp;
}

double getMagnitude(const Complex& cp)
{
	cout << "> Get magnitude called" << endl;
	double m = cp.real * cp.real + cp.imag * cp.imag;
	return sqrt(m);
}




//***********************************************//
//  Implementation of the Pixel class            //
//***********************************************//

Pixel::~Pixel()
{
	cout << "> Pixel destructor called" << endl;
}

const unsigned int& Pixel::operator[](const char* color)
{
	cout << "> operator[] called for pixel" << endl;
	try {
		if (strcmp(color, "red"))
		{
			throw InputOutOfBoundsException("It's not red", color);
			return red;
		}
		else if (strcmp(color, "green"))
		{
			throw InputOutOfBoundsException("It's not green", color);
			return green;
		}
		else if (strcmp(color, "blue"))
		{
			throw InputOutOfBoundsException("It's not blue", color);
			return blue;
		}
	}
	catch (InputOutOfBoundsException& error)
	{
		error.returnError();
		error.returnOffendingIndex();
	}
}

Pixel::InputOutOfBoundsException::InputOutOfBoundsException(const char* error, const char* index)
{
	errorMessage = error;
	offendingIndex = index;
}

const char* Pixel::InputOutOfBoundsException::returnError()
{
	return errorMessage;
}

const char* Pixel::InputOutOfBoundsException::returnOffendingIndex()
{
	return offendingIndex;
}

Pixel::Pixel()
{
	red = 0;
	green = 0;
	blue = 0;
	cout << "> Pixel default constructor called" << endl;
}

Pixel::Pixel(const Pixel& p)
{
	cout << "> pixel copy constructor called" << endl;
	red = p.red;
	green = p.green;
	blue = p.blue;
}

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b)
{
	cout << "> pixel three-arg constructor called" << endl;
	red = r;
	green = g;
	blue = b;
}


//***********************************************//
//  Implementation of the Fractal class          //
//***********************************************//

Fractal::~Fractal()
{
	cout << "> Destructor called" << endl;
	for (unsigned int i = 0; i < rows; i++)
	{
		delete[] grid[i];
		grid[i] = nullptr;
	}
	delete[] grid;
	grid = nullptr;
}

Pixel Fractal::determinePixelColor(Complex cp)
{
	double tol = 1E-4, diff = 1.0, test = 0.58974;
	unsigned int iter = 0, color = 0;
	Complex Znew;
	Complex Ztemp;
	while (iter < 512)
	{
		iter++;
		Ztemp["real"] = 1;
		Ztemp["imag"] = 0;
		Znew = cp - ((cp * cp * cp) - ((2.0 * Ztemp["real"]) * cp) + 2.0 * Ztemp["real"]) / ((3.0 * Ztemp["real"] * cp * cp) - 2.0 * Ztemp["real"]);
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

Fractal::Fractal() :maxIter(30), rows(30), cols(30)
{
	cout << "> Default constructor called" << endl;
	grid = new Pixel * [rows];
	for (unsigned int i = 0; i < rows; i++)
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
}

// Move constructor

Fractal::Fractal(Fractal&& f)
{
	cout << "> Move constructor called" << endl;
	grid = f.grid;
	f.grid = nullptr;
	rows = f.rows;
	cols = f.cols;
	maxIter = f.maxIter;
	f.rows = 0;
	f.cols = 0;
	f.maxIter = 30;
}

Fractal::Fractal(unsigned int r, unsigned int c) : maxIter(30)
{
	cout << "> Two-arg constructor called" << endl;
	rows = r;
	cols = c;
	int count = 0;
	grid = new Pixel * [rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
		count++;
		cout << count << endl;
	}

	this->makeNewtonFractal();
}

const Fractal& Fractal::operator=(const Fractal& f)
{
	cout << "> Assignment operator called" << endl;
	if (this != &f)
	{
		if (f.grid != nullptr)
		{
			this->rows = f.rows;
			this->cols = f.cols;
			this->maxIter = f.maxIter;
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
	return (*this);
}

Fractal& Fractal::operator=(Fractal&& f)
{
	cout << "> Move assignment operator called" << endl;
	if (this != &f)
	{
		swap(this->grid, f.grid);
		swap(this->cols, f.cols);
		swap(this->rows, f.rows);
		swap(this->maxIter, f.maxIter);
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


ofstream& operator<<(ofstream& file, const Pixel& p)
{
	try {
		if (p.red > 255 || p.red < 0)
		{
			throw Pixel::InputOutOfBoundsException("Color bounds [0, 255]", "Error appears at red");
		}
		else if (p.green > 255 || p.green < 0)
		{
			throw Pixel::InputOutOfBoundsException("Color bounds [0, 255]", "Error appears at green");
		}
		else if (p.blue > 255 || p.blue < 0)
		{
			throw Pixel::InputOutOfBoundsException("Color bounds [0, 255]", "Error appears at blue");
		}
		file << p.red << p.green << p.blue;
	}
	catch (Pixel::InputOutOfBoundsException& error)
	{
		error.returnError();
		error.returnOffendingIndex();
	}
	
	return file;
}

void saveToPPM(Fractal f, const char* name)
{
	cout << "> Saving Fractal object to PPM file" << endl;
	ofstream dataFile(name, ios::out);
	if (dataFile.fail())
	{
		cout << "Fail opening the file" << endl;
	}
	else
	{
		for (unsigned int i = 0; i < f.rows; i++)
		{
			for (unsigned int j = 0; j < f.cols; j++)
			{
				dataFile << f.grid[i][j];
			}
		}
	}
}
