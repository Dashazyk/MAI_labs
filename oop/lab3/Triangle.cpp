#include "Triangle.h"
#include <iostream>
#include <cmath>

Triangle::Triangle() : Triangle(0, 0, 0) {
}

Triangle::Triangle(size_t i, size_t j, size_t k) : side_a(i), side_b(j), side_c(k) {
    std::cout << "Triangle created: " << side_a << ", " << side_b << ", " << side_c << std::endl;
}

Triangle::Triangle( Triangle& orig) {
    std::cout << "Triangle copy created" << std::endl;
    side_a = orig.side_a;
    side_b = orig.side_b;
    side_c = orig.side_c;
}

double Triangle::Square(){
    double p = double(side_a + side_b + side_c) / 2.0;
    return sqrt(p * (p - double(side_a))*(p - double(side_b))*(p - double(side_c)));
}

Triangle& Triangle::operator=( Triangle& right) {

    //if (this == &right) 
	//	return *this;

    std::cout << "Triangle copied" << std::endl;
    side_a = right.side_a;
    side_b = right.side_b;
    side_c = right.side_c;

    return *this;
}

Triangle::~Triangle() {
	std::cerr << "Deleting: " << std::endl;
	print(std::cerr);
	std::cerr << "\n";
	std::cout << "Triangle deleted" << std::endl;
}

void Triangle::print(std::ostream& os) {
	os << "a=" << side_a << ", b=" << side_b << ", c=" << side_c;
}

std::ostream& operator<<(std::ostream& os, Triangle& obj) {
	obj.print(os);
	return os;
}

