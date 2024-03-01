#include "Pixel.hpp"
#include <iostream>
#include <fstream>
using namespace std;

Pixel::~Pixel()
{
	//cout << "> Pixel destructor called" << endl;
}

const unsigned int& Pixel::operator[](const char* color)
{
	//cout << "> operator[] called for pixel" << endl;
	try {
		if (strcmp(color, "red"))
		{
			return red;
			throw InputOutOfBoundsException("It's not red", color);
			
		}
		else if (strcmp(color, "green"))
		{
			return green;
			throw InputOutOfBoundsException("It's not green", color);
			
		}
		else if (strcmp(color, "blue"))
		{
			return blue;
			throw InputOutOfBoundsException("It's not blue", color);
			
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
	red = 0U;
	green = 0U;
	blue = 0U;
	//cout << "> Pixel default constructor called" << endl;
}

Pixel::Pixel(const Pixel& p)
{
	//cout << "> pixel copy constructor called" << endl;
	red = p.red;
	green = p.green;
	blue = p.blue;
}

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b)
{
	//cout << "> pixel three-arg constructor called" << endl;
	red = r;
	green = g;
	blue = b;
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