#include "Fractal.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Fractal::~Fractal()
{
	cout << "> Destructor called" << endl;
	if(grid!=nullptr)
	{
		for (unsigned int i = 0; i < rows; i++)
		{
			delete[] grid[i];
			grid[i] = nullptr;
		}
		delete[] grid;
		grid = nullptr;
	}
}



Fractal::Fractal() :maxIter(30), rows(2), cols(2)
{
	cout << "> Default constructor called" << endl;
	grid = nullptr;
}

Fractal::Fractal(const Fractal& f)
{
	cout << "> Copy constructor called"<<endl;
	maxIter = 30;
	rows = f.rows;
	cols = f.cols;
	grid = new Pixel*[rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
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
	maxIter = f.maxIter;
	grid = f.grid;
	f.grid = nullptr;
	rows = f.rows;
	cols = f.cols;
	//maxIter = f.maxIter;
	f.rows = 0;
	f.cols = 0;
	f.maxIter = 30;
}

// Move assignment operator
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
		//count++;
		//cout << count << endl;
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

Pixel Fractal::determinePixelColor(Complex cp)
{
	double tol = 1E-4, diff = 1.0, test = 0.58974;
	//cout << "This is tol: " << tol << endl;
	unsigned int iter = 0, color = 0;
	Complex Znew;

	while (iter < 512)
	{
		iter++;
		Znew = cp - ((cp * cp * cp) - (2.0 * cp) + 2) / ((3.0 * cp * cp) - 2.0);
		diff = getMagnitude(cp - Znew);
		cp = Znew;
		//cout << cp.real << " + (" << cp.imag << "i)" << endl;
		//cout <<  diff << endl;

		/*Znew = cp - ((cp * cp * cp) - ((2.0 * cp) + 2.0)) / ((3.0 * cp * cp) - 2.0);
		diff = getMagnitude(cp - Znew);
		cout << diff << endl;
		cout << getMagnitude(cp - ((cp * cp * cp) - ((2.0 * cp) + 2.0)))<<endl;
		cp = Znew;
		*/
		//cout << "Diff: "<< diff << endl;
		if (diff < tol)
		{
			color = maxIter - min(iter, maxIter);
			if (abs(cp.imag) < tol)
			{
				//	cout << "color first: " << color;
				return Pixel(color, color, 0);
			}
			else if (abs((cp.imag - test)) < tol)
			{
				//cout << "color second: " << color;
				return Pixel(0, color, color);
			}
			else if (abs(cp.imag + test) < tol)
			{
				//	cout << "color third: " << color;
				return Pixel(color, 0, color);
			}
		}
	}
	return Pixel(0, 0, 0);
}


void saveToPPM(const Fractal& f, const char* name)
{
	cout << "> Saving Fractal object to PPM file" << endl;
	ofstream dataFile(name, ios::out);
	if (!dataFile.is_open())
	{
		cout << "Fail opening the file" << endl;
	}
	else
	{
		dataFile << "P3" << endl << "# The Newton's Fractal" << endl << f.rows << " " << f.cols << endl << 255 << endl;
		for (unsigned int i = 0; i < f.rows; i++)
		{
			for (unsigned int j = 0; j < f.cols; j++)
			{
				dataFile << f.grid[i][j];
			}
			dataFile << endl;
		}
	}
}
