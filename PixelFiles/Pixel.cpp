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
		if (!strcmp(color, "red"))
		{
			return red;
		}
		else if (!strcmp(color, "green"))
		{
			return green;
		}
		else if (!strcmp(color, "blue"))
		{
			return blue;
		}
		else
			throw InputOutOfBoundsException("Invalid color ", color);

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
		file << p.red << " " << p.green << " " << p.blue << " ";
	}
	catch (Pixel::InputOutOfBoundsException& error)
	{
		error.returnError();
		error.returnOffendingIndex();
	}

	return file;
}


/*
Pixel::InputOutOfBoundsException::InputOutOfBoundsException(const char* error, const char* offending)
	: errorMessage(error), offendingIndex(offending) {}


const char* Pixel::InputOutOfBoundsException::returnError() {
	return errorMessage;
}


const char* Pixel::InputOutOfBoundsException::returnOffendingIndex() {
	return offendingIndex;
}


Pixel::Pixel() : red(0), blue(0), green(0) {}
Pixel::Pixel(const Pixel& p) : red(p.red), blue(p.blue), green(p.green) {}


Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b) : red(r), green(g), blue(b) {}


Pixel::~Pixel() {}


const unsigned int& Pixel::operator[](const char* p) {
	if (!strcmp(p, "red")) {
		cout << "Red Value: " << this->red << "." << endl;
		return this->red;
	}
	else if (!strcmp(p, "green")) {
		cout << "Green Value: " << this->green << "." << endl;
		return this->green;
	}
	else if (!strcmp(p, "blue")) {
		cout << "Blue Value: " << this->blue << "." << endl;
		return this->blue;
	}
	else {
		throw InputOutOfBoundsException("Invalid color component", p);
	}
}


ofstream& operator<<(ofstream& os, const Pixel& p) {
	
	os << p.red << p.green << p.blue;
	return os;
}

*/

