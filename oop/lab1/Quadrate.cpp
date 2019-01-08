#include "Quadrate.h"
#include <iostream>
#include <cmath>

Quadrate::Quadrate() : Quadrate(0) {
}
Quadrate::Quadrate(size_t i) : side_a(i) {
	std::cout << side_a << std::endl;
}

Quadrate::Quadrate(std::istream &is) {
	is >> side_a;
	std::cout << "Quadrate created: ";
}

double Quadrate::Square() {
	double p = 2;
	return pow(double (side_a), p) ;
}

void Quadrate::Print() {
	std::cout << "a = "<< side_a << std::endl;
}

Quadrate::~Quadrate() {
	std::cout << "Quadrate deleted" << std::endl;
}


