#include "Complex.hpp"
#include "Pixel.hpp"
#include "Fractal.hpp"
#include <iostream>


Fractal testMoveConstructor(unsigned int row, unsigned int col)
{
	return Fractal(row, col);
}

int main()
{
	Fractal m1(20U, 20U), m2, m3;
	saveToPPM(m1, "newton1.ppm");
	/*Complex a(6, 5);
	Complex b(2, 2);
	Complex c;
	
	c = a / b;
	cout << getMagnitude(c) << endl;*/
	
	
	m2 = Fractal(m1);
	saveToPPM(m2, "newton2.ppm");

	m3 = testMoveConstructor(600U, 800U);
	saveToPPM(m3, "newton3.ppm");

	return 0;
}