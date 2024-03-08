#include "Complex.hpp"
#include "Pixel.hpp"
#include "Fractal.hpp"
#include <iostream>


Fractal testMoveConstructor(unsigned int row, unsigned int col)
{
	Fractal m(row, col);
	return m;
}

int main()
{
	Fractal m1(2000U, 2000U), m2, m3;
	saveToPPM(m1, "newton1.ppm");
	/*Complex a(6, 5);
	Complex b(2, 2);
	Complex c;
	
	c = a / b;
	cout << getMagnitude(c) << endl;
	*/
	cout << "step 2" << endl;
	
	m2 = Fractal(m1);
	saveToPPM(m2, "newton2.ppm");
	cout << "step 3" << endl;
	m3 = testMoveConstructor(600U, 800U);
	saveToPPM(m3, "newton3.ppm");
	
	return 0;
}