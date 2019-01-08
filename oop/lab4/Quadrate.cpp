#include "Quadrate.h"
#include <iostream>
#include <cmath>

Quadrate::Quadrate() : Quadrate(0) {
}
Quadrate::Quadrate(size_t i) : side_a(i) {
	std::cout << "Quadrate created: " << side_a << ", " << std::endl;
}

Quadrate::Quadrate( Quadrate& orig) {
	std::cout << "Quadrate copy created" << std::endl;
    side_a = orig.side_a;
}

double Quadrate::Square() {
	double p = 2;
	return pow(double (side_a), p) ;
}

void Quadrate::print(std::ostream& os) {
	os << "a=" << side_a ;
}

Quadrate& Quadrate::operator=( Quadrate& right) {

    std::cout << "Quadrate copied" << std::endl;
    side_a = right.side_a;
   
    return *this;
}

std::ostream& operator<<(std::ostream& os, Quadrate& obj) {
	obj.print(os);
	return os;
}

Quadrate::~Quadrate() {
	std::cerr << "Deleting: " << std::endl;
	print(std::cerr);
	std::cerr << "\n";
	std::cout << "Quadrate deleted" << std::endl;
}

