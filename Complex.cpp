#include "Complex.hpp"
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
			return real;
			throw InputOutOfBoundsException("Yooo, it's definitely not real", realOrnot); 
																				
		}
		else if (strcmp(realOrnot, "imag"))
		{
			return imag;
			throw InputOutOfBoundsException("Yooo, it's definitely not imag", realOrnot);
		}
		
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
Complex::Complex()
{
	//cout << "> Complex default constructor called" << endl;
	this->real = 0.0;
	this->imag = 0.0;
}

Complex::Complex(const Complex& cp)
 {
	//cout << "> complex copy constructor called" << endl;
	this->real = cp.real;
	this->imag = cp.imag;
}

Complex::Complex(double a)
{
	//cout << "> complex one-arg constructor called" << endl;
	this->real = a;
	this->imag = a;
}

Complex::Complex(double a, double b) 
{
	//cout << "> Complex two-arg constructor called" << endl;
	this->real = a;
	this->imag = b;
}

Complex::~Complex()
{
	//cout << "> Complex destructor called";
}

const Complex operator*(const Complex& cp1, const Complex& cp2)
{
	//cout << "> Operator * called" << endl;
	Complex temp;
	temp.real = (cp1.real * cp2.real - cp1.imag * cp2.imag);
	temp.imag = (cp1.real * cp2.imag + cp1.imag * cp2.real);
	return temp;
	/*
	temp.real = cp1.real * cp2.real - cp1.imag * cp2.imag;
	temp.imag = cp1.real * cp2.imag + cp1.imag * cp2.real;
	*/
}

const Complex operator/(const Complex& cp1, const Complex& cp2)
{
	//cout << "> Operator / called" << endl;
	Complex temp;
	temp.real = (cp1.real * cp2.real + cp1.imag * cp2.imag) / (cp2.real * cp2.real + cp2.imag * cp2.imag);
	temp.imag = (cp1.imag * cp2.real - cp1.real * cp2.imag) / (cp2.real * cp2.real + cp2.imag * cp2.imag);
	return temp;
	/*
	temp.real = (cp1.real * cp2.real + cp1.imag * cp2.imag) / (cp2.real * cp2.real + cp2.imag * cp2.imag);
	temp.imag = (cp1.imag * cp2.real - cp1.real * cp2.imag) / (cp2.real * cp2.real + cp2.imag * cp2.imag);
	*/
}

const Complex operator+(const Complex& cp1, const Complex& cp2)
{
	//cout << "> Operator + called" << endl;
	Complex temp;
	temp.real = cp1.real + cp2.real;
	temp.imag = cp1.imag + cp2.imag;
	return temp;
	/*
	temp.real = cp1.real + cp2.real;
	temp.imag = cp2.imag + cp1.imag;
	*/
}

const Complex operator-(const Complex& cp1, const Complex& cp2)
{
	//cout << "> Operator - called" << endl;
	Complex temp;
	temp.real = cp1.real - cp2.real;
	temp.imag = cp2.imag - cp1.imag;
	return temp;
}

double getMagnitude(const Complex& cp)
{
	//cout << "> Get magnitude called" << endl;
	double m = cp.real * cp.real + cp.imag * cp.imag;
	return sqrt(m);
}

/*
Complex& Complex::operator=(const Complex& cp)
{
	this->real = cp.real;
	this->imag = cp.imag;
	return (*this);
}
*/

//***********************************************//
//  Implementation of the Pixel class            //
//***********************************************//




//***********************************************//
//  Implementation of the Fractal class          //
//***********************************************//


