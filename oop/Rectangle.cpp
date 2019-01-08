#include "Rectangle.h"
#include <iostream>
#include <cmath>

Rectangle::Rectangle() : Rectangle(0, 0) {
}
Rectangle::Rectangle(size_t i, size_t j) : side_a(i), side_b(j) {
	std::cout << side_a << ", " << side_b << std::endl;
}

Rectangle::Rectangle(std::istream &is) {
	is >> side_a;
	is >> side_b;
	std::cout << "Rectangle created: ";
}

double Rectangle::Square() {
	return double (side_a) * double (side_b) ;
}

void Rectangle::Print() {
	std::cout << "a = "<< side_a <<", b = " << side_b << std::endl;
}

Rectangle::~Rectangle() {
	std::cout << "Rectangle deleted" << std::endl;
}
